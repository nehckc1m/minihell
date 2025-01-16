/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 06:12:07 by micchen           #+#    #+#             */
/*   Updated: 2025/01/14 06:12:09 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var(char *env)
{
	int	i;
	int	res;
	
	i = 0;
	res = 0;
	if (env[0] == '=')
		return (0);
	while (env[i] && ft_isalpha(env[i]))
	{
		i++;
		if (env[i] == '=')
			res = 1;
	}
	return (res);
}


int	alloc_size(char *str, t_shell *shell)
{
	int	i;
	int	in_quotes;
	char	*env_var_value;
	char	*word;
	int	size;
	
	size = 0;
	in_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && in_quotes != 2)
			in_quotes = (in_quotes == 1) ? 0 : 1;
		else if (str[i] == '\"' && in_quotes != 1)
			in_quotes = (in_quotes == 2) ? 0 : 2;
		else if (str[i] == '$' && in_quotes != 1)
		{
			word = extract_word(&str[i + 1]);
			//printf("word: %s\n", word);
			if (word)
			{
				env_var_value = get_env_value(shell->env, word);
				//printf("env: %s\n", env_var_value);
				if (env_var_value)
				{
					i += ft_strlen(word);
					size += ft_strlen(env_var_value);
					free(env_var_value);
				}
				else
					i += ft_strlen(word);
				free(word);
			}
			else
				size++;
		}
		else
			size++;
		i++;
	}
	return (size);
}

char	*handle_quotes(char *prompt, t_shell *shell)
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
			//printf("word: %s\n",word);
			if (word)
			{
				env_var_value = get_env_value(shell->env, word);
				//printf("env_var_value: %s\n",env_var_value);
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
	printf("dans HANDLE: %s\n",res);
	return (res);
}

char	**parsing_cmd(char **cmd, t_shell *shell)
{
	int	i;

	i = -1;
	while (cmd[++i])
		cmd[i] = handle_quotes(cmd[i], shell);
	return (cmd);
}

