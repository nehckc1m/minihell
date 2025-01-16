/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:55:11 by micchen           #+#    #+#             */
/*   Updated: 2025/01/10 20:23:04 by itoudji          ###   ########.fr       */
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

void	print_list(t_env *list_env)
{
    t_env *current = list_env;

    while (current)
    {
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
    }
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

// Fonction pour insérer un nœud dans la liste triée en respectant l'ordre alphabétique
void insert_sorted(t_env **copy, t_env *new_node)
{
	t_env *current;

    // Cas où la liste triée est vide ou que le nouveau nœud doit être inséré au début
	if (*copy == NULL || ft_strcmp(new_node->name, (*copy)->name) < 0)
	{
		new_node->next = *copy;
		*copy = new_node;
		return;
	}

    // Trouver la bonne position pour insérer le nouveau nœud
	current = *copy;
	while (current->next != NULL && ft_strcmp(new_node->name, current->next->name) > 0)
		current = current->next;

    // Insérer le nouveau nœud dans la bonne position
	new_node->next = current->next;
	current->next = new_node;
}

// Fonction principale pour trier la liste `env`
t_env *sort_env(t_env *env, t_env *copy)
{

	t_env	*current;
	t_env	*new_node;
	
	current = env;
    // Initialiser la liste triée (copy) à NULL
	copy = NULL;

    // Parcourir la liste non triée et insérer chaque nœud dans la liste triée
	while (current != NULL)
	{
		new_node = create_node(current->name, current->value);
		if (!new_node)
			return NULL;  // Gestion d'erreur en cas d'échec d'allocation
		insert_sorted(&copy, new_node);
		current = current->next;
	}
	return copy;
}

void	print_list_no_args(t_env *list_env)
{
	t_env	*current;
	current = list_env;
	
	while (current->next)
	{
		printf("declare -x %s=\"%s\"\n", current->name, current->value);
		current = current->next;
	}
}

t_env	*export_env(t_shell *shell, char **env_var)
{
	t_env	*tmp;
	t_env	*new;
	int	i;
	int	j=0;
	
	i = 0;
	new = NULL;
	if (!*env_var)
	{
		shell->copy_env = sort_env(shell->env, shell->copy_env);
		print_list_no_args(shell->copy_env);
		return (shell->copy_env);
	}
	while (env_var[i])
	{
		new = malloc (sizeof(t_env));
		new->name = strndup(env_var[i], ft_strchr(env_var[i], '=') - env_var[i]);
		new->value = strdup(ft_strchr(env_var[i], '=') + 1);
		tmp = shell->env;
		while(tmp->next)
		{
			if (ft_strcmp(tmp->name, new->name) == 0)
				break;
			tmp = tmp->next;
			j++;
		}
		if (ft_strcmp(tmp->name, new->name) == 0)
			tmp = new;
		else
		{
			new->next = NULL;
			tmp->next = new;
		}
		i++;
	}
	return (shell->env);
}

