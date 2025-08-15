void	skip_spaces(char **input)
{
	while (**input == ' ' || **input == '\t')
		(*input)++;
}

int	is_shell_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
