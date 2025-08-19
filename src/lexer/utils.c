
#include "token_types.h"
#include "lexer.h"

int	try_add_token(t_token **tokens, t_token_type type, char *value)
{
	if (!create_and_add_token(tokens, type, value))
		return (0);
	return (1);
}
int	handle_redirect_out_operator(t_token **tokens, char **current)
{
	if (*(*current + 1) == '>')
	{
		if (!try_add_token(tokens, TOKEN_REDIRECT_OUT_APPEND, ">>"))
			return (0);
		(*current) += 2;
	}
	else
	{
		if (!try_add_token(tokens, TOKEN_REDIRECT_OUT, ">"))
			return (0);
		(*current)++;
	}
	return (1);
}