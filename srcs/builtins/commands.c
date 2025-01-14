/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:32:43 by micchen           #+#    #+#             */
/*   Updated: 2025/01/10 20:22:30 by itoudji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_cmd_in_path(char *cmd, t_env *env)
{
	char	*path;
	char	**dirs;
	t_env	*current;
	int	i;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	current = env;
	path = NULL;
	while (current->next)
	{
		if (ft_strcmp(current->name, "PATH") == 0)
		{
			path = ft_strdup(current->value);
			break;
		}
		current = current->next;
	}
	if (path == NULL)
		return (NULL);
		
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		path = ft_strjoin_three(dirs[i], "/", cmd);
		if (access(path, X_OK) == 0)
		{
			free_array(dirs);
			return (path);
		}
		free(path);
		i++;
	}
	free_array(dirs);
	return (NULL);
}


static void	external_command(t_shell *shell, t_env *env)
{
	pid_t	pid;
	int	status;
	char	*cmd_path;

	cmd_path = find_cmd_in_path(shell->cmd[0], env);
	if (cmd_path == NULL)
	{
		printf("command not found: %s\n", shell->cmd[0]);
		return ;
	}
	
	pid = fork();
	shell->env_array = convert_env_to_array(env);
	if (pid == 0)
	{
		if (execve(cmd_path, shell->cmd, shell->env_array) == -1)
		{
			perror("minishell: execve\n");
			shell->running = 0;
		}
	}
	
	else if (pid < 0)
		perror("minishell: fork");
	else
		waitpid(pid, &status, 0);
	free(cmd_path);
}

void	commands(t_shell *shell)
{
	if (ft_strcmp(shell->cmd[0], "pwd") == 0)
		ft_pwd(&shell->cmd[1]);
	else if (ft_strcmp(shell->cmd[0], "env") == 0)
		print_list(shell->env);
	else if (ft_strcmp(shell->cmd[0], "export") == 0)
		export_env(shell, shell->cmd + 1);
	else if	(ft_strcmp(shell->cmd[0], "echo") == 0)
		ft_echo(shell->cmd + 1, shell);
	else if (ft_strcmp(shell->cmd[0], "unset") == 0)
		ft_unset(shell->env, shell->cmd + 1);
	else if (ft_strcmp(shell->cmd[0], "exit") == 0)
		ft_exit(shell, shell->cmd + 1);
	else if (ft_strcmp(shell->cmd[0], "cd") == 0)
		ft_cd(shell, shell->cmd[1]);
	else
		 external_command(shell, shell->env);
		//printf("command not found: %s\n", shell->cmd[0]);
}
