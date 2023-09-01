# How to run
example
```
$ make
$ sudo insmod rubik.ko
$ sudo mknod /dev/rubikscubemawasukun --mode=666 c `grep rubik /proc/devices | awk '{print $1;}'` 0
```

By executing the second line, the kernel module is inserted into the Linux kernel, and you can see the result by running ```$ cat /proc/devices``` command. The device number is decided dynamically.

The third line makes the special file on /dev. So you can check the result by executing ```$ ls /dev```. There should be /dev/rubikscubemawasukun.

# How to play
This kernel module accepts open/close/read/write/ioctl system calls. Therefore, executing the following-like programs to access the kernel module.

## r/w
```c
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  char buff[1024];
  int fd0_A;

  if ((fd0_A = open("/dev/rubikcubemawasukun", O_RDWR)) < 0) perror("open");

  if (read(fd0_A, buff, 1000) != 0) perror("read");
  printf("%s\n", buff);

  if (write(fd0_A, "U", 2) != 0) perror("write");

  if (read(fd0_A, buff, 1000) != 0) perror("read");
  printf("%s\n", buff);

  if (close(fd0_A) != 0) perror("close");

  return 0;
}
```

## ioctl
```c
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define ROTATE_BY_INDEX 0
#define GET_OLD_STATE 1
#define ROTATE_RANDOM 2

int main(void) {
  int fd;
  int rotate_index = 0;
  int get_old = 2;
  int random_num = 15;

  if ((fd = open("/dev/rubikcubemawasukun", O_RDWR)) < 0) {
    perror("open");
  }

  if (ioctl(fd, ROTATE_BY_INDEX, rotate_index) < 0) {
    perror("ioctl_rotate_by_index");
  }

  if (ioctl(fd, ROTATE_BY_INDEX, 1) < 0) {
    perror("ioctl_rotate_by_index");
  }
  if (ioctl(fd, ROTATE_BY_INDEX, 2) < 0) {
    perror("ioctl_rotate_by_index");
  }

  if (ioctl(fd, GET_OLD_STATE, get_old) < 0) {
    perror("ioctl_get_old_state");
  }

  if (ioctl(fd, ROTATE_RANDOM, random_num) < 0) {
    perror("ioctl_rotate_random");
  }

  if (close(fd) != 0) {
    perror("close");
  }
  return 0;
}
```
