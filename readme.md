# Objetivo do trabalho
Projeto disciplina Software Básico da Universidade de Brasília com objetivo de simular funcionamento de uma máquina java virtual (**Java**)

## Como rodar projeto
Dentro do diretório do projeto, rode:
`make clean`
Para apagar registros antigos

Então, rode:
`make` para criar arquivo leitor exibidor

E, por fim:
`./jvm_viewer exemplos/nome_arquivo.class `

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

`logic_instructions` e `arithmertic_instructions`
Possui todas as instruções lógicas e aritméticas implementadas na JVM.

`conversions.c` e `helpers.c`
Arquivos responsáveis pela conversões de tipos, como *long to double*, por exemplo.