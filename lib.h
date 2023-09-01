#ifndef __LIB_HEADER_INCLUDED__
#define __LIB_HEADER_INCLUDED__
#include <asm/errno.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/types.h>

#include "vector.h"
typedef struct {
  vector *cp;
  vector *co;
  vector *ep;
  vector *eo;
} State;

static void *xmalloc(size_t size, gfp_t gfptype) {
  void *m = kmalloc(size, gfptype);
  if (m == NULL) {
    printk(KERN_ERR "failed to allocate memory\n");
    panic("failed to allocate memory\n");
  }
  return m;
}

#define New(type) ((type *)xmalloc(sizeof(type), GFP_KERNEL))

#endif
