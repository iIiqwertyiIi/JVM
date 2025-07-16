/**
 * @file class_file.h
 * @brief arquivo cabecalho das instrucoes de leitura, retorno e desalocacao de memoria do class_file lido pela JVM
 * @author Nicolas Paulin
 * @see class_file.c
 */

#ifndef CLASS_FILE_H
#define CLASS_FILE_H
#include "types.h"
#include "reader.h"
#include "field_reader.h"
#include "method_info.h"
#include "constant_pool.h"
#include "attribute_info.h" 

/**
 * @brief Funcao responsável pela leitura do class-file lido pela JVM
 * @return ponteiro para ClassFile
 * @see read_class_file() implemetacao (em class_file.c)
 */
ClassFile * read_class_file();

/**
 * @brief recupera buffer do arquivo classFile lido inicialmente pela JVM, com todas as suas informacoes
 * @return Buffer arquivo ClassFile
 * @see get_class_file_buffer() implemetacao (em class_file.c)
 */
ClassFileBuffer * get_class_file_buffer();

/**
 * @brief desaloca informacoes da classFile lidas pela JVM
 * @see free_class_file() implemetacao (em class_file.c)
 */
void free_class_file(ClassFile* class_file);
void pushToClassFileList(ClassFile * class_file);

void setup_static_fields(ClassFile * class_file);

#endif