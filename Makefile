# **************************************************************************** #
#                              Minishell Makefile                              #
# **************************************************************************** #

NAME := minishell

#flags
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
RM		:= rm -f

#Dir
SRC_DIR	:= src
OBJ_DIR	:= obj

#SRCS	:= $(SRC_DIR)/minishell.c
SRCS	:= $(shell find $(SRC_DIR) -name '*.c')
OBJ		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

HEADER	:= -I ./includes

YELLOW	:= \033[1;33m
GREEN	:= \033[1;32m
BLUE	:= \033[1;34m
RED		:= \033[1;31m
RESET	:= \033[0m
NL		:= \n

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)
	@echo "$(NL)$(GREEN)Build completed successfully: $(NAME)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS)  -c $< $(HEADER) -o $@
	@echo  "$(YELLOW)Compiling source file:$(RESET) $(notdir $<)"

clean:
	@echo "$(NL)$(RED)Cleaning objects...$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Removing binary:$(RESET) $(NAME)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re