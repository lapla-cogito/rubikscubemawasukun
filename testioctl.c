#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define ROTATE_BY_INDEX 0
#define GET_OLD_STATE 1
#define ROTATE_RANDOM 3

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

