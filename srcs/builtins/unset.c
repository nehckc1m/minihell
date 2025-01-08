/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:12:41 by micchen           #+#    #+#             */
/*   Updated: 2025/01/08 03:51:09 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_rm(t_env *env, char *var)
{
	t_env	*current;
	char	*name;
	t_env	*prev;

	current = env;
	prev = NULL;
	name = strndup(var, ft_strchr(var, '=') - var);
	while (current->next)
	{

		if (ft_strcmp(name, current->name) == 0)
		{
			prev->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			free(name);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

int	ft_unset(t_env	*env, char **args)
{
	t_env	*head;
	int	i;

	i = 0;
	head = env;
	if (!*args)
	{
		printf("unset: not enough arguments\n");
		return(1);
	}
	else
	{
		while(args[i])
		{
			ft_rm(env, args[i]);
			i++;
		}
	}
	return (0);
}
