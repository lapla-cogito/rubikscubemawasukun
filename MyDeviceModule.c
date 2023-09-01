#include <asm/current.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/random.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/types.h>

#include "dict.h"
#include "lib.h"
#include "vector.h"
static const unsigned int MINOR_BASE = 0;
static const unsigned int MINOR_NUM = 2;
static unsigned int mydevice_major;
static struct cdev mydevice_cdev;

extern vector *vec_new(int size);

extern vector *vec_new_from_arr(int *arr, int size);

extern int vec_push(vector *vec, int data);

extern vector *vec_dup(vector *original);

extern char *vec_to_str(vector *vec);

extern State *dict_get(char *key);

#define DRIVER_NAME "rubikcubemawasukun"
#define ROTATE_BY_INDEX 0
#define GET_OLD_STATE 1
#define ROTATE_RANDOM 3

MODULE_LICENSE("GPL");

struct _mydevice_file_data {
  State *sample_cube;
  vector *rotates;
};

State *InitCube(void) {
  State *newcube = New(State);  // kmalloc 3
  int cp[] = {0, 1, 2, 3, 4, 5, 6, 7};
  int co[] = {0, 0, 0, 0, 0, 0, 0, 0};
  int ep[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  newcube->cp = vec_new_from_arr(cp, 8);
  newcube->co = vec_new_from_arr(co, 8);
  newcube->ep = vec_new_from_arr(ep, 12);
  newcube->eo = vec_new_from_arr(eo, 12);

  return newcube;
}

int mydevice_open(struct inode *inode, struct file *file) {
  struct _mydevice_file_data *p =
      kmalloc(sizeof(struct _mydevice_file_data), GFP_KERNEL);  // kmalloc 4
  if (p == NULL) {
    return -ENOMEM;
  }
  p->sample_cube = InitCube();  // kmalloc 5
  p->rotates = vec_new(0);      // kmalloc 6
  file->private_data = (void *)p;
  return 0;
}

int mydevice_close(struct inode *inode, struct file *file) {
  if (file->private_data) {
    kfree(file->private_data);
  }
  return 0;
}

static ssize_t mydevice_read(struct file *filp, char __user *buf, size_t count,
                             loff_t *f_pos) {
  int i;
  int data;
  State *current_state =
      ((struct _mydevice_file_data *)filp->private_data)->sample_cube;
  char *res = xmalloc(sizeof(char) * 1024, GFP_KERNEL);
  int seek = 0;  // 何文字読み込んだかを見る

  // cp
  res[seek++] = 'c';
  res[seek++] = 'p';
  res[seek++] = ':';
  res[seek++] = ' ';
  res[seek++] = '[';
  for (i = 0; i < current_state->cp->size; ++i) {
    data = ((int *)current_state->cp->data)[i];
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
  res[seek++] = '\n';
  // cp

  // co
  res[seek++] = 'c';
  res[seek++] = 'o';
  res[seek++] = ':';
  res[seek++] = ' ';
  res[seek++] = '[';
  for (i = 0; i < current_state->co->size; ++i) {
    data = ((int *)current_state->co->data)[i];
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
  res[seek++] = '\n';
  // co

  // ep
  res[seek++] = 'e';
  res[seek++] = 'p';
  res[seek++] = ':';
  res[seek++] = ' ';
  res[seek++] = '[';
  for (i = 0; i < current_state->ep->size; ++i) {
    data = ((int *)current_state->ep->data)[i];
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
  res[seek++] = '\n';
  // ep

  // eo
  res[seek++] = 'e';
  res[seek++] = 'o';
  res[seek++] = ':';
  res[seek++] = ' ';
  res[seek++] = '[';

  for (i = 0; i < current_state->eo->size; ++i) {
    data = ((int *)current_state->eo->data)[i];
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
  res[seek++] = '\n';
  // eo

  res[seek] = '\0';  // NULL terminate

  if (copy_to_user(buf, res, seek)) {
    return -EFAULT;
  }

  count = seek;
  *f_pos += count;
  kfree(res);
  return 0;
}

State *apply_move(State *cube, State *move) {
  vector *new_cp = vec_new(0);  // kmalloc 8
  for (int i = 0; i < (move->cp->size); ++i) {
    vec_push(new_cp, ((int *)cube->cp)[((int *)move->cp->data)[i]]);
  }

  vector *new_co = vec_new(0);  // kmalloc 9
  for (int i = 0; i < (move->co->size); ++i) {
    vec_push(new_co, (((int *)cube->co->data)[((int *)move->cp->data)[i]] +
                      ((int *)move->co->data)[i]) %
                         3);
  }

  vector *new_ep = vec_new(0);  // kmalloc 10
  for (int i = 0; i < (move->ep->size); ++i) {
    vec_push(new_cp, ((int *)cube->ep)[((int *)move->ep->data)[i]]);
  }

  vector *new_eo = vec_new(0);  // kmalloc 11
  for (int i = 0; i < (move->eo->size); ++i) {
    vec_push(new_eo, (((int *)cube->eo->data)[((int *)move->ep->data)[i]] +
                      ((int *)move->eo->data)[i]) %
                         2);
  }

  for (int i = 0; i < (move->cp->size); ++i) {
   ((int *)cube->cp->data)[i]=((int *)move->cp->data)[i];
  }
  for (int i = 0; i < (move->co->size); ++i) {
   ((int *)cube->co->data)[i]=((int *)move->co->data)[i];
  }
  for (int i = 0; i < (move->ep->size); ++i) {
   ((int *)cube->ep->data)[i]=((int *)move->ep->data)[i];
  }
  for (int i = 0; i < (move->eo->size); ++i) {
   ((int *)cube->eo->data)[i]=((int *)move->eo->data)[i];
  }

  kfree(new_cp);
  kfree(new_co);
  kfree(new_ep);
  kfree(new_eo);
  return cube;
}

int index_from_notation(char *str) {
  if (strcmp(str, "R") == 0) {
    return 0;
  }
  if (strcmp(str, "RP") == 0) {
    return 1;
  }
  if (strcmp(str, "R2") == 0) {
    return 2;
  }
  if (strcmp(str, "L") == 0) {
    return 3;
  }
  if (strcmp(str, "LP") == 0) {
    return 4;
  }
  if (strcmp(str, "L2") == 0) {
    return 5;
  }
  if (strcmp(str, "U") == 0) {
    return 6;
  }
  if (strcmp(str, "UP") == 0) {
    return 7;
  }
  if (strcmp(str, "U2") == 0) {
    return 8;
  }
  if (strcmp(str, "D") == 0) {
    return 9;
  }
  if (strcmp(str, "DP") == 0) {
    return 10;
  }
  if (strcmp(str, "D2") == 0) {
    return 11;
  }
  if (strcmp(str, "F") == 0) {
    return 12;
  }
  if (strcmp(str, "FP") == 0) {
    return 13;
  }
  if (strcmp(str, "F2") == 0) {
    return 14;
  }
  if (strcmp(str, "B") == 0) {
    return 15;
  }
  if (strcmp(str, "BP") == 0) {
    return 16;
  }
  if (strcmp(str, "B2") == 0) {
    return 17;
  }
  return -1;
}

static ssize_t mydevice_write(struct file *filp, const char __user *buf,
                              size_t count, loff_t *f_pos) {
  int index_num;
  if (count > 3) {
    return -EINVAL;
  }

  char *kbuf = xmalloc(sizeof(char) * count, GFP_KERNEL);  // kmalloc 13
  if (copy_from_user(kbuf, buf, count)) {
    return -EFAULT;
  }
  kbuf[count] = '\0';

  index_num = index_from_notation(kbuf);

  State *sample_cube =
      ((struct _mydevice_file_data *)filp->private_data)->sample_cube;
  vector *rotates = ((struct _mydevice_file_data *)filp->private_data)->rotates;

  switch (index_num) {
    case 0:
      sample_cube = apply_move(sample_cube, dict_get("R"));
      vec_push(rotates, index_num);
      break;
    case 1:
      sample_cube = apply_move(sample_cube, dict_get("RP"));
      vec_push(rotates, index_num);
      break;
    case 2:
      sample_cube = apply_move(sample_cube, dict_get("R2"));
      vec_push(rotates, index_num);
      break;
    case 3:
      sample_cube = apply_move(sample_cube, dict_get("L"));
      vec_push(rotates, index_num);
      break;
    case 4:
      sample_cube = apply_move(sample_cube, dict_get("LP"));
      vec_push(rotates, index_num);
      break;
    case 5:
      sample_cube = apply_move(sample_cube, dict_get("L2"));
      vec_push(rotates, index_num);
      break;
    case 6:
      sample_cube = apply_move(sample_cube, dict_get("U"));
      vec_push(rotates, index_num);
      break;
    case 7:
      sample_cube = apply_move(sample_cube, dict_get("UP"));
      vec_push(rotates, index_num);
      break;
    case 8:
      sample_cube = apply_move(sample_cube, dict_get("U2"));
      vec_push(rotates, index_num);
      break;
    case 9:
      sample_cube = apply_move(sample_cube, dict_get("D"));
      vec_push(rotates, index_num);
      break;
    case 10:
      sample_cube = apply_move(sample_cube, dict_get("DP"));
      vec_push(rotates, index_num);
      break;
    case 11:
      sample_cube = apply_move(sample_cube, dict_get("D2"));
      vec_push(rotates, index_num);
      break;
    case 12:
      sample_cube = apply_move(sample_cube, dict_get("F"));
      vec_push(rotates, index_num);
      break;
    case 13:
      sample_cube = apply_move(sample_cube, dict_get("FP"));
      vec_push(rotates, index_num);
      break;
    case 14:
      sample_cube = apply_move(sample_cube, dict_get("F2"));
      vec_push(rotates, index_num);
      break;
    case 15:
      sample_cube = apply_move(sample_cube, dict_get("B"));
      vec_push(rotates, index_num);
      break;
    case 16:
      sample_cube = apply_move(sample_cube, dict_get("BP"));
      vec_push(rotates, index_num);
      break;
    case 17:
      sample_cube = apply_move(sample_cube, dict_get("B2"));
      vec_push(rotates, index_num);
      break;
    default:
      break;
  }
  kfree(kbuf);
  return 0;
}

State *rotate_by_ind(State *state, unsigned int arg, vector *rotates) {
  switch (arg) {
    case 0:
      state = apply_move(state, dict_get("R"));
      vec_push(rotates, arg);
      break;
    case 1:
      state = apply_move(state, dict_get("RP"));
      vec_push(rotates, arg);
      break;
    case 2:
      state = apply_move(state, dict_get("R2"));
      vec_push(rotates, arg);
      break;
    case 3:
      state = apply_move(state, dict_get("L"));
      vec_push(rotates, arg);
      break;
    case 4:
      state = apply_move(state, dict_get("LP"));
      vec_push(rotates, arg);
      break;
    case 5:
      state = apply_move(state, dict_get("L2"));
      vec_push(rotates, arg);
      break;
    case 6:
      state = apply_move(state, dict_get("U"));
      vec_push(rotates, arg);
      break;
    case 7:
      state = apply_move(state, dict_get("UP"));
      vec_push(rotates, arg);
      break;
    case 8:
      state = apply_move(state, dict_get("U2"));
      vec_push(rotates, arg);
      break;
    case 9:
      state = apply_move(state, dict_get("D"));
      vec_push(rotates, arg);
      break;
    case 10:
      state = apply_move(state, dict_get("DP"));
      vec_push(rotates, arg);
      break;
    case 11:
      state = apply_move(state, dict_get("D2"));
      vec_push(rotates, arg);
      break;
    case 12:
      state = apply_move(state, dict_get("F"));
      vec_push(rotates, arg);
      break;
    case 13:
      state = apply_move(state, dict_get("FP"));
      vec_push(rotates, arg);
      break;
    case 14:
      state = apply_move(state, dict_get("F2"));
      vec_push(rotates, arg);
      break;
    case 15:
      state = apply_move(state, dict_get("B"));
      vec_push(rotates, arg);
      break;
    case 16:
      state = apply_move(state, dict_get("BP"));
      vec_push(rotates, arg);
      break;
    case 17:
      state = apply_move(state, dict_get("B2"));
      vec_push(rotates, arg);
      break;
    default:
      break;
  }
  return state;
}

State *get_old_rubik(State *state, unsigned int arg, vector *rotates) {
  int i;
  int vec_get_num;
  State *return_state = New(State);  // kmalloc 14
  return_state->cp = vec_dup(state->cp);
  return_state->co = vec_dup(state->co);
  return_state->ep = vec_dup(state->ep);
  return_state->eo = vec_dup(state->eo);
  for (i = 0; i < arg; ++i) {
    vec_get_num = ((int *)rotates->data)[(rotates->size) - i - 1];
    switch (vec_get_num) {
      case 0:
        return_state = apply_move(return_state, dict_get("RP"));
        break;
      case 1:
        return_state = apply_move(return_state, dict_get("R"));
        break;
      case 2:
        return_state = apply_move(return_state, dict_get("R2"));
        break;
      case 3:
        return_state = apply_move(return_state, dict_get("LP"));
        break;
      case 4:
        return_state = apply_move(return_state, dict_get("L"));
        break;
      case 5:
        return_state = apply_move(return_state, dict_get("L2"));
        break;
      case 6:
        return_state = apply_move(return_state, dict_get("UP"));
        break;
      case 7:
        return_state = apply_move(return_state, dict_get("U"));
        break;
      case 8:
        return_state = apply_move(return_state, dict_get("U2"));
        break;
      case 9:
        return_state = apply_move(return_state, dict_get("DP"));
        break;
      case 10:
        return_state = apply_move(return_state, dict_get("D"));
        break;
      case 11:
        return_state = apply_move(return_state, dict_get("D2"));
        break;
      case 12:
        return_state = apply_move(return_state, dict_get("FP"));
        break;
      case 13:
        return_state = apply_move(return_state, dict_get("F"));
        break;
      case 14:
        return_state = apply_move(return_state, dict_get("F2"));
        break;
      case 15:
        return_state = apply_move(return_state, dict_get("BP"));
        break;
      case 16:
        return_state = apply_move(return_state, dict_get("B"));
        break;
      case 17:
        return_state = apply_move(return_state, dict_get("B2"));
        break;
      default:
        break;
    }
  }
  return return_state;
}

State *rand_rotate(State *state, unsigned int arg, vector *rotates) {
  int i;
  unsigned int rand_num;
  for (i = 0; i < arg; ++i) {
    rand_num = get_random_u32() % 18;
    state = rotate_by_ind(state, rand_num, rotates);
  }
  return state;
}

long int mydevice_ioctl(struct file *filp, unsigned int cmd,
                        long unsigned int arg) {
  switch (cmd) {
    case ROTATE_BY_INDEX:
      State *ind_state = rotate_by_ind(
          ((struct _mydevice_file_data *)filp->private_data)->sample_cube, arg,
          ((struct _mydevice_file_data *)filp->private_data)->rotates);
      printk(KERN_INFO "%s\n", vec_to_str(ind_state->cp));
      printk(KERN_INFO "%s\n", vec_to_str(ind_state->co));
      printk(KERN_INFO "%s\n", vec_to_str(ind_state->ep));
      printk(KERN_INFO "%s\n", vec_to_str(ind_state->eo));
      break;
    case GET_OLD_STATE:
      State *old_state = get_old_rubik(
          ((struct _mydevice_file_data *)filp->private_data)->sample_cube, arg,
          ((struct _mydevice_file_data *)filp->private_data)->rotates);
      printk(KERN_INFO "%s\n", vec_to_str(old_state->cp));
      printk(KERN_INFO "%s\n", vec_to_str(old_state->co));
      printk(KERN_INFO "%s\n", vec_to_str(old_state->ep));
      printk(KERN_INFO "%s\n", vec_to_str(old_state->eo));
      if (old_state) {
        kfree(old_state->cp);
        kfree(old_state->co);
        kfree(old_state->ep);
        kfree(old_state->eo);
        kfree(old_state);
      }
      break;
    case ROTATE_RANDOM:
      State *rand_state = rand_rotate(
          ((struct _mydevice_file_data *)filp->private_data)->sample_cube, arg,
          ((struct _mydevice_file_data *)filp->private_data)->rotates);
      printk(KERN_INFO "%s\n", vec_to_str(rand_state->cp));
      printk(KERN_INFO "%s\n", vec_to_str(rand_state->co));
      printk(KERN_INFO "%s\n", vec_to_str(rand_state->ep));
      printk(KERN_INFO "%s\n", vec_to_str(rand_state->eo));
      break;
    default:
      return -EFAULT;
  }
  printk("\n");
  return 0;
}

struct file_operations s_mydevice_fops = {
    .open = mydevice_open,
    .release = mydevice_close,
    .read = mydevice_read,
    .write = mydevice_write,
    .unlocked_ioctl = mydevice_ioctl,
    .compat_ioctl = mydevice_ioctl,
};

static int mydevice_init(void) {
  int alloc_ret = 0;
  int cdev_err = 0;
  dev_t dev;

  alloc_ret = alloc_chrdev_region(&dev, MINOR_BASE, MINOR_NUM, DRIVER_NAME);
  if (alloc_ret != 0) {
    printk(KERN_ERR "alloc_chrdev_region = %d\n", alloc_ret);
    return -1;
  }

  mydevice_major = MAJOR(dev);
  dev = MKDEV(mydevice_major, MINOR_BASE);
  cdev_init(&mydevice_cdev, &s_mydevice_fops);
  mydevice_cdev.owner = THIS_MODULE;

  cdev_err = cdev_add(&mydevice_cdev, dev, MINOR_NUM);
  if (cdev_err != 0) {
    printk(KERN_ERR "cdev_add = %d\n", cdev_err);
    unregister_chrdev_region(dev, MINOR_NUM);
    return -1;
  }

  return 0;
}
static void mydevice_exit(void) {
  dev_t dev = MKDEV(mydevice_major, MINOR_BASE);
  cdev_del(&mydevice_cdev);
  unregister_chrdev_region(dev, MINOR_NUM);
}

module_init(mydevice_init);
module_exit(mydevice_exit);
