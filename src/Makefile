# Nome do compilador C
CC = gcc

# Flags de compilação:
# -Wall: Ativa todos os avisos do compilador (altamente recomendado)
# -Wextra: Ativa avisos extras
# -g: Gera informações de depuração (para usar com gdb)
# -O2: Otimização de nível 2 para o código final
CFLAGS = -Wall -Wextra -g -O2

# Flags de linkagem:
# -lm: Vincula a biblioteca matemática (necessária para math.h)
LDFLAGS = -lm

# Nome do executável final
TARGET = ted

# Encontra automaticamente todos os arquivos fonte .c no diretório atual
SRCS = $(wildcard *.c)

# Gera os nomes dos arquivos objeto (.o) a partir dos arquivos fonte (.c)
OBJS = $(SRCS:.c=.o)

# O alvo padrão (executado quando você digita 'make')
.PHONY: all
all: $(TARGET)

# Regra para linkar o programa final a partir dos arquivos objeto
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Regra para compilar arquivos .c em arquivos .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Alvo para limpar os arquivos gerados (executável e objetos)
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)