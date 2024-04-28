#include <stddef.h>
#include <string.h>

static void memswap(void *one, void *other, size_t width){
	char tmp[width];
	memcpy(tmp, one, width);
	memcpy(one, other, width);
	memcpy(other, tmp, width);
}
void bubble_sort(void *base, size_t nelements, size_t width,
			int (*compare)(const void *, const void *)) {
	int swap_flg = 0;
	if (nelements <= 1)
		return;
	char *limit = (char *)base + (nelements - 1) * width;
	for (char *ptr = base; ptr < limit; ptr += width)
		if (compare(ptr, ptr + width) > 0) {
			memswap(ptr, ptr + width, width);
			swap_flg = 1;
		}
	if (swap_flg == 0)
		return;
	bubble_sort(base, nelements - 1, width, compare);
}
