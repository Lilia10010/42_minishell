#!/bin/bash

# Diretórios principais
mkdir -p minishell/{src,include,obj,lib}
mkdir -p minishell/src/{main,lexer,parser,executor,builtins,env,redirections,signals,utils}
mkdir -p minishell/lib/libft
touch minishell/Makefile

# Arquivo principal
touch minishell/src/main/minishell.c
touch minishell/include/minishell.h

# Headers
for h in lexer parser executor builtins env signals redirections utils; do
  touch "minishell/include/${h}.h"
done

# Sources
declare -A modules=(
  [lexer]="lexer tokenizer_utils"
  [parser]="parser parser_utils"
  [executor]="executor pipes process"
  [builtins]="cd echo env exit export pwd unset"
  [env]="env_utils export_utils"
  [redirections]="redirections heredoc"
  [signals]="signals"
  [utils]="str_utils free_utils error"
)

for dir in "${!modules[@]}"; do
  for file in ${modules[$dir]}; do
    touch "minishell/src/${dir}/${file}.c"
  done
done

echo "Estrutura criada com sucesso! Agora é só codar, meu consagrado! 🚀"

#rodar o script de setup
#chmod +x setup.sh
#./setup.sh
