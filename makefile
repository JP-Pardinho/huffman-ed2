CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lm

# Arquivos objeto
OBJS = huffman.o heap.o
MAIN_OBJ = main.o
TEST_OBJ = test.o

# Nomes dos executáveis
EXEC = huffman
TEST_EXEC = test_runner

# Alvo padrão
all: $(EXEC)

# Compilar o executável principal
$(EXEC): $(MAIN_OBJ) $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(MAIN_OBJ) $(OBJS) $(LDFLAGS)

# Compilar o executável de testes
$(TEST_EXEC): $(TEST_OBJ) $(OBJS)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_OBJ) $(OBJS) $(LDFLAGS)

# Compilar main.c
main.o: main.c huffman.h heap.h
	$(CC) $(CFLAGS) -c main.c

# Compilar huffman.c
huffman.o: huffman.c huffman.h heap.h
	$(CC) $(CFLAGS) -c huffman.c

# Compilar heap.c
heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c

# Compilar test.c
test.o: test.c huffman.h heap.h
	$(CC) $(CFLAGS) -c test.c

# Executar o programa principal
run: $(EXEC)
	./$(EXEC)

# Compilar e executar testes
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Limpar arquivos objeto e executáveis
clean:
	rm -f $(OBJS) $(MAIN_OBJ) $(TEST_OBJ) $(EXEC) $(TEST_EXEC)

# Recompilar tudo
rebuild: clean all

# Recompilar tudo com testes
rebuild-test: clean all test

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make          - compila o projeto principal"
	@echo "  make run      - compila e executa o programa"
	@echo "  make test     - compila e executa os testes"
	@echo "  make clean    - remove arquivos compilados"
	@echo "  make rebuild  - limpa e recompila"
	@echo "  make rebuild-test - limpa e recompila com testes"
	@echo "  make help     - mostra esta mensagem"

.PHONY: all run test clean rebuild rebuild-test help