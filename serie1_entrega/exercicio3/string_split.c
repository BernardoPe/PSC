#include <stdio.h>
#include <string.h>

char *current_text = NULL;
size_t current_position = 0;

size_t string_split(char *text, char *separators, char *words[], size_t words_size) {

    if (text == NULL && current_text != NULL) {
        text = current_text + current_position; //get remaining text from last function call
    } else {
        current_position = 0;
        current_text = text;
    }

    size_t num_words = 0;
    char *word_start = text;

    while (*text != '\0') {
        
        //check if a delimiter was reached
        int is_separator = 0;
        for (size_t i = 0; separators[i] != '\0'; i++) { 
            if (*text == separators[i]) {
                is_separator = 1;
                break;
            }
        }
        //add word start pointer to array and set separator char to '\0'
        if (is_separator) { 
            *text = '\0';
            if (word_start != text) {
                words[num_words] = word_start;
                num_words++;
                //if the word limit has been reached, update the last position reached in the string and end the loop
                if (num_words == words_size) {
                    current_position = text - current_text + 1; 
                    return num_words;
                }
            }

            word_start = text + 1;
        }
        text++;
    }
    //last word in string might not have separator
    //if this happens, word_start and text pointers will not have same value
    if (word_start != text) {
        words[num_words] = word_start;
        num_words++;
    }

    current_position = text - current_text;

    return num_words;
}