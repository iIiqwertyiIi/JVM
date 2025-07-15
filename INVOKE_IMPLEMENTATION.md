# Implementação das Instruções de Chamada de Métodos

## Visão Geral

Esta implementação adiciona suporte às quatro principais instruções de chamada de métodos da JVM:

- **invokevirtual** (0xb6): Chama métodos de instância com despacho dinâmico
- **invokespecial** (0xb7): Chama métodos especiais (construtores, métodos privados)
- **invokestatic** (0xb8): Chama métodos estáticos
- **invokeinterface** (0xb9): Chama métodos de interface

## Arquivos Adicionados

### method_invocation.h
Contém as declarações das funções e estruturas necessárias:
- `ResolvedMethod`: Estrutura para armazenar informações de métodos resolvidos
- Funções de resolução de métodos
- Funções de execução de métodos
- Funções para as instruções invoke

### method_invocation.c
Implementação completa das funcionalidades:
- Resolução de métodos em hierarquias de classes
- Criação e gerenciamento de frames
- Execução de métodos
- Implementação das quatro instruções invoke

## Funcionalidades Implementadas

### 1. Resolução de Métodos
- **resolve_method()**: Resolve MethodRef do constant pool
- **resolve_interface_method()**: Resolve InterfaceMethodRef
- **find_method_in_class()**: Encontra método em uma classe específica
- **find_method_in_superclass()**: Procura método na hierarquia de superclasses

### 2. Gerenciamento de Frames
- **create_frame()**: Cria novo frame para execução de método
- **push_frame()**: Empilha frame na pilha de execução
- **pop_frame()**: Desempilha frame da pilha de execução

### 3. Utilitários
- **get_utf8_string()**: Obtém strings UTF-8 do constant pool
- **get_class_name()**: Obtém nomes de classes do constant pool

### 4. Instruções Invoke
- **invokevirtual()**: Implementa invokevirtual
- **invokespecial()**: Implementa invokespecial
- **invokestatic()**: Implementa invokestatic
- **invokeinterface()**: Implementa invokeinterface

## Como Funciona

### Fluxo de Execução

1. **Decodificação**: A instrução é decodificada para obter o índice do método no constant pool
2. **Resolução**: O método é resolvido usando as informações do constant pool
3. **Preparação**: Um novo frame é criado para o método chamado
4. **Execução**: O método é executado no novo frame
5. **Retorno**: O resultado é copiado de volta para o frame original

### Exemplo de Uso

```java
public class Test {
    public static void main(String[] args) {
        Test t = new Test();
        t.instanceMethod();  // invokevirtual
        staticMethod();      // invokestatic
    }
    
    public void instanceMethod() {
        // código do método
    }
    
    public static void staticMethod() {
        // código do método estático
    }
}
```

## Integração com o Sistema Existente

### Modificações nos Arquivos Existentes

1. **instructions.h**: Adicionado include para method_invocation.h
2. **instructions.c**: Conectadas as funções invoke às suas respectivas instruções
3. **makefile**: Adicionados os novos arquivos ao build

### Estruturas Utilizadas

- **ClassFile**: Para informações da classe
- **method_info**: Para informações do método
- **Frame**: Para execução do método
- **OperandStack**: Para pilha de operandos
- **cp_info**: Para constant pool

## Limitações Atuais

1. **Execução Simplificada**: A função `execute_method()` é um placeholder
2. **Gerenciamento de Argumentos**: Transferência de argumentos entre frames não está completamente implementada
3. **Valores de Retorno**: Tratamento de valores de retorno é simplificado
4. **Carregamento de Classes**: Depende da função `get_class_file()` existente

## Próximos Passos

Para completar a implementação, seria necessário:

1. **Implementar execute_method()**: Loop principal de execução de bytecode
2. **Gerenciar Argumentos**: Transferir argumentos corretamente entre frames
3. **Tratar Retornos**: Implementar instruções de retorno (ireturn, lreturn, etc.)
4. **Carregamento Dinâmico**: Melhorar o carregamento de classes
5. **Tratamento de Erros**: Adicionar verificações de segurança

## Testando

Para testar a implementação:

1. Compile uma classe Java com chamadas de métodos
2. Use a JVM para carregar e analisar o arquivo .class
3. Verifique se as instruções invoke são reconhecidas corretamente

```bash
javac TestInvoke.java
./jvm_viewer TestInvoke.class
```

## Compatibilidade

Esta implementação é compatível com:
- ✅ Estrutura de dados existente
- ✅ Sistema de instruções atual
- ✅ Constant pool
- ✅ Operand stack
- ✅ Variáveis locais

A implementação foi projetada para se integrar perfeitamente com o código existente da sua JVM. 