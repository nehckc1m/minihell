/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 23:16:02 by micchen           #+#    #+#             */
/*   Updated: 2025/01/12 01:49:59 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_pwd(char **cmd)
{
	int	i;
	char	path[PATH_MAX];

	i = 0;
	if (cmd[i])
	{
		i++;
	}
	if (i > 0)
		printf("pwd: too many arguments\n");
	else
		printf("%s\n", getcwd(path,sizeof(path)));
}

static t_env	*update_pwd(t_shell *shell)
{
	t_env	*current;
	char	path[PATH_MAX];
	int	updated;
	char	*old_path;

	updated = 1;
	current = shell->env;
	while (current->next)
	{
		if (ft_strcmp(current->name, "PWD") == 0)
		{
			old_path = current->value;
			break;
		}
		current = current->next;
	}
	while (updated != 0)
	{
		current = shell->env;
		while (current->next)
		{
			if (ft_strcmp(current->name, "OLDPWD") == 0 && updated == 1)
			{
				if (current->value)
					free(current->value);
				current->value = ft_strdup(old_path);
				updated = 2;
			}
			if (ft_strcmp(current->name, "PWD") == 0 && updated == 2)
			{
				current->value = getcwd(path, sizeof(path));
				updated = 0;
			}
			current = current->next;
		}
	}
	/*else
	{
		updated_pwd = malloc(sizeof(t_env));
		updated_pwd->name = "PWD";
		updated_pwd->value = getcwd(path, sizeof(path));
		updated_pwd->next = NULL;
		current = updated_pwd;
	}*/
	return (shell->env);
}

void	ft_cd(t_shell *shell, char *path)
{
	char	*home_path;
	int	err;

	err = 0;
	if (path == NULL || path[0] == '\0')
	{
		err = chdir(get_env_value(shell->env, "HOME"));
		perror("cd");
		shell->env = update_pwd(shell);
		return ;
	}
	else if (path[0])
	{
		if (path[0] == '~')
		{
			home_path = ft_strjoin(get_env_value(shell->env, "HOME"), path + 1);
			err = chdir(home_path);
			free(home_path);
		}
		else
			err = chdir(path);
	}
	if (err != 0)
	{
		perror("cd");
		return ;
	}
	shell->env = update_pwd(shell);
	return ;
}
