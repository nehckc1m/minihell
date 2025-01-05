/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:55:11 by micchen           #+#    #+#             */
/*   Updated: 2025/01/03 19:59:43 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_hell(t_shell *shell, char **env)
{
	//t_env	*list;
	shell->env = list_env(env);
	shell->running = 1;

}

static int	check_quotes(char *prompt)
{
	int	i;
	bool	open_s_quote;
	bool	open_d_quote;
	i = 0;
	open_s_quote = 0;
	open_d_quote = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' && !open_d_quote)
			open_s_quote = !open_s_quote;
		if (prompt[i] == '\"' && !open_s_quote)
			open_d_quote = !open_d_quote;
		i++;
	}
	return (open_s_quote || open_d_quote);
}

int main(int ac, char **av, char **env)
{
	(void)av;
	char *prompt;
	//t_env	*list;
	t_shell	*shell;

	if (ac > 1)
		return (printf("ERROR: too much args for minishell\n"));
	shell = malloc(sizeof(t_shell));
	init_hell(shell, env);
	//list = list_env(env);
	while (shell->running)
	{
		//list = list_env(env);
		prompt = readline("😈mini_hell>");
		if (prompt == NULL)
		{
			printf("exit\n");
			break;
		}
		if (*prompt) 
			add_history(prompt);
		if (check_quotes(prompt))
			printf ("ERROR: quotes not closed properly\n");
		commands(prompt, shell);
	}
	return (0);
}
