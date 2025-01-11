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
	else if	(ft_strcmp(shell->cmd[0], "cd") == 0)
		ft_cd(shell, shell->cmd[1]);
	else
		printf("command not found: %s\n", shell->cmd[0]);
}	
