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
