#include <stdlib.h>
#include <string.h>

#include "lib_ft.h"
#include <stdio.h>

#include <unistd.h>
#include "minishell.h"


static const char *get_env_value(const char *key)
{
	int i;
	size_t key_len;

	key_len = strlen(key);
	i = 0;
	while (__environ[i])
	{
		if (strncmp(__environ[i], key, key_len) == 0 && __environ[i][key_len] == '=')
			return __environ[i] + key_len + 1;
		i++;
	}
	return NULL;
}

static char *extract_var_name(const char **ptr)
{
	const char *start = *ptr;
	int len = 0;

	// Calcula o tamanho da variável
	while (**ptr && (ft_isalnum(**ptr) || **ptr == '_'))
	{
		(*ptr)++;
		len++;
	}

	if (len == 0)
		return (NULL);

	char *var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);

	ft_strlcpy(var_name, start, len + 1);
	return var_name;
}

/*
 * append_char:
 * Adiciona um caractere único à string resultante.
 */
static void append_char(char **result, char c)
{
	char tmp[2] = {c, '\0'};
	char *old = *result;
	*result = ft_strjoin(*result, tmp);
	free(old);
}

/*
 * append_str:
 * Adiciona uma string inteira à string resultante.
 */
static void append_str(char **result, const char *str)
{
	char *old = *result;
	*result = ft_strjoin(*result, str);
	free(old);
}


/*
 * expand_variables:
 * Expande variáveis no formato $VAR se existirem no mock.
 * Retorna nova string com substituições.
 */

char *expand_variables(const char *input)
{
	char *result = ft_strdup("");
	const char *ptr = input;

	while (*ptr)
	{
		if (*ptr == '$')
		{
			ptr++; // pula o '$'
			char *var_name = extract_var_name(&ptr);

			if (var_name)
			{
				const char *value = get_env_value(var_name);
				if (value)
					append_str(&result, value);
				free(var_name);
			}
			// Se inválida: expande para vazio (nada é adicionado)
		}
		else
		{
			append_char(&result, *ptr);
			ptr++;
		}
	}
	return result;
}
