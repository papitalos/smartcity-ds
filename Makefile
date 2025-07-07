# Compilador
CC = gcc

# Nome do executável
TARGET = smartcity

# Arquivos fonte
SOURCES = Main.c Cliente.c Gestor.c Transporte.c Localizacao.c Grafo.c

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99

# Regra principal
all: $(TARGET)

# Compilar o executável
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

# Limpar arquivos gerados
clean:
	rm -f $(TARGET)

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Regra para debug
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)

.PHONY: all clean run debug 