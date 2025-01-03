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

typedef struct s_env{
	char *name;
	char *value;
	struct s_env	*next;
}		t_env;

//env.c
t_env	*list_env(char **env);
void	print_list(t_env *list_env);
#endif
