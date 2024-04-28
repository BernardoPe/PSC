#include "struct_values.h"

int compare_offset(struct values *values[], int i, int j, int k, struct values *avalue) {
	return k < values[i][j].len && values[i][j].offset[k] == avalue->offset[k];
}
