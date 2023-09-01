#ifndef __VECTOR_HEADER_INCLUDED__
#define __VECTOR_HEADER_INCLUDED__
#include <linux/stddef.h>

typedef struct {
  void *data;
  int size;
  int capacity;
  int data_size;
} vector;

vector *vec_new(int size);

vector *vec_new_from_arr(int *arr, int size);

int vec_push(vector *vec, int data);

vector *vec_dup(vector *original);

char *vec_to_str(vector *vec);
#endif
