#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO "fifo.0"
#define MAXBUF 100
/*serv*/
int main(){
  char * buf;
  int check_r, fd, n = 0;
  buf = (char *) malloc(MAXBUF);
  mknod(FIFO, S_IFIFO | 0755, 0);
  while(1){
    if ((fd = open(FIFO, O_RDONLY)) < 0){
      perror("open1: ");
      exit(0);
    };
    check_r = read(fd, buf, MAXBUF);
    write(1, buf, check_r);
    n++;
    close(fd);
  }
  unlink(FIFO);
  free(buf);
  return 0;
}
