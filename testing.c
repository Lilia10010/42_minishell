
#include <stdio.h>

int main(int argc, char **argv)
{
	int i = 0;
	while (i < argc)
	{
		printf("posicao: [%d] - argumento %s\n", i, argv[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// char *replace(const char *original, const char *target, const char *replacement)
// {
//     if (!original || !target || !replacement)
//         return NULL;

//     size_t len_target = strlen(target);
//     size_t len_replacement = strlen(replacement);
//     size_t count = 0;

//     // Conta quantas vezes a target aparece
//     const char *tmp = original;
//     while ((tmp = strstr(tmp, target)))
//     {
//         count++;
//         tmp += len_target;
//     }

//     // Aloca espaço para a nova string
//     size_t new_len = strlen(original) + count * (len_replacement - len_target);
//     char *result = malloc(new_len + 1);
//     if (!result)
//         return NULL;

//     // Substituição real
//     const char *orig_ptr = original;
//     char *res_ptr = result;

//     while (*orig_ptr)
//     {
//         if (strstr(orig_ptr, target) == orig_ptr)
//         {
//             strcpy(res_ptr, replacement);
//             res_ptr += len_replacement;
//             orig_ptr += len_target;
//         }
//         else
//         {
//             *res_ptr++ = *orig_ptr++;
//         }
//     }
//     *res_ptr = '\0';

//     return result;
// }
