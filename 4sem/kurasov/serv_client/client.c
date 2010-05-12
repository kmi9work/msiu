#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MAXBUF 10
#define FIFO "fifo.0"

/*client*/
int main(){
  int fd_out;
  if ((fd_out = open(FIFO, O_WRONLY, 00755)) < 0){
    perror("open2: ");
    exit(0);
  };
  write(fd_out, "Hello World!\n", 13);
  close(fd_out);
  return 0;
}
