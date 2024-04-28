/*
 *	Programação em Sistemas Computacionais
 *	Semestre de inverno de 2023/2024
 *	Primeira série de exercícios
 *
 *	Programa de teste do 1º exercício
 *
 *	Utilização:
 *
 *	$ gcc max_value_test.c max_value.c -o max_value_test -g -Wall -pedantic
 *
 *	$ ./max_value_test
 */

#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

unsigned long max_value(unsigned nchars);

struct {
	int nchars;
	unsigned long result_value;
} test_array[] = {
	{.nchars = 0, .result_value = 0UL},
	{.nchars = 1, .result_value = 127UL},
	{.nchars = 2, .result_value = 32767UL},
	{.nchars = 3, .result_value = 8388607UL},
	{.nchars = 4, .result_value = 2147483647UL},
	{.nchars = 5, .result_value = 549755813887UL},
	{.nchars = 6, .result_value = 140737488355327UL},
	{.nchars = 7, .result_value = 36028797018963967UL},
	{.nchars = 8, .result_value = 9223372036854775807UL},
	{.nchars = 9, .result_value = 0},
	{.nchars = 10, .result_value = 0},
};

int error;

void print_result(int i, size_t result_value) {
	if (result_value != test_array[i].result_value) {
		printf("[%d] - Error, expected value = %ld, returned value = %ld\n",
			i, test_array[i].result_value, result_value);
		error = 1;
	}
	else
		printf("[%d] - OK\n", i);
}

int main() {
	for (int i = 0; i < ARRAY_SIZE(test_array); ++i) {
		unsigned long result = max_value(test_array[i].nchars);
		print_result(i, result);
	}
	return error;
}

