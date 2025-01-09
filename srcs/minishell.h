/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:01:31 by micchen           #+#    #+#             */
/*   Updated: 2024/11/16 21:54:57 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <limits.h>
# include <stdbool.h>

typedef struct s_env{
	char *name;
	char *value;
	struct s_env	*next;
}		t_env;

typedef struct s_shell{
	struct s_env	*env;
	struct s_env	*copy_env;
	char		**cmd;
	bool	running;
	
}		t_shell;

//main.c
char	*remove_quotes(char *prompt);
int	check_quotes(char *prompt);
//unset.c
int	ft_unset(t_env *env, char **args);
//env.c
t_env	*list_env(char **env);
t_env	*export_env(t_shell *shell, char **env_var);
void free_env_list(t_env *env_list);
void	print_list(t_env *list_env);
//commands.c
void	commands(t_shell *shell);
//utils.c
int     ft_strcmp(char *s1, char *s2);
//echo.c
void ft_echo(char **cmd, t_shell *shell);
#endif
