/*
 *	Programação em Sistemas Computacionais
 *	Semestre de inverno de 2023/2024
 *	Primeira série de exercícios
 *
 *	Programa de teste do 3º exercício
 *
 *	Utilização:
 *
 *	$ gcc string_split_test.c string_split.c -o string_split_test -g -Wall -pedantic
 *
 *	$ ./bits_test
 */

#include <stdio.h>
#include <string.h>

size_t string_split(char *text, char *separators, char *words[], size_t words_size);

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

int error;

struct {
	char text[100];
	char *text_ptr;
	size_t result_size;
	char *words[4];
} test_array[] = {
	{ "aaa bbb ccc ddd", test_array[0].text, 4,
		{test_array[0].text, test_array[0].text + 4, test_array[0].text + 8, test_array[0].text + 12} },
	{ "aaa bbb ccc  ddd ", test_array[1].text, 4,
		{test_array[1].text, test_array[1].text + 4, test_array[1].text + 8, test_array[1].text + 13} },
	{ "aaa\tbbb ccc ddd", test_array[2].text, 4,
		{test_array[2].text, test_array[2].text + 4, test_array[2].text + 8, test_array[2].text + 12} },
	{ "aaa", test_array[3].text, 1,
		{test_array[3].text} },
	{ "", test_array[4].text, 0,
		{test_array[4].text} },
	{ "   \taaa\tbbb ccc        ", test_array[5].text, 3,
		{test_array[5].text + 4, test_array[5].text + 8, test_array[5].text + 12} },
	{ "aaa bbb ccc ddd eee", test_array[6].text, 4,
		{test_array[6].text, test_array[6].text + 4, test_array[6].text + 8, test_array[6].text + 12} },
	{ "", NULL , 1,
		{test_array[6].text + 16} },
};

void print_result(int i, char *words[], size_t nwords) {
	if (nwords != test_array[i].result_size) {
		printf("[%d] - Error, expected = %zd, returned %zd\n", i, test_array[i].result_size, nwords);
		error = 1;
	}
	else {
		for (size_t n = 0; n < nwords; n++) {
			if (strcmp(words[n], test_array[i].words[n]) != 0) {
				printf("[%d] - Error, expected = %s, returned %s\n", i, test_array[i].words[n], words[n]);
				error = 1;
				goto break2;
			}
		}
		printf("[%d] - OK\n", i);
	}
	break2:;
}

int main() {
	for (int i = 0; i < ARRAY_SIZE(test_array); ++i) {
		char *words[ARRAY_SIZE(test_array[0].words)];
		size_t nwords = string_split(test_array[i].text_ptr, " \t\n", words, ARRAY_SIZE(words));
		print_result(i, words, nwords);
	}
}


