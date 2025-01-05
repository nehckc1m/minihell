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

void	commands(char *prompt, t_shell *shell)
{
	char    path[PATH_MAX];
	if (ft_strcmp(prompt, "pwd") == 0)
		printf("%s\n", getcwd(path, sizeof(path)));
	else if (ft_strcmp(prompt, "env") == 0)
		print_list(shell->env);
	else if (ft_strcmp(prompt, "export") == 0)
		export(shell->env);
	//else if (ft_strcmp(prompt
}	
