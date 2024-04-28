#include <stdio.h>

#include "struct_values.h"

const char *register_name[] = { "", "rbp", "rbx", "r15", "r14", "r13", "r12" };

int invoke_and_test(void *, void (*)(), int, ...);

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

static short offset0[] = { 10, 20, 30, 40, 50 };
static short offset1[] = { 100, 200, 300, 400, 500 };
static short offset2[] = { 1000, 2000, 3000, 4000, 5000 };
static short offset3[] = { 10, 200, 3000, 400, 50 };

struct values values0[] = {
	{ .len = ARRAY_SIZE(offset0), .offset = offset0 },
	{ .len = ARRAY_SIZE(offset1), .offset = offset1 },
	{ .len = ARRAY_SIZE(offset2), .offset = offset2 },
};
struct values values1[] = {
	{ .len = ARRAY_SIZE(offset0), .offset = offset0 },
	{ .len = ARRAY_SIZE(offset1), .offset = offset1 },
	{ .len = ARRAY_SIZE(offset2), .offset = offset2 },
};

struct values values2[] = {
	{ .len = ARRAY_SIZE(offset0), .offset = offset0 },
	{ .len = ARRAY_SIZE(offset1), .offset = offset1 },
	{ .len = ARRAY_SIZE(offset2), .offset = offset2 },
};

struct values *values[] = { values0, values1, values2 };

struct {
	struct values **values;
	struct values ref;
	int i, j, k, expected_result;
} test_array[] = {
	{.values = values, .ref = {.len = ARRAY_SIZE(offset0), .offset = offset0},
		.i = 0, .j = 0, .k = 100, .expected_result = 0},
	{.values = values, .ref = {.len = ARRAY_SIZE(offset0), .offset = offset0},
		.i = 0, .j = 1, .k = 1, .expected_result = 0},
	{.values = values, .ref = {.len = ARRAY_SIZE(offset0), .offset = offset0},
		.i = 0, .j = 0, .k = 0, .expected_result = 1},
	{.values = values, .ref = {.len = ARRAY_SIZE(offset2), .offset = offset2},
		.i = 0, .j = 0, .k = 0, .expected_result = 0},
	{.values = values, .ref = {.len = ARRAY_SIZE(offset2), .offset = offset2},
		.i = 2, .j = 2, .k = 2, .expected_result = 1},
	{.values = values, .ref = {.len = ARRAY_SIZE(offset3), .offset = offset3},
		.i = 2, .j = 2, .k = 2, .expected_result = 1},
	{.values = values, .ref = {.len = ARRAY_SIZE(offset3), .offset = offset3},
		.i = 1, .j = 1, .k = 3, .expected_result = 1},
};

int compare_offset(struct values *values[], int i, int j, int k, struct values *avalue);

int main() {
	for (size_t i = 0; i < ARRAY_SIZE(test_array); i++) {
		int received_result;
		int result = invoke_and_test(&received_result, (void (*)())compare_offset,
					5, test_array[i].values, test_array[i].i, test_array[i].j, test_array[i].k, &test_array[i].ref);
		if (result != 0) {
			printf("Your function currupted %s, that is a calee saved register\n",
				register_name[result]);
			break;
		}
		if (received_result != test_array[i].expected_result) {
			printf("[%zd] - Received: %d Expected: %d\n",
				i, received_result, test_array[i].expected_result);
		}
	}
}
