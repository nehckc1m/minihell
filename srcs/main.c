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
	shell->env_array = NULL;
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
	/*char **cmd;
	int	i;
	int	j;
	bool	in_quotes;
	bool	in_word;
	int	start = 0;
	
	
	in_word = 0;
	in_quotes = 0;	
	j = 0;
	i = 0;
	if (shell->cmd)
		free(shell->cmd);
	while (prompt[i])
	{
		while (prompt[i] && prompt[i] == ' ')
			i++;
		if (prompt[i])
		{
			in_word = 1;
			while (in_word)
			{
				i++;
				if (prompt[i + 1] == ' ')
					in_word = 0;
			}
		}
		else if (prompt[i] == '\'' || prompt[i] == '\"')
		{
			in_quotes = 1;
			while ((prompt[i] != '\'' || prompt[i] != '\"') && in_quotes == 1)
				i++;
			in_quotes = 0;
			j++;
		}			
	}
	cmd = malloc(sizeof(char *) * (j + 1));
	i = 0;
	j = 0;
	while (prompt[i])
	{
		if (ft_isalpha(prompt[i]))
		{
			in_word = 1;
			while (in_word)
			{
				i++;
				if (prompt[i + 1] == ' ')
				{
					cmd[j] = strndup(prompt + start, i - start);
					in_word = 0;
				}
			}
		}
		else if (prompt[i] == '\'' || prompt[i] == '\"')
		{
			in_quotes = 1;
			while ((prompt[i] != '\'' || prompt[i] != '\"') && in_quotes == 1)
				i++;
			in_quotes = 0;
			cmd[j] = ft_strdup(prompt - i);
			j++;
		}
		else
			i++;			
	}
	cmd[j] = NULL;
	j = 0;
	while (cmd[j])
	{
		printf("array: %s\n",cmd[j]);
		j++;
	}
	return (cmd);*/
    char **cmd;
    int i = 0;
    int j = 0;
    int word_count = 0;
    int start = 0;
    char quote_char;

    // First pass: count words
    while (prompt[i])
    {
        // Skip spaces
        while (prompt[i] && prompt[i] == ' ')
            i++;
        
        if (prompt[i])
        {
            word_count++;
            // Handle quoted strings
            if (prompt[i] == '\'' || prompt[i] == '\"')
            {
                quote_char = prompt[i];
                i++;
                while (prompt[i] && prompt[i] != quote_char)
                    i++;
                if (prompt[i])
                    i++;
            }
            // Handle regular words
            else
            {
                while (prompt[i] && prompt[i] != ' ')
                {
                    if (prompt[i] == '\'' || prompt[i] == '\"')
                    {
                        quote_char = prompt[i];
                        i++;
                        while (prompt[i] && prompt[i] != quote_char)
                            i++;
                        if (prompt[i])
                            i++;
                    }
                    else
                        i++;
                }
            }
        }
    }

    // Allocate array
    cmd = malloc(sizeof(char *) * (word_count + 1));
    if (!cmd)
        return NULL;

    // Second pass: fill array
    i = 0;
    while (prompt[i])
    {
        // Skip spaces
        while (prompt[i] && prompt[i] == ' ')
            i++;
        
        if (prompt[i])
        {
            start = i;
            // Handle quoted strings
            if (prompt[i] == '\'' || prompt[i] == '\"')
            {
                quote_char = prompt[i];
                i++;
                while (prompt[i] && prompt[i] != quote_char)
                    i++;
                if (prompt[i])
                    i++;
            }
            // Handle regular words
            else
            {
                while (prompt[i] && prompt[i] != ' ')
                {
                    if (prompt[i] == '\'' || prompt[i] == '\"')
                    {
                        quote_char = prompt[i];
                        i++;
                        while (prompt[i] && prompt[i] != quote_char)
                            i++;
                        if (prompt[i])
                            i++;
                    }
                    else
                        i++;
                }
            }
            cmd[j] = strndup(prompt + start, i - start);
            j++;
        }
    }
    cmd[j] = NULL;

    // Free previous command if it exists
    if (shell->cmd)
        free(shell->cmd);

    return cmd;
}


void	free_readline(void)
{
	clear_history();
	rl_clear_pending_input();
	rl_clear_signals();
	rl_clear_history();
	rl_free_line_state();
	rl_deprep_terminal();	
}

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
		prompt = readline("😈mini_hell>");
		if (prompt == NULL)
		{
			
			printf("exit\n");
			free_readline();
			free_env_list(shell->env);
			return (0);
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
	return (0);
}
