/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:25:07 by micchen           #+#    #+#             */
/*   Updated: 2025/01/10 20:24:00 by itoudji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell, char **cmd)
{
	int	i;
	
	i = 0;
	//printf("ex1t: %s\n", cmd[i]);
	if (ft_isalpha((int)*cmd[i]))
	{
		printf("exit: %s: numeric argument required\n", cmd[i]);
		shell->running = 0;
		return ;
	}
	while (cmd[i])
		i++;
	if (i > 1)
	{	
		printf("exit: too many arguments\n");
		return ;
	}
	printf("exit\n");
	shell->running = 0;
}
