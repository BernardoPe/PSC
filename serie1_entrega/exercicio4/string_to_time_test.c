/*
 *	Programação em Sistemas Computacionais
 *	Semestre de inverno de 2023/2024
 *	Primeira série de exercícios
 *
 *	Programa de teste do 4º exercício
 *
 *	Utilização:
 *
 *	$ gcc string_to_time_test.c string_to_time.c -o string_to_time_test -g -Wall -pedantic
 *
 *	$ ./string_to_time_test
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

struct {
	char *string_time;
	int result;
	struct tm tm;
} test_array[] = {
	{.string_time = "11-09-2023 13:43:45", 1,
		.tm = {.tm_mday = 11, .tm_mon = 8, .tm_year = 123,
				.tm_hour = 13, .tm_min = 43, .tm_sec = 45 }},
	{.string_time = "11/9-2023 13:43:45", 0},
	{.string_time = "11-9-2023 13:43", 0},
};

int error;

void print_result(int i, int result, struct tm *tm) {
	if (result != test_array[i].result) {
		printf("[%d] - Error, expected value = %d, returned value = %d\n",
			i, test_array[i].result, result);
		error = 1;
	}
	else if (result == 1) {
		if (tm->tm_mday != test_array[i].tm.tm_mday) {
			printf("[%d] - Error, expected = tm_mday = %d, returned tm_mday = %d\n",
				i, test_array[i].tm.tm_mday, tm->tm_mday);
			error = 1;
			goto break2;
		}
		if (tm->tm_mon != test_array[i].tm.tm_mon) {
			printf("[%d] - Error, expected = tm_mon = %d, returned tm_mon = %d\n",
				i, test_array[i].tm.tm_mon, tm->tm_mon);
			error = 1;
			goto break2;
		}
		if (tm->tm_year != test_array[i].tm.tm_year) {
			printf("[%d] - Error, expected = tm_year = %d, returned tm_year = %d\n",
				i, test_array[i].tm.tm_year, tm->tm_year);
			error = 1;
			goto break2;
		}
		if (tm->tm_hour != test_array[i].tm.tm_hour) {
			printf("[%d] - Error, expected = tm_hour = %d, returned tm_hour = %d\n",
				i, test_array[i].tm.tm_hour, tm->tm_hour);
			error = 1;
			goto break2;
		}
		if (tm->tm_min != test_array[i].tm.tm_min) {
			printf("[%d] - Error, expected = tm_min = %d, returned tm_min = %d\n",
				i, test_array[i].tm.tm_min, tm->tm_min);
			error = 1;
			goto break2;
		}
		if (tm->tm_sec != test_array[i].tm.tm_sec) {
			printf("[%d] - Error, expected = tm_sec = %d, returned tm_sec = %d\n",
				i, test_array[i].tm.tm_sec, tm->tm_sec);
			error = 1;
			goto break2;
		}
		printf("[%d] - OK\n", i);
	}
	else
		printf("[%d] - OK\n", i);
	break2:;
}

int string_to_time(const char *string, struct tm *tm);

int main() {
	for (int i = 0; i < ARRAY_SIZE(test_array); ++i) {
		struct tm tm;
		int result = string_to_time(test_array[i].string_time, &tm);
		print_result(i, result, &tm);
	}
	return error;
}

