#include <linux/string.h>

#include "lib.h"

typedef struct {
  char *key;
  State *val;
} dict;

State *dict_get(char *key);

