# Configurações do compilador
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
TARGET = jvm_viewer

# Diretórios
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = .

# Arquivos fonte
SRCS = reader.c \
       constant_pool.c \
       field_reader.c \
       method_info.c \
       attribute_info.c \
       output.c \
       class_file.c \
       helper.c \
       stack_operations.c \
	   logic_instructions.c \
	   arithmetic_instructions.c \
	   main.c \

# Arquivos objeto
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Headers
HEADERS = types.h \
          reader.h \
          constant_pool.h \
          field_reader.h \
          method_info.h \
          attribute_info.h \
          output.h \
          class_file.h \
          helper.h \
          stack_operations.h \
		  logic_instructions.h \
		  arithmetic_instructions.h \

# Regra principal
all: directories $(TARGET)

# Criar diretórios necessários
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Compilar o executável
$(TARGET): $(OBJS)
	@echo "Linkando $@..."
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/$(TARGET) $(OBJS) -lm
	@echo "Build completo! Executável: $(BIN_DIR)/$(TARGET)"

# Regra genérica para compilar arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "Compilando $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Regras específicas para dependências

$(OBJ_DIR)/reader.o: reader.c reader.h types.h
	@echo "Compilando reader.c..."
	@$(CC) $(CFLAGS) -c reader.c -o $@

$(OBJ_DIR)/constant_pool.o: constant_pool.c constant_pool.h types.h reader.h
	@echo "Compilando constant_pool.c..."
	@$(CC) $(CFLAGS) -c constant_pool.c -o $@

$(OBJ_DIR)/field_reader.o: field_reader.c field_reader.h types.h reader.h
	@echo "Compilando field_reader.c..."
	@$(CC) $(CFLAGS) -c field_reader.c -o $@

$(OBJ_DIR)/method_info.o: method_info.c method_info.h types.h reader.h attribute_info.h
	@echo "Compilando method_info.c..."
	@$(CC) $(CFLAGS) -c method_info.c -o $@

$(OBJ_DIR)/attribute_info.o: attribute_info.c attribute_info.h types.h reader.h
	@echo "Compilando attribute_info.c..."
	@$(CC) $(CFLAGS) -c attribute_info.c -o $@

$(OBJ_DIR)/output.o: output.c output.h types.h
	@echo "Compilando output.c..."
	@$(CC) $(CFLAGS) -c output.c -o $@

$(OBJ_DIR)/class_file.o: class_file.c class_file.h types.h reader.h constant_pool.h field_reader.h method_info.h attribute_info.h
	@echo "Compilando class_file.c..."
	@$(CC) $(CFLAGS) -c class_file.c -o $@
	
$(OBJ_DIR)/main.o: main.c reader.h class_file.h output.h
	@echo "Compilando main.c..."
	@$(CC) $(CFLAGS) -c main.c -o $@

$(OBJ_DIR)/helper.o: helper.c helper.h types.h
	@echo "Compilando helper.c..."
	@$(CC) $(CFLAGS) -c helper.c -o $@

$(OBJ_DIR)/stack_operations.o: stack_operations.c stack_operations.h types.h helper.h
	@echo "Compilando stack_operations.c..."
	@$(CC) $(CFLAGS) -c stack_operations.c -o $@

$(OBJ_DIR)/logic_instructions.o: logic_instructions.c logic_instructions.h types.h
	@echo "Compilando logic_instructions.c..."
	@$(CC) $(CFLAGS) -c logic_instructions.c -o $@

$(OBJ_DIR)/arithmetic_instructions.o: arithmetic_instructions.c arithmetic_instructions.h types.h
	@echo "Compilando arithmetic_instructions.c..."
	@$(CC) $(CFLAGS) -c arithmetic_instructions.c -o $@

# Limpeza
clean:
	@echo "Limpando arquivos objeto e executável..."
	@rm -rf $(OBJ_DIR)
	@rm -f $(BIN_DIR)/$(TARGET)
	@echo "Limpeza completa!"

# Limpeza profunda (inclui arquivos de teste)
distclean: clean
	@echo "Removendo arquivos .class de teste..."
	@rm -f *.class
	@echo "Limpeza profunda completa!"

# Compilar classe Java de teste
test-java:
	@echo "Compilando classes Java de teste..."
	@javac Test.java 2>/dev/null || echo "Crie um arquivo Test.java para testar"
	@javac HelloWorld.java 2>/dev/null || echo "HelloWorld.java não encontrado"
	@javac TestFields.java 2>/dev/null || echo "TestFields.java não encontrado"
	@echo "Classes Java compiladas!"

# Executar teste básico
test: $(TARGET) test-java
	@echo "\n=== Testando com Test.class ===\n"
	@if [ -f Test.class ]; then \
		./$(TARGET) Test.class; \
	else \
		echo "Arquivo Test.class não encontrado. Execute 'make test-java' primeiro."; \
	fi

# Executar com valgrind para detectar vazamentos de memória
memcheck: $(TARGET)
	@echo "Executando com valgrind..."
	@valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) Test.class

# Executar com um arquivo específico
run: $(TARGET)
	@if [ -z "$(FILE)" ]; then \
		echo "Uso: make run FILE=arquivo.class"; \
	else \
		./$(TARGET) $(FILE); \
	fi

# Debug com gdb
debug: $(TARGET)
	@if [ -z "$(FILE)" ]; then \
		echo "Uso: make debug FILE=arquivo.class"; \
	else \
		gdb --args ./$(TARGET) $(FILE); \
	fi

# Verificar sintaxe
syntax-check:
	@echo "Verificando sintaxe dos arquivos C..."
	@for file in $(SRCS); do \
		$(CC) $(CFLAGS) -fsyntax-only $$file && echo "✓ $$file" || echo "✗ $$file"; \
	done

# Contar linhas de código
count:
	@echo "Contagem de linhas de código:"
	@echo "Headers (.h):"
	@wc -l *.h | tail -1
	@echo "\nImplementações (.c):"
	@wc -l *.c | tail -1
	@echo "\nTotal:"
	@wc -l *.h *.c | tail -1

# Gerar documentação (requer doxygen)
docs:
	@echo "Gerando documentação..."
	@doxygen Doxyfile 2>/dev/null || echo "Doxygen não encontrado ou Doxyfile não configurado"

# Ajuda
help:
	@echo "JVM Class File Viewer - Makefile"
	@echo "================================"
	@echo "Comandos disponíveis:"
	@echo "  make              - Compila o projeto"
	@echo "  make clean        - Remove arquivos objeto e executável"
	@echo "  make distclean    - Remove tudo incluindo .class de teste"
	@echo "  make test-java    - Compila classes Java de teste"
	@echo "  make test         - Compila e executa teste básico"
	@echo "  make memcheck     - Executa com valgrind"
	@echo "  make run FILE=x   - Executa com arquivo específico"
	@echo "  make debug FILE=x - Debug com gdb"
	@echo "  make syntax-check - Verifica sintaxe dos arquivos"
	@echo "  make count        - Conta linhas de código"
	@echo "  make help         - Mostra esta ajuda"
	@echo ""
	@echo "Exemplo de uso:"
	@echo "  make clean && make"
	@echo "  make run FILE=MinhaClasse.class"

# Instalar (opcional)
install: $(TARGET)
	@echo "Instalando em /usr/local/bin..."
	@sudo cp $(TARGET) /usr/local/bin/
	@echo "Instalação completa!"

# Desinstalar (opcional)
uninstall:
	@echo "Removendo de /usr/local/bin..."
	@sudo rm -f /usr/local/bin/$(TARGET)
	@echo "Desinstalação completa!"

# Arquivo .PHONY para indicar que não são arquivos reais
.PHONY: all clean distclean test test-java memcheck run debug \
        syntax-check count docs help install uninstall directories