#include "../structs/dictionary.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <dictionary_file> <word_to_lookup>\n", argv[0]);
        return 1;
    }

    const char *dictionary_filename = argv[1];
    const char *word_to_lookup = argv[2];

    Dictionary *dictionary = dictionary_create();
    dictionary_add(dictionary, dictionary_filename);

    /** Verificação da presença da palavra no dicionario fornecido */
    if (dictionary_lookup(dictionary, word_to_lookup)) {
        printf("The word '%s' is in the dictionary.\n", word_to_lookup);
    } else {
        printf("The word '%s' is NOT in the dictionary.\n", word_to_lookup);
    }

    dictionary_destroy(dictionary);

    return 0;
    
}
