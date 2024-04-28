#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LEN 100


/** Criar e inicializar uma variável struct Dictionary */
Dictionary *dictionary_create() {
    Dictionary *dictionary = g_new(Dictionary, 1);
    dictionary->hash_table = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
    return dictionary;
}


/** Adicionar ao dicionário o conjunto de palavras presentes no ficheiro indicado */
void dictionary_add(Dictionary *dictionary, const char *filename) {
    
    FILE *file = fopen(filename,"r");

    if (file == NULL){
        perror("At dictionary addition");
        return;
    }

    char word[MAX_WORD_LEN];

    while (fscanf(file, "%s", word) == 1) {
        g_hash_table_add(dictionary->hash_table, g_strdup(word));
    }


    fclose(file);

}


/** Verifica se o dicionário contém a palavra indicada */
int dictionary_lookup(Dictionary *dictionary, const char *word) {
    return g_hash_table_contains(dictionary->hash_table, word);
}


/** Liberta os recursos associados ao dicionário */
void dictionary_destroy(Dictionary *dictionary) {
    g_hash_table_destroy(dictionary->hash_table);
    g_free(dictionary);
}

