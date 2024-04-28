#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

#define MAX_LINE_LENGTH 1024
#define MAX_COLUMN_LENGTH 256

int main(int argc, char *argv[]) {
    FILE *input_file = stdin;
    FILE *output_file = stdout;
    char *search_pattern = NULL;
    int column = -1;
    int case_sensitive = 0;
    char line[MAX_LINE_LENGTH];
    char input_file_path[MAX_LINE_LENGTH];
    int c;
   
    char *csv_filter_path = getenv("CSV_FILTER_PATH");

    if (csv_filter_path == NULL) {
        csv_filter_path = ".";
    }
    //get input and output files, check if the matches are case sensitive or not 
    while ((c = getopt(argc, argv, "i:o:c")) != -1) {
        switch (c) {
            case 'i':
                snprintf(input_file_path, sizeof(input_file_path), "%s/%s", csv_filter_path, optarg); //create input file path
                input_file = fopen(input_file_path, "r");
                if (!input_file) {
                    printf("Erro ao abrir ficheiro de entrada\n");
                    return 1;
                }
                break;
            case 'o':
                output_file = fopen(optarg, "w");
                if (!output_file) {
                    //close input file if there was an error with the output file
                    printf("Erro ao abrir ficheiro de saída\n");
                    if (input_file != stdin) fclose(input_file);
                    return 1;
                }
                break;
            case 'c':
                case_sensitive = 1;
                break;
            default:
                printf("Uso: %s -i <input_file> -o <output_file> -c <column> <pattern>\n", argv[0]);
                return 1;
        }
    }

    column = (*argv[optind] - '0');
    search_pattern = argv[optind + 1];
    char delimiter = ',';
    
   while (fgets(line, sizeof(line), input_file)) {
        char *line_copy = strdup(line);
        char *word = strtok(line_copy, &delimiter);
        int current_column = 1;
        //split the line, iterate through the columns while looking for a match, if a match is found the line is written to the output file
        while (word != NULL) {
            if (current_column == column) {
                if (!case_sensitive) {
                    for (int i = 0; search_pattern[i] != '\0'; i++) {
                        search_pattern[i] = tolower(search_pattern[i]);
                        word[i] = tolower(word[i]);
                    }
                }

                if (strcmp(word, search_pattern) == 0) {
                    fputs(line, output_file); 
                }
                
            }

            word = strtok(NULL, &delimiter);
            current_column++;
        }
   }


    if (input_file != stdin) {
        fclose(input_file);
    }

    if (output_file != stdout) {
        fclose(output_file);
    }

    return 0;
}
