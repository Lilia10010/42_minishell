void	debug_print_tokens(t_token *tokens)
{
	t_token	*current;
	int		i;

	i = 0;
	current = tokens;
	printf("\n=== TOKENS DEBUG ===\n");
	while (current)
	{
		printf("Token %d: tipo=%d, valor=%s\n",
			i++, current->type, current->value);
		current = current->next;
	}
	printf("===================\n");
}