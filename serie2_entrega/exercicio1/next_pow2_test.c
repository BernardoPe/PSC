#include <stdio.h>
#include <limits.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

const char *register_name[] = { "", "rbp", "rbx", "r15", "r14", "r13", "r12" };

int invoke_and_test(void *, void (*)(), int, ...);

extern size_t next_pow2(size_t x);

struct {
	size_t x;
	size_t result;
} test_array[] = {
	{0, 0},
	{4, 4},
	{23, 32},
	{1 << 10, 1 << 10},
	{(1 << 10) + 1, 1 << 11},
	{1UL << ((sizeof test_array[0].x * CHAR_BIT) - 1), 1UL << ((sizeof test_array[0].x * CHAR_BIT) - 1) },
	{(1UL << ((sizeof test_array[0].x * CHAR_BIT) - 1)) + 1, 0 },
};

int main() {
	for (size_t i = 0; i < ARRAY_SIZE(test_array); i++) {
		size_t received_result;
		int result = invoke_and_test(&received_result,
				(void (*)())next_pow2, 1, test_array[i].x);
		if (result != 0) {
			printf("Your function currupted %s, that is a calee saved register\n",
							register_name[result]);
			break;
		}
		if (received_result != test_array[i].result)
			printf("[%zu] Expected: %zx, receiced: %zx\n", i,
				test_array[i].result, received_result);
	}
}

