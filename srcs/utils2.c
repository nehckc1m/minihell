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
			env_var_value = get_env_value(shell->env, extract_word(&str[i + 1]));
			if (env_var_value)
			{
				//i += 
				free(env_var_value);
			}
		}
		else
			i++;
	}
	return (i);
}

