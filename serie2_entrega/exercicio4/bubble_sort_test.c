#include <stdio.h>
#include <string.h>

static const char *register_name[] = { "", "rbp", "rbx", "r15", "r14", "r13", "r12" };
int invoke_and_test(void *, void (*)(), int, ...);

#define ARRAY_SIZE(a)	(sizeof(a)/sizeof(a[0]))

void bubble_sort(void *base, size_t nelements, size_t width,
			int (*compare)(const void *, const void *));

/* tipo int ------------------------------------------------------------------*/

static int unsorted_ints[] = {3, 6, 2, 0, 1, 5, 4, 8, 7, 9};

static int sorted_ints[]   = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

#if 1
int compare_ints(const void *a, const void *b);
#else
static int compare_ints(const void *a, const void *b) {
	if (*(int *)a > *(int *)b)
		return +1;
	else if (*(int *)a < *(int *)b)
		return -1;
	return 0;
}

#endif

static void print_ints(void *array, size_t array_size) {
	int *p = (int *)array;
	for (size_t i = 0; i < array_size; i++, p++) {
		printf("%d ", *p);
	}
}

/* tipo char * ---------------------------------------------------------------*/

static const char *unsorted_strings[] = {"bbb", "ggg", "aaa", "fff", "ddd", "eee", "ccc"};

static const char *sorted_strings[]   = {"aaa", "bbb", "ccc", "ddd", "eee", "fff", "ggg"};

#if 1
int compare_strings(const void *a, const void *b);
#else
static int compare_strings(const void *a, const void *b) {
	return strcmp(*(char **)a, *(char **)b);
}
#endif

static void print_strings(void *array, size_t array_size) {
	char **p = (char **)array;
	for (size_t i = 0; i < array_size; i++, p++) {
		printf("%s ", *p);
	}
}

/* tipo struct ---------------------------------------------------------------*/

static struct test {
	char c;
	int i;
	short s;
} unsorted_structs[] = {
	{ .i = 3 },
	{ .i = 6 },
	{ .i = 2 },
	{ .i = 0 },
	{ .i = 1 },
	{ .i = 5 },
	{ .i = 4 },
	{ .i = 8 },
	{ .i = 7 },
	{ .i = 9 }
};

static struct test sorted_structs[] = {
	{ .i = 0 },
	{ .i = 1 },
	{ .i = 2 },
	{ .i = 3 },
	{ .i = 4 },
	{ .i = 5 },
	{ .i = 6 },
	{ .i = 7 },
	{ .i = 8 },
	{ .i = 9 }
};

#if 1
int compare_structs(const void *a, const void *b);
#else
static int compare_structs(const void *a, const void *b) {
	if (((struct test *)a)->i > ((struct test *)b)->i)
		return +1;
	else if (((struct test *)a)->i < ((struct test *)b)->i)
		return -1;
	return 0;
}
#endif

static void print_structs(void *array, size_t array_size) {
	struct test *p = (struct test *)array;
	for (size_t i = 0; i < array_size; i++, p++) {
		printf("%d ", p->i);
	}
}

static struct {
	void *unsorted;
	void *sorted;
	size_t size;
	size_t element_size;
	int (*compare_function)(const void *, const void *);
	void (*print)(void *, size_t);
} test_array[] = {
	{ unsorted_ints, sorted_ints, ARRAY_SIZE(unsorted_ints), sizeof unsorted_ints[0], compare_ints, print_ints },
	{ unsorted_strings, sorted_strings, ARRAY_SIZE(unsorted_strings), sizeof unsorted_strings[0], compare_strings, print_strings },
	{ unsorted_structs, sorted_structs, ARRAY_SIZE(unsorted_structs), sizeof unsorted_structs[0], compare_structs, print_structs },
};

static void print_result(size_t i) {
	if (memcmp(test_array[i].unsorted, test_array[i].sorted,
			test_array[i].size * test_array[i].element_size) != 0) {
		printf("[%zu] Expected: ", i);
		test_array[i].print(test_array[i].sorted, test_array[i].size);
		putchar('\n');
		printf("Received: ");
		test_array[i].print(test_array[i].unsorted, test_array[i].size);
		putchar('\n');
	}
//	else
//		printf("[%zu] - OK\n", i);
}

int main() {
	int error = 0;
	for (size_t i = 0; i < ARRAY_SIZE(test_array); ++i) {
		void *dummy;
		int result = invoke_and_test(&dummy, (void (*)())bubble_sort, 4,
			test_array[i].unsorted, test_array[i].size, test_array[i].element_size, test_array[i].compare_function);
		if (result != 0) {
			printf("Your function currupted %s, that is a calee saved register\n",
				register_name[result]);
			error = 1;
			break;
		}
		print_result(i);
	}
	return error;
}

