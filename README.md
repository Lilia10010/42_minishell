# 🐚 Minishell

> Uma implementação simplificada de um shell Unix para entender os fundamentos de como funciona um terminal

O **Minishell** simula a execução de comandos, gerenciamento de variáveis de ambiente e controle de processos, incluindo funcionalidades como pipes, redirecionamentos e comandos embutidos (builtins).

## 🏗️ Arquitetura

O projeto segue uma arquitetura em **pipeline** de 4 estágios:

```
Input → LEXER → PARSER → EXECUTOR → Output
```

---

## 1. 🔤 LEXER - Tokenização

**Função:** Quebra a linha de entrada em tokens (unidades significativas)

### Tipos de Tokens

| Token | Símbolo | Descrição |
|-------|---------|-----------|
| `WORD` | `comando` | Comandos, argumentos ou nomes de arquivos |
| `PIPE` | `\|` | Conecta saída de um comando à entrada de outro |
| `REDIRECT_IN` | `<` | Redireciona entrada de um arquivo |
| `REDIRECT_OUT` | `>` | Redireciona saída para arquivo (sobrescreve) |
| `REDIRECT_APPEND` | `>>` | Redireciona saída para arquivo (anexa) |
| `HEREDOC` | `<<` | Entrada de múltiplas linhas até delimitador |
| `STRING` | `"texto"` | Texto delimitado por aspas |
| `VARIABLE` | `$VAR` | Expande variáveis de ambiente |

### Exemplo
```bash
echo "Hello World" > output.txt
```
**Tokens gerados:**
- `WORD`: `echo`
- `STRING`: `"Hello World"`
- `REDIRECT_OUT`: `>`
- `WORD`: `output.txt`

---

## 2. 🌳 PARSER - Análise Sintática

**Função:** Organiza tokens em estruturas de dados coerentes e valida a sintaxe

- Cria **árvores de comandos**
- Identifica **argumentos** e **redirecionamentos**
- Valida **conexões entre pipes**
- Prepara estruturas para execução

### Exemplo de Estrutura
```bash
ls -la | grep ".txt" > results.txt
```

**Estrutura gerada:**
```
Command 1: [ls, -la] → pipe → Command 2: [grep, ".txt"] → redirect > results.txt
```

---

## 3. ⚡ EXECUTOR - Execução

**Função:** Executa os comandos preparados pelo parser

### Responsabilidades

- ✅ Verificar se é **builtin** ou **comando externo**
- ✅ Criar **processos filhos** para comandos externos
- ✅ Gerenciar **redirecionamentos** de I/O
- ✅ Criar **pipes** entre comandos
- ✅ Lidar com **sinais** (`CTRL+C`, `CTRL+D`)
- ✅ Controlar **códigos de saída**

---

## 4. 🔧 Builtins

Comandos implementados **dentro do shell** (sem criar novo processo)

| Comando | Função | Por que é builtin? |
|---------|--------|--------------------|
| `echo` | Imprimir texto | Controle preciso sobre flags (`-n`) |
| `cd` | Mudar diretório | Precisa alterar diretório do processo pai |
| `pwd` | Mostrar diretório atual | Acesso direto ao contexto do shell |
| `export` | Exportar variáveis | Modifica ambiente do shell |
| `unset` | Remover variáveis | Modifica ambiente do shell |
| `env` | Mostrar variáveis de ambiente | Acesso direto às variáveis internas |
| `exit` | Sair do shell | Encerra o processo principal |

### Exemplo de uso
```bash
minishell$ export MY_VAR="Hello"
minishell$ echo $MY_VAR
Hello
minishell$ cd /tmp
minishell$ pwd
/tmp
```

---

## 5. 🌐 Comandos Externos

Programas localizados no sistema (normalmente em `/bin`, `/usr/bin`, etc.)

### Exemplos Comuns
- `ls` - Listar arquivos
- `cat` - Mostrar conteúdo de arquivo
- `grep` - Buscar texto
- `mkdir` - Criar diretório
- `rm` - Remover arquivos
- `touch` - Criar arquivo vazio

### Como funciona
1. Shell busca o executável no **PATH**
2. Cria um **processo filho**
3. Executa o binário com **execve()**
4. Aguarda finalização e captura **código de saída**

---

## 🚀 Execução

```bash
# Compilar
make

# Executar
./minishell

# Exemplos de uso
minishell$ echo "Hello World"
minishell$ ls -la | grep ".c"
minishell$ cat file.txt > output.txt
minishell$ export PATH="/usr/bin:$PATH"
minishell$ exit
```


---

## 🎯 Status do Projeto

### ✅ Implementado
- [x] Lexer básico
- [x] Parser de comandos simples  
- [x] Executor de builtins
- [x] Builtin `echo`

### 🚧 Em Desenvolvimento
- [ ] Pipes
- [ ] Redirecionamentos
- [ ] Comandos externos com execve()
- [ ] Variáveis de ambiente
- [ ] Tratamento de sinais

### 📋 Próximos Passos
- [ ] Histórico de comandos
- [ ] Autocompletar
- [ ] Wildcards (`*`, `?`)
- [ ] Job control