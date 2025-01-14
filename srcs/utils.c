/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:41:34 by micchen           #+#    #+#             */
/*   Updated: 2025/01/03 19:42:04 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Compter le nombre d'éléments dans la liste chaînée
int	env_list_size(t_env *env)
{
	int size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return size;
}

// Convertir la liste chaînée en tableau de chaînes
char	**convert_env_to_array(t_env *env)
{
	int size;
	char **env_array; // +1 pour NULL final
	int i;
	char	*tmp;
	
	i = 0;
	size = env_list_size(env);
	env_array = malloc((size + 1) * sizeof(char *));

	if (!env_array)
		return NULL;
	while (env)
	{
		tmp = malloc(ft_strlen(env->name) + ft_strlen(env->value) + 2);
		if (!tmp)
		{
			free_array(env_array);
			return NULL;
		}
		tmp = ft_strjoin_three(env->name, "=", env->value);
		env_array[i] = tmp; // Copier la variable d'environnement
		env = env->next;
		i++;
	}
	env_array[i] = NULL; // Terminer le tableau par NULL
	return env_array;
}


void free_array(char **array)
{
	int i;
	
	i = 0;
	if (!array)
        return;

	while (array[i])
	{
		free(array[i]); // Libérer chaque chaîne de caractères
		i++;
	}
	free(array); // Libérer le tableau lui-même
}

char *ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char 	*res;
	char	*tmp;
	
	if(!s1 || !s2 || !s3)
		return NULL;
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return NULL;
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
