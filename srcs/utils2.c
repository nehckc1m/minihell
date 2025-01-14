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

