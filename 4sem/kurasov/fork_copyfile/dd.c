#include <fcntl.h>
#include <unistd.h>
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
/*
  Копировать из начала или кусок файла. Добавить lseek перед чтением.
  ./a.out test test1 current offset bs
 */
int main(int argc, char ** argv){
  int fd_in, fd_out, bs, count_r, count_w, offset, l, current, i;
  char * buf;
  if ((fd_in = open(argv[1], O_RDONLY, 00755)) < 0){
    perror("open1: ");
    exit(0);
  };
  if ((fd_out = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 00755)) < 0){
    perror("open2: ");
    exit(0);
  };
  
  current = atoi(argv[3]);
  offset = atoi(argv[4]);
  bs = atoi(argv[5]);
  if (offset % bs != 0){
    printf("wrong offset, it must be divisible by bs\n");
    exit(0);
  }
  if ((l = lseek(fd_in, current, SEEK_SET)) < 0){
    perror("lseek: ");
    exit(0);
  }
  if (l < current){
    exit(0);
  }
  count_r = 1;
  buf = (char *) malloc(bs);
  i = 0;
  while (count_r > 0 && i < offset){
    if ((count_r = read(fd_in, buf, bs)) < 0){
      perror("read: ");
      exit(0);
    };
    if ((count_w = write(fd_out, buf, count_r)) < 0){
      perror("write: ");
      exit(0);
    };
    i += bs;
  }
  if (close(fd_in) < 0){
    perror("close fd_in: ");
    exit(0);
  };
  if (close(fd_out) < 0){
    perror("close fd_out: ");
    exit(0);
  };
  free(buf);
  return 0;
}
