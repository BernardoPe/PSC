#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <glib.h>

typedef struct 
{
    GHashTable * hash_table;
} Dictionary;


/** Criar e inicializar uma variável struct Dictionary */
Dictionary *dictionary_create();


/** Adicionar ao dicionário o conjunto de palavras presentes no ficheiro indicado */
void dictionary_add(Dictionary *dictionary, const char *filename);


/** Verifica se o dicionário contém a palavra indicada */
int dictionary_lookup(Dictionary *dictionary, const char *word);


/** Liberta os recursos associados ao dicionário */
void dictionary_destroy(Dictionary *dictionary);


#endif 