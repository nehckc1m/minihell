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

char	*remove_quotes(char *prompt)
{
	char	*res;
	int	i;
	int	j;
	int	quote_count;
	int	in_quotes;
	
	i = 0;
	j = 0;
	in_quotes = 0;
	quote_count = 0;
	if (!prompt)
		return (NULL);
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '\"')
			quote_count++;
		i++;
	}
	res = malloc(sizeof(char) * (ft_strlen(prompt) - quote_count + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (prompt[i])
	{
		if ((prompt[i] == '\'' || prompt[i] == '\"') && in_quotes == 0)
			in_quotes = prompt[i];
		else if (prompt[i] == in_quotes)
			in_quotes = 0;
		else
			res[j++] = prompt[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

void init_hell(t_shell *shell, char **env)
{
	shell->env = list_env(env);
	shell->cmd = NULL;
	shell->running = 1;

}

int	check_quotes(char *prompt)
{
	int	i;
	bool	open_s_quote;
	bool	open_d_quote;
	i = 0;
	open_s_quote = false;
	open_d_quote = false;
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

static char **prompt_to_array(char *prompt, t_shell *shell)
{
	char **cmd;
	
	if (shell->cmd)
		free(shell->cmd);
	cmd = malloc(sizeof(char *));
	cmd = ft_split(prompt, ' ');
	return (cmd);
}
/*static void free_shell(t_shell *shell)
{
	if (shell->cmd)
		free(shell->cmd);
	free_env_list(shell->env);


}*/
int main(int ac, char **av, char **env)
{
	(void)av;
	char *prompt;
	t_shell	*shell;

	if (ac > 1)
		return (printf("ERROR: too much args for minishell\n"));
	shell = malloc(sizeof(t_shell));
	init_hell(shell, env);
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
		if (check_quotes(prompt)== 1)
			printf ("ERROR: quotes not closed properly\n");
		else
		{
			shell->cmd = prompt_to_array(prompt, shell);
			shell->cmd[0] = remove_quotes(shell->cmd[0]);
			if (shell->cmd[0])
				commands(shell);
		}
		free(prompt);
	}
	//free_shell(shell);
	//free(shell);
	return (0);
}
