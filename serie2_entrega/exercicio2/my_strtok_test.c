#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *my_strtok(char *str, const char *sep);

const char *register_name[] = { "", "rbp", "rbx", "r15", "r14", "r13", "r12" };

int invoke_and_test(void *, void (*)(), int, ...);


struct {
	char *seps;
	char text[100];
	char *text_ptr;
	char *token_ptr;

	size_t result_size;
	char *words[4];
} test_array[] = {
	{" \t\n","", test_array[0].text, NULL},
	{" \t\n","  aaa", test_array[1].text, test_array[1].text + 2},
	{" \t\n","  aaa", NULL, NULL},
	{" \t\n","aaa	bbb	", test_array[3].text, test_array[3].text},
	{" \t\n","aaa	bbb	", NULL, test_array[3].text + 4},
	{" \t\n","aaa	bbb	", NULL, NULL},
};

int main() {
	for (int i = 0; i < ARRAY_SIZE(test_array); ++i) {
		char *received_result;
		int result = invoke_and_test(&received_result, (void (*)())my_strtok, 2,
			test_array[i].text_ptr, test_array[i].seps);
		if (result != 0)
			printf("Your function currupted %s, that is a calee saved register\n",
				register_name[result]);
		if (test_array[i].token_ptr == NULL && received_result == NULL)
			;	//printf("[%d] - OK\n", i);
		else if (test_array[i].token_ptr == NULL && received_result != NULL)
			printf("[%d] expected: NULL, received: %p\n", i, received_result);
		else if (test_array[i].token_ptr != NULL && received_result == NULL)
			printf("[%d] expected: %s, received: NULL\n", i, test_array[i].token_ptr);
		else if (strcmp(received_result, test_array[i].token_ptr) != 0)
			printf("[%d] expected: %s, received: %s\n", i,
				test_array[i].token_ptr, received_result);
//		else
//			printf("[%d] - OK\n", i);
	}
}
