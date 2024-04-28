/*
 *	Programação em Sistemas Computacionais
 *	Semestre de inverno de 2023/2024
 *	Primeira série de exercícios
 *
 *	Programa de teste do 2º exercício
 *
 *	Utilização:
 *
 *	$ gcc bits_test.c bits.c -o bits_test -g -Wall -pedantic
 *
 *	$ ./bits_test
 */

#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

unsigned long getbits(unsigned long data[], unsigned index, unsigned length);
void setbits(unsigned long data[], unsigned index, unsigned length, unsigned long val);

int error;

struct {
	unsigned long data[10];
	unsigned index, length;
	unsigned long result_value;
} getbits_test_array[] = {
	{.data = { 0xBFFFFFECABCD1234, 0xC, 2, 3 }, .index = 0, .length = 64, .result_value = 0xBFFFFFECABCD1234},
	{.data = { 0xBFFFFFECABCD1234, 0xC, 2, 3 }, .index = 192, .length = 1, .result_value = 0x1},
	{.data = { 0xBFFFFFECABCD1234, 0xC, 2, 3 }, .index = 0, .length = 8, .result_value = 0x34},
	{.data = { 0xBFFFFFECABCD1234, 0xC, 2, 3 }, .index = 64, .length = 8, .result_value = 0xc},
	{.data = { 0xBFFFFFECABCD1234, 0xC, 2, 3 }, .index = 29, .length = 8, .result_value = 0x65},
	{.data = { 0xBFFFFFECABCD1234, 0xC, 2, 3 }, .index = 60, .length = 8, .result_value = 0xcb},
	{.data = { 0xBFFFFFECABCD1234, 0xC, 2, 3 }, .index = 125, .length = 8, .result_value = 0x10},
};

void getbits_print_result(int i, unsigned long result_value) {
	if (result_value != getbits_test_array[i].result_value) {
		printf("[%d] - Error, expected value = %lx, returned value = %lx\n",
			i, getbits_test_array[i].result_value, result_value);
		error = 1;
	}
	else
		printf("[%d] - OK\n", i);
}

struct {
	unsigned long data[4];
	unsigned index, length;
	unsigned long value;
	unsigned long data_result[4];
} setbits_test_array[] = {
	{.data = { 0xBFFFFFECABCD1234, 0xC, 2, 3 }, .index = 16, .length = 8, .value = 0xff, .data_result = { 0xBFFFFFECABFF1234, 0xC, 2, 3 }},
	{.data = { 0xBFFFFFECABCD1234, 0xC, 2, 3 }, .index = 60, .length = 8, .value = 0xff, .data_result = { 0xFFFFFFECABCD1234, 0xF, 2, 3 }},
	{.data = { 0xBFFFFFECABCD1234, 0xC, 2, 3 }, .index = 191, .length = 8, .value = 0xff, .data_result = { 0xBFFFFFECABCD1234, 0xC, 0x8000000000000002, 0x7f }},
};

void setbits_print_result(int i, unsigned long data_result[], size_t data_result_size) {
	if (memcmp(setbits_test_array[i].data_result, data_result, data_result_size * sizeof data_result[0]) != 0) {
		printf("[%d] - Error, expected = [%lx", i, setbits_test_array[i].data_result[0]);
		for (unsigned j = 1; j < data_result_size; j++)
			printf(", %lx", setbits_test_array[i].data_result[j]);
		printf("], returned = [%lx", data_result[0]);
		for (unsigned j = 1; j < data_result_size; j++)
			printf(", %lx", data_result[j]);
		printf("]\n");
		error = 1;
	}
	else
		printf("[%d] - OK\n", i);
}

int main() {
	for (int i = 0; i < ARRAY_SIZE(getbits_test_array); ++i) {
		unsigned long result = getbits(getbits_test_array[i].data, getbits_test_array[i].index, getbits_test_array[i].length);
		getbits_print_result(i, result);
	}

	for (int i = 0; i < ARRAY_SIZE(setbits_test_array); ++i) {
		unsigned long data_result[ARRAY_SIZE(setbits_test_array[0].data)];
		memcpy(data_result, setbits_test_array[i].data, ARRAY_SIZE(data_result) * sizeof data_result[0]);
		setbits(data_result, setbits_test_array[i].index, setbits_test_array[i].length, setbits_test_array[i].value);
		setbits_print_result(i, data_result, ARRAY_SIZE(data_result));
	}
	return error;
}

