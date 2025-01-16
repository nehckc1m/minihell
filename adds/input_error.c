

int	has_input_error(char *input, int *exit_status, t_env *minienv)
{
	int	result;

	result = 0;
	if (/*empty*/)
		result = 1;
	else if (/*quotes*/))
		result = 1;
	else if (invalid_syntax(input))
	{
		/*exit_status*/
		result = 1;
	}
	else if (/*heredoc*/)
		result = 1;
	if (result == 1)
		free(input);
	return (result);
}