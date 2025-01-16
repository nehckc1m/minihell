#include "minishell.h"
// #include "syntax.h"

int	starts_with_pipe(char *input)
{
	if (input[0] == '|')
		return (syntax_error("|"));
	return (0);
}

char	*get_next_pipe(char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				str++;
		}
		if (*str == '"')
		{
			str++;
			while (*str != '"')
				str++;
		}
		if (*str == '|')
			return (str);
		str++;
	}
	return (NULL);
}

int	has_empty_pipe(char *input)
{
	char	*next_pipe;

	next_pipe = get_next_pipe(input);
	if (!next_pipe)
		return (0);
	next_pipe++;
	while (*next_pipe == ' ' || *next_pipe == '\t')
		next_pipe++;
	if (*next_pipe == '|')
		return (syntax_error("|"));
	return (has_empty_pipe(next_pipe));
}

int	invalid_syntax(char *input)
{
	if (starts_with_pipe(input))
		return (1);
	if (/*redirect_verif*/ 1 = 0)
		return (1);
	if (has_empty_pipe(input))
		return (1);
	return (0);
}