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
	while (current->next)
	{
		if (strcmp(current->name, var) == 0)
			value = ft_strdup(current->value);
		current = current->next;
	}
	if (!value)
		return (NULL);
	else
		return (value);
}

char	*handle_quotes_echo(char *prompt, t_shell *shell)
{
	char	*res;
	int	i;
	int	j;
	int	quote_count;
	int	in_quotes;
	char	*env_var_value;
	char	*word;
	
	i = 0;
	j = 0;
	in_quotes = 0;
	quote_count = 0;
	if (!prompt)
		return (NULL);
	res = malloc(sizeof(char) * alloc_size(prompt, shell) + 1);
	if (!res)
		return (NULL);
	i = 0;
	ft_memset(res, 0, alloc_size(prompt, shell) + 1);
	while (prompt[i])
	{
		if (prompt[i] == '\'' && in_quotes != 2)
			in_quotes = (in_quotes == 1) ? 0 : 1;
		else if (prompt[i] == '\"' && in_quotes != 1)
			in_quotes = (in_quotes == 2) ? 0 : 2;
		else if (prompt[i] == '$' && in_quotes != 1) // if not in single quote
		{
			word = extract_word(&prompt[i + 1]);
			if (word)
			{
				env_var_value = get_env_value(shell->env, word);
				if (env_var_value)
				{
					res = ft_strcat(res, env_var_value);
					j += ft_strlen(env_var_value);
					i += ft_strlen(word);
					free(env_var_value);
				}
				else
					i += ft_strlen(word);
				free(word);
			}
		}
		else
			res[j++] = prompt[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

void ft_echo(char **cmd, t_shell *shell)
{
	//int	i;
	bool	newline;
	char	*line;

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
		line = handle_quotes_echo(*cmd, shell);
		printf("%s",line);
		free(line);
		cmd++;
		if (*cmd)
			printf(" ");
	}
	if (newline)
		printf("\n");
}
