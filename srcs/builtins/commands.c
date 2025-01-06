/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:32:43 by micchen           #+#    #+#             */
/*   Updated: 2025/01/03 19:32:45 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void ft_echo(char **cmd)
{
	//int	i;
	bool	newline;

	newline = true;
	if (!*cmd)
	{
		printf("\n");
		return ;
	}
	while (*cmd && ft_strcmp(*cmd, "-n") == 0)
	{
		cmd++;
		newline = false;
	}
	while (*cmd)
	{
		printf("%s",*cmd);
		cmd++;
	}
	if (newline)
		printf("\n");
}


void	commands(t_shell *shell)
{
	char    path[PATH_MAX];
	if (ft_strcmp(shell->cmd[0], "pwd") == 0)
		printf("%s\n", getcwd(path, sizeof(path)));
	else if (ft_strcmp(shell->cmd[0], "env") == 0)
		print_list(shell->env);
	else if (ft_strcmp(shell->cmd[0], "export") == 0)
		export_env(shell, shell->cmd + 1);
	else if	(ft_strcmp(shell->cmd[0], "echo") == 0)
		ft_echo(shell->cmd + 1);
	else
		printf("command not found: %s\n", shell->cmd[0]);
	//else if (ft_strcmp(prompt
}	
