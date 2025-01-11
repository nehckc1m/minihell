/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 23:16:02 by micchen           #+#    #+#             */
/*   Updated: 2025/01/12 00:18:02 by micchen          ###   ########.fr       */
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
/*
static void	update_home(t_

static void	update_pwd(t_shell *shell)
{




}
*/
void	ft_cd(t_shell *shell, char *path)
{
	char	*home_path;
	int	err;

	err = 0;
	if (path == NULL || path[0] == '\0')
	{
		err = chdir(get_env_value(shell->env, "HOME"));
		perror("cd");
		return;
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
	return /*(update_pwd(shell->env), update_home(shell->env))*/;
}
