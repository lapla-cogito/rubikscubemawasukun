#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  char c1, c2;
  int fd0_A;

  if ((fd0_A = open("/dev/rubikcubemawasukun", O_RDWR)) < 0) perror("open");

  //if (read(fd0_A, &c1, 1) != 0) perror("read");
  //printf("%c\n", c1);
  //lseek(fd0_A, 0, SEEK_SET);
  //if (read(fd0_A, &c2, 1) != 0) perror("read");
  //printf("%c\n", c2);

while(read(fd0_A, &c1,1)!=0){printf("%c",c1);}
  if (close(fd0_A) != 0) perror("close");

  return 0;
}
