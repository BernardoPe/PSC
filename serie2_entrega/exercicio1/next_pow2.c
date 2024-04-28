#include <stddef.h>
#include <limits.h>

size_t next_pow2(size_t x)
{
	size_t mask = 1UL << ((sizeof mask * CHAR_BIT) - 1);
	if (x == 0 || x > mask)
		return 0;
	while ((x & mask) == 0)
		mask >>= 1;
	return mask << (x != mask);
}
