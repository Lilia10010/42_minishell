minishell/
├── Makefile
├── minishell.c           # Arquivo principal (main)
├── include/              # Headers (.h)
│   ├── minishell.h       # Header geral com includes comuns
│   ├── lexer.h           # Tokenização
│   ├── parser.h          # Parser e AST
│   ├── executor.h        # Execução de comandos
│   ├── builtins.h        # Built-ins (cd, echo, etc)
│   ├── env.h             # Manipulação de variáveis de ambiente
│   ├── signals.h         # Tratamento de sinais (SIGINT, etc)
│   ├── redirections.h    # Redirecionamentos
│   ├── utils.h           # Funções auxiliares
├── src/
│   ├── main/             # Entrada principal
│   │   └── minishell.c   # Função main
│   ├── lexer/            # Tokenização do input
│   │   ├── lexer.c
│   │   └── tokenizer_utils.c
│   ├── parser/           # Construção da AST / comandos
│   │   ├── parser.c
│   │   └── parser_utils.c
│   ├── executor/         # Execução dos comandos
│   │   ├── executor.c
│   │   ├── pipes.c
│   │   └── process.c
│   ├── builtins/         # Comandos internos
│   │   ├── cd.c
│   │   ├── echo.c
│   │   ├── env.c
│   │   ├── exit.c
│   │   ├── export.c
│   │   ├── pwd.c
│   │   └── unset.c
│   ├── env/              # Variáveis de ambiente
│   │   ├── env_utils.c
│   │   └── export_utils.c
│   ├── redirections/     # Redirecionamento e heredocs
│   │   ├── redirections.c
│   │   └── heredoc.c
│   ├── signals/          # Tratamento de sinais
│   │   └── signals.c
│   ├── utils/            # Funções auxiliares (strings, free, etc)
│   │   ├── str_utils.c
│   │   ├── free_utils.c
│   │   └── error.c
├── lib/                  # Bibliotecas (libft, readline, etc)
│   ├── libft/            # Sua lib personalizada
│   │   ├── *.c
│   │   └── *.h
│   └── readline/         # Headers do readline (symlink opcional)
│ 