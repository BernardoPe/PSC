#include "structs/dictionary.h"
#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <glib.h>

#define MAX_LINE_LEN 2048

typedef struct textCoords
{
    int line;
    int col;
} TextCoords;

void printIncorrectWords(const char *filename, Dictionary *dictionary, char* search_word);


#include <time.h>

#include <time.h>

int main(int argc, char **argv) {
    int opt;
    
    char *t = NULL;
    char *w = NULL;

    Dictionary *dictionary = dictionary_create();

    while ((opt = getopt(argc, argv, "d:t:w:")) != -1) {
        switch (opt) {
            case 'd':
                dictionary_add(dictionary, optarg);
                break;
            case 't':
                t = optarg;
                break;
            case 'w':
                w = optarg;
                break;
            default:
                fprintf(stderr, "Uso: %s -d <dictionary_file> [-d <additional_dictionary_file> ...] (-t <text_file> | -w <word>)\n", argv[0]);
                dictionary_destroy(dictionary);
                return 1;
        }
    }
    
    clock_t start = clock();
    printIncorrectWords(t, dictionary, w);
    clock_t end = clock();
    
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC * 1000; // in milliseconds

    printf("printIncorrectWords() took %f milliseconds to execute \n", time_taken);

    dictionary_destroy(dictionary);

    return 0;
}

void free_list(gpointer data) {
    GList *list = data;
    while (list != NULL) {
        GList *next = list->next;
        free(list->data);
        free(list);
        list = next;
    }
}

void printIncorrectWords (const char *filename, Dictionary *dictionary, char* search_word) {

    if (filename != NULL && search_word != NULL)
    {
        fprintf(stderr, "Erro: Opções -t and -w não podem ser usadas simultaneamente.\n");
        return;
    }

    if (filename == NULL && search_word == NULL)
    {
        fprintf(stderr, "Erro: Deve ser fornecido um ficheiro de texto ou uma palavra a pesquisar.\n");
    }

    if (search_word != NULL)
    {
        if (dictionary_lookup(dictionary, search_word)) {
            printf("Palavra '%s' encontrada no dicionário.\n", search_word);
        }
        else {
            printf("Palavra '%s' não encontrada no dicionário.\n", search_word);
        }
        return;
    }
    

    FILE *file = fopen(filename,"r");

    if (file == NULL){
        fprintf(stderr, "Erro: Não foi possível abrir o ficheiro %s\n", filename);
        return;
    }
    
    const char delimiters[] = " \t\n.,;:!?\"()'[]{}<>&^%$#@+-=*/";
    
    GHashTable *map = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    
    int current_line = 1;
    int current_col;
    char line[MAX_LINE_LEN];

    GList *words_list = NULL; // list of words that are not in the dictionary ordered by appearance in the text
       
    while (fgets(line, sizeof(line), file) != NULL) {
        
        size_t len = strlen(line);
    
        while (len > 0 && isspace(line[len - 1])) {
            line[--len] = ' ';
        }

        current_col = 0;
        char *token = strtok(line, delimiters);

        while (token != NULL) {

            char *word = g_strdup(token);  
            size_t len = strlen(word);

            if (!dictionary_lookup(dictionary, word) && len > 0) {  

                TextCoords *coords = g_new(TextCoords, 1);
                coords->line = current_line;
                coords->col = current_col;

                if (g_hash_table_contains(map, word)) {
                    GList *list = g_hash_table_lookup(map, word);
                    list = g_list_prepend(list, coords); 
                    g_hash_table_insert(map, word, list);
                } else {
                    words_list = g_list_prepend(words_list, word); 
                    GList *newList = NULL; 
                    newList = g_list_prepend(newList, coords); 
                    g_hash_table_insert(map, word, newList);
                }    
            }
            token = strtok(NULL, delimiters);
            current_col += len + 1;
        }

        current_line++;

    }

    GList *words_list_iterator = g_list_last(words_list); // iterate in reverse order

    while (words_list_iterator != NULL) {
        char *word = words_list_iterator->data;
        GList *coords_list = g_hash_table_lookup(map, word);
        if (coords_list != NULL)
        {
            printf("Palavra '%s' não encontrada nas seguintes posições:\n", word);
            GList *coords_list_iterator = g_list_last(coords_list);
            while (coords_list_iterator != NULL) {
                TextCoords *coords = coords_list_iterator->data;
                printf("Linha %d, Coluna %d\n", coords->line, coords->col);
                coords_list_iterator = g_list_previous(coords_list_iterator);
            }
            printf("\n");
        }
        words_list_iterator = g_list_previous(words_list_iterator);
    }

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, map);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        GList *coords_list = value;
        g_list_free_full(coords_list, g_free);
    }

    g_hash_table_destroy(map);

    g_list_free_full(words_list, g_free);

    fclose(file);

}

