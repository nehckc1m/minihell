/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:55:11 by micchen           #+#    #+#             */
/*   Updated: 2024/11/16 21:58:11 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void free_env_list(t_env *env_list)
{
    t_env *temp;

    while (env_list)
    {
        temp = env_list;
        env_list = env_list->next;
        free(temp->name);
        free(temp->value);
        free(temp);
    }
}

t_env	*list_env(char **env)
{
	int	i;
	t_env	*env_list;
	t_env	*tmp;
	t_env	*head;
	
	env_list = NULL;
	head = NULL;
	i = 0;
	while (env[i])
	{
		tmp = malloc(sizeof(t_env));
		if (!tmp)
		{
			free_env_list(head);
			return NULL;
		}
		tmp->name = strndup(env[i], ft_strchr(env[i], '=') - env[i]);
		tmp->value = strdup(ft_strchr(env[i], '=') + 1);
		tmp->next = NULL;
		if (!tmp->name || !tmp->value)
		{
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return NULL;
		}
		if (!head)
			head = tmp;
		else
			env_list->next = tmp;
		env_list = tmp;
		i++;
	}
	return (head);
}

void	print_list(t_env *list_env)
{
    t_env *current = list_env;

    while (current)
    {
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
    }
}
