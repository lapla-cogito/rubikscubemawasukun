#include "vector.h"

#include <linux/slab.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/module.h>

#include "lib.h"

MODULE_LICENSE("GPL");

vector *vec_new(int size) {
  vector *v = New(vector);  // kmalloc 1
  if (v == NULL) {
    return NULL;
  }
  v->size = 0;
  v->data_size = sizeof(int);
  v->capacity = size;
  v->data = xmalloc(size * sizeof(int), GFP_KERNEL);
  if (v->data == NULL) {
    return NULL;
  }

  memset(v->data, 0, size * sizeof(int));
  return v;
}

int vec_realloc(vector *vec, int realloc_size) {
  void *p;
  if ((p = krealloc(vec->data, realloc_size * vec->data_size, GFP_KERNEL)) ==
      NULL) {
    return 0;
  }
  vec->data = p;
  memset(vec->data + ((vec->capacity) * (vec->data_size)), 0,
         (realloc_size - vec->capacity) * (vec->data_size));
  vec->capacity = realloc_size;
  return 1;
}

int vec_push(vector *vec, int data) {
  if (vec->size == vec->capacity &&
      vec_realloc(vec, vec->capacity + (vec->capacity >> 1) + 1) == 0) {
    return 0;
  }
  memcpy(vec->data + (vec->size++ * vec->data_size), &data, vec->data_size);
  return 1;
}

vector *vec_new_from_arr(int *arr, int size) {
  int i;
  vector *vec = vec_new(size);
  for (i = 0; i < size; ++i) {
    if (!vec_push(vec, arr[i])) {
      return vec;
    }
  }
  return vec;
}

vector *vec_dup(vector *original) {
  int i;
  vector *ret = vec_new(0);
  for (i = 0; i < original->size; ++i) {
    vec_push(ret, ((int *)original->data)[i]);
  }
  return ret;
}

char *vec_to_str(vector *vec) {
  int i;
  int data;
  int ressize = 0;

  for (i = 0; i < vec->size; ++i) {
    data = ((int *)vec->data)[i];
    if (data >= 10) {
      ressize += 2;
    } else {
      ++ressize;
    }
    ressize += 2;
  }

  char *res = xmalloc(sizeof(char) * (ressize + 1), GFP_KERNEL);
  int seek = 0;  // 文字列終端を示す
  res[seek++] = '[';
  for (i = 0; i < vec->size; ++i) {
    data = ((int *)vec->data)[i];
    if (data >= 10) {
      res[seek++] = '0' + data / 10;
      res[seek++] = '0' + data % 10;
    } else {
      res[seek++] = '0' + data;
    }
    res[seek++] = ',';
    res[seek++] = ' ';
  }
  if (seek > 0) {
    seek -= 2;  // 最後の ", " を削除
  }
  res[seek++] = ']';
  res[seek++] = '\0';  // NULL terminate
  return res;
}
