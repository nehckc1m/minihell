/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itoudji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:08:34 by itoudji           #+#    #+#             */
/*   Updated: 2025/01/17 00:08:44 by itoudji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env_list(t_env *env_list)
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

t_env	*create_node(char *name, char *value)
{
	t_env	*new_node;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return NULL;
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return new_node;
}