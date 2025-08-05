

#ifndef PROMPT_DEFS_H
#define PROMPT_DEFS_H

#define GREEN "\001\033[1;32m\002"
#define RESET_COLOR "\001\033[0m\002"
#define GREEN_BG     "\001\033[42m\002"
#define ROSA "\001\033[48;5;206m\002"
#define BOLD "\001\033[1m\002"


//#define MATRIX_PROMPT "\033[1;32m\033[40m minishell$ " RESET_COLOR
//#define MATRIX_PROMPT "\033[1;32m\033[40m minishell$ " RESET_COLOR
//#define MATRIX_PROMPT "\033[30m" GREEN_BG " minishell$ " RESET_COLOR
#define MINI_PROMPT ROSA BOLD " minishell$ " RESET_COLOR " "

#endif // PROMPT_DEFS_H
