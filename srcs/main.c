/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:55:11 by micchen           #+#    #+#             */
/*   Updated: 2024/11/16 21:58:11 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	ft_strcmp(char *s1, char *s2)
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


int main(int ac, char **av, char **env)
{
	(void)av;
	char *prompt;
	char    path[PATH_MAX];
	t_env	*list;

	if (ac > 1)
		return (printf("ERROR: too much args for minishell"));
	list = list_env(env);
	//print_list(list);
	while (1)
	{
		list = list_env(env);
		prompt = readline("😈mini_hell>");
		if (prompt == NULL)
		{
			printf("exit\n");
			break;
		}
		if (*prompt) 
			add_history(prompt);
		if (ft_strcmp(prompt, "pwd") == 0)
			printf("%s\n", getcwd(path, sizeof(path)));
		else if (ft_strcmp(prompt, "env") == 0)
			print_list(list);
	}
	return (0);
}
