#include "minishell.h"
// #include "syntax.h"

int	syntax_error(char *token)
{
	printf("Unexpected token : \"%s\" ", token);
	return (1);
}

/* int redirect_verif() */

int	unexpected_token(char *input)
{
	if (input[0] == '<' && input[1] == '<')
		return (syntax_error("<<"));
	else if (input[0] == '>' && input[1] == '>')
		return (syntax_error(">>"));
	input[1] = '\0';
	return (syntax_error(input));
}

int	invalid_token(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	return (0);
}