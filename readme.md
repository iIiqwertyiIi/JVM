# Objetivo do trabalho
Projeto disciplina Software Básico da Universidade de Brasília com objetivo de simular funcionamento de uma máquina java virtual (**Java**)

## Como rodar projeto como interpretador
Dentro do diretório do projeto, rode:
`make clean`
Para apagar registros antigos

Então, rode:
`make` para criar arquivo leitor exibidor

E, por fim:
`./jvm_viewer exemplos/nome_arquivo.class `

## Como rodar projeto como leitor exibidor
Dentro do diretório do projeto, rode:
`make clean`
Para apagar registros antigos

Então, rode:
`make` para criar arquivo leitor exibidor

E, por fim:
`./jvm_viewer exemplos/nome_arquivo.class -show`

## Como acessar documentação
Dentro do terminal do projeto rode:
`doxygen Doxyfile`
depois vá até a pasta `docs/html` e copie o caminho do arquivo `index.html` e cole o resultado no navegador

## Alguns Arquivos importantes
`instruction.c`
Arquivo necessário com a listagem dos opcodes e das instruções através do método *get_instruction_type*
Também possui o método *add_to_stack* e *remove_from_stack* que lida com o empilhamento dos frames da JVM

`output.c`
Responsável pela impressão do leitor exibidor.

`reader.c`
Responsável pela leitura dos arquivos *.class*.

`types.c`
Define toda a tipagem e interface da JVM. Através desse arquivo, é possível visualizar e interagir com todo o projeto.

### O que cada membro fez
#### Ana Paula Nobrega - 190142120
- configuração makeFile
- instruções lógicas
- instruções leitura e desalocação de memória dos field_info
- slides apresentações

#### Eduardo Volpi - 190134330
- instruções de chamada de metodo (invoke)
- instruções de conversão de tipos
- instruções leitura e desalocação de memória para attribute_info

#### Gabriel Cruz - 200049038
- instruções leitura e desalocação de memória para method-info
- instruções auxiliares conversão de tipos signed para unsiged
- correção bugs e warnings de compilação
- documentação do código usando Doxygen
- distribuição das tarefas e organização do projeto

#### Tiago Buson - 200034162
- instruções de aritmética
- instruções tableswitch
- instruções lookupswitch

#### Nicolas Paulin - 200025627
- Estruturação geral dos tipos do projeto e arquitetura
- implementação adição e remoção pilha de frames
- implementação dicionário de instruções
- instrução de array e objetos da JVM
- instruções de de load e store
- instruções de return
- interpretador
- leitor de arquivo .class

