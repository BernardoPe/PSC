#include <string.h>

char *my_strtok(char *str, const char *sep)
{
	static char *p = NULL;
	if (str != NULL)
		p = str;
	if (p == NULL || *p == 0)
		return NULL;
	while (strchr(sep, *p) != NULL)
		++p;
	if (*p == 0)
		return NULL;
	char *q = p;
	while (*p != 0 && strchr(sep, *p) == NULL)
		++p;
	*p++ = 0;
	return q;
}

int main() {
	return 0;
}