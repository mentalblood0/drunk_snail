#include <stdlib.h>

#define DArray_type 

typedef struct DArray {
	DArray_type *array;
	size_t used;
	size_t size;
} DArray;

void initArray(DArray *a, size_t initialSize) {
	a->array = malloc(initialSize * sizeof(DArray_type));
	a->used = 0;
	a->size = initialSize;
}

void insertArray(DArray *a, DArray_type element) {
	// a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
	// Therefore a->used can go up to a->size 
	if (a->used == a->size) {
		a->size *= 2;
		a->array = realloc(a->array, a->size * sizeof(DArray_type));
	}
	a->array[a->used++] = element;
}

void freeArray(DArray *a) {
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}