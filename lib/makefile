# Variáveis
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
AR		:= ar rcs
RM		:= rm -f

# Arquivos e diretórios
NAME		:= libft.a
LIBFT_DIR	:= lib_ft

OBJ_DIR		:= obj

LIBFT_SRCS 	:= $(wildcard $(LIBFT_DIR)/*.c)

LIBFT_OBJS = $(patsubst $(LIBFT_DIR)/%.c,$(OBJ_DIR)/lib_ft/%.o,$(LIBFT_SRCS))

OBJS = $(LIBFT_OBJS) $(GNL_OBJS) $(PRINTF_OBJS)

YELLOW	:= \033[1;33m
GREEN	:= \033[1;32m
BLUE	:= \033[1;34m
RED		:= \033[1;31m
RESET	:= \033[0m
NL		:= \n

# Regras
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJ_DIR)/lib_ft/%.o: $(LIBFT_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/lib_ft
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	@echo "$(NL)$(RED)[libft]Cleaning objects...$(RESET)"
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)[libft]Removing binary:$(RESET) $(NAME)"
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
