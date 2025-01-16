/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:42:43 by micchen           #+#    #+#             */
/*   Updated: 2025/01/10 20:22:45 by itoudji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *dest, char *to)
{
	char	*res;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	res = malloc(sizeof(char) * ft_strlen(dest) + ft_strlen(to) + 1);
	while (dest[i])
	{
		res[j] = dest[i];
		i++;
		j++;
	}
	i = 0;
	while (to[i])
	{
		res[j] = to[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*extract_word(char *str)
{
	int	i;
	char	*res;
	
	i = 0;
	while (str[i] >= 'A' && str[i] <= 'Z')
		i++;
	res = malloc(sizeof(char) * i + 1);
	i  = 0;
	while (str[i] >= 'A' && str[i] <= 'Z')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_env_value(t_env *env, char *var)
{
	t_env	*current;
	char	*value;

	value = NULL;
	current = env;
	//printf("var:%s\n", var);
	while (current->next)
	{
		if (strcmp(current->name, var) == 0)
		{
			break;
		}
		current = current->next;
	}
	value = ft_strdup(current->value);
	//printf("name: %s\n", current->name);
	//printf("value: %s\n",current->value);
	//printf("value: %s\n",value);
	if (!value)
		return (NULL);
	else
		return (value);
}

void ft_echo(char **cmd)
{
	//int	i;
	bool	newline;


	newline = true;
	if (!*cmd)
	{
		printf("\n");
		return ;
	}
	while (*cmd && ft_strcmp(*cmd, "-n") == 0)
	{
		cmd++;
		newline = false;
	}
	while (*cmd)
	{
		printf("%s",*cmd);
		cmd++;
		if (*cmd)
			printf(" ");
	}
	if (newline)
		printf("\n");
}
