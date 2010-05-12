#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>


#define FIFO "fifo.0"

static struct sembuf iter_lock[1] = {{0, 1, 0}};
static struct sembuf iter_unlock[1] = {{0, -1, 0}};
static struct sembuf iter_wait[1] = {{0, 0, 0}};
static struct sembuf r_lock[1] = {{1, -1, 0}};
static struct sembuf r_unlock[1] = {{1, 1, 0}};
static struct sembuf w_lock[1] = {{2, -1, 0}};
static struct sembuf w_unlock[1] = {{2, 1, IPC_NOWAIT}};
static struct sembuf work_start[1] = {{3, 1, IPC_NOWAIT}};
static struct sembuf work_stop[1] = {{3, -1, IPC_NOWAIT}};

volatile sig_atomic_t die = 0;

void sigchldhandler(int signal){
  while ((waitpid(0,NULL,WNOHANG))>0){
    die++;
  }
}

void detach_seg(char *seg_ptr){
  if ((shmdt(seg_ptr)) < 0) {
    perror("error detaching"); 
    exit(2);
  }
}

void close_seg(int shm_id){
  if ((shmctl(shm_id,IPC_RMID,0)) < 0) {
    perror("error deleting seg"); 
    exit(2);
  }
}


int open_seg(key_t keyval, int segsize){
  int shm_id;
  if ((shm_id = shmget(keyval, segsize, IPC_CREAT | IPC_EXCL | 0660)) < 0){
    if (errno == EEXIST){
      if ((shm_id = shmget(keyval, 0, 0)) < 0) {
        return -1;      
      }
    }else{
      return -1;
    }
  }
  return shm_id;
}

int open_sem(key_t keyval, int semnum){
  int sem_id;
  if ((sem_id = semget(keyval,semnum,IPC_CREAT | IPC_EXCL | 0660)) < 0){
    if (errno == EEXIST){
      if ((sem_id = semget(keyval, 0, 0)) < 0) {
        return -1;      
      }
    }else{
      return -1;
    }
  }
  return sem_id;
}

int set_sem_val(int sid, int semnum, int val){
  union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
  } semarg;
  
  semarg.val = val;
  return (semctl(sid, semnum, SETVAL, semarg));
}

int get_sem_val(int sid, int semnum){
  return(semctl(sid, semnum, GETVAL, 0));
}

void close_sem(int sem_id){
  if ((semctl(sem_id,0,IPC_RMID)) < 0) {
    perror("error deleting semafor"); 
    exit(2);
  }
}


void op_sem(int semid, struct sembuf *sops){
  while(1){
    if (semop(semid,sops,1) < 0) {
      if (errno == EINTR){
        continue;
      }
      printf("semop error\nsem num: %d\nsem op: %d\n", sops[0].sem_num, sops[0].sem_op);
      perror("error:");	
      exit(2);
    }else{
      break;
    }
  }
}
void make_step(int type, int m, int num_ms, int msgid, int sem_id){
  int i, j;
  int count;/*part size*/
  int * warr;
  struct msgbuf{
    long int mtype;
    int mtext[2];
  } buf;
  warr = (int *) malloc(sizeof(int) * 2);
  buf.mtype = 1;
  switch (type){
  case 1: /*pyramid*/
    count = m/num_ms;
    for(j = num_ms - 1; j >= 0; j--){
      for(i = 0; i < count/2; i++){	
       	buf.mtext[0] = i+(num_ms-1-j)*count;
        buf.mtext[1] = m-1 - j*count - i;
        while(1){
          if (msgsnd(msgid, &buf, sizeof(int)*2, 0) < 0){
            if (errno == EINTR){
              continue;
            }
            perror("write fd 1");
            exit(2);
          }else{
            break;
          };	
        }
        op_sem(sem_id, &iter_lock[0]);
      }
    }
    break;
  case 2: /*stairway*/
    count = m/num_ms;
    for(j = 0; j < num_ms; j++){
      for(i = 0; i < count/2; i++){
        buf.mtext[0] = j*count + i;
        buf.mtext[1] = j*count + i + count/2;
        while(1){
          if (msgsnd(msgid, &buf, sizeof(int)*2, 0) < 0){
            if (errno == EINTR){
              continue;
            }
            perror("write fd 1");
            exit(2);
          }else{
            break;
          };	
        }
        op_sem(sem_id, &iter_lock[0]);
      }
    }
    break;
  case 3: /*[ones]*/
    for(i = 0; i < m/2; i++){
      buf.mtext[0] = i*2;
      buf.mtext[1] = i*2 + 1;
      while(1){
        if (msgsnd(msgid, &buf, sizeof(int)*2, 0) < 0){
          if (errno == EINTR){
            continue;
          }
          perror("write fd 1");
          exit(2);
        }else{
          break;
        }
      }
      op_sem(sem_id, &iter_lock[0]);
    }
    break;
  default: printf("Make step error.\n"); exit(2);
  }
  op_sem(sem_id, &iter_wait[0]);
  free(warr);
}


void bs(int n, int height, int i,  int msgid, int sem_id){
  if (n == 2){
    make_step(3, height, 1, msgid, sem_id);
  }else if (n >= 4){
    make_step(2, height, i, msgid, sem_id);
    bs(n/2, height, i*2, msgid, sem_id);
  }else{
    printf("Error bs!\n");
    exit(0);
  }
}



void make_mn(int n, int height, int i,  int msgid, int sem_id){
  if (n == 2){
    make_step(3, height, 1, msgid, sem_id);
  }else if (n >= 4){
    make_mn(n/2, height, i*2, msgid, sem_id);
    make_step(1, height, i, msgid, sem_id);
    bs(n/2, height, i*2, msgid, sem_id);
  }else{
    printf("Error mn!\n");
    exit(0);
  }
}

int main(int argc, char ** argv){
  key_t key;
  int *shm_seg, shm_id, sem_id, pid, msgid;
  int i, tmp, count_r;
  unsigned int nn, n, size;
  struct sigaction sa;
  struct msgbuf{
    long mtype;
    int mtext[2];
  } buf;  
  
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = sigchldhandler;
  if (sigaction(SIGCHLD, &sa, 0) < 0){
    perror("sigaction");
    exit(0);
  }
  
  printf("n: "); scanf("%u", &n); 
  if (n < 2){ printf("n must be bigger than 1\n"); _exit(0); }
  nn = 2;
  while (nn < n){
    nn <<= 1;
  }

  /*-initialize*/
  if ((key = ftok(argv[0], 'p')) < 0) { perror("ftok"); exit(2); }/*ftok=======*/
  size = nn*sizeof(int);
  if ((shm_id = open_seg(key,size)) < 0){ printf("open_seg error\n"); exit(2); }
  if (*(shm_seg = shmat(shm_id, 0, 0)) < 0) { printf("error attaching %d\n",shm_id); exit(2); }
  if ((sem_id = open_sem(key,4)) < 0){ printf("open_sem error\n"); exit(2); }
  
  srand(key);
  for(i = 0; i < n; i++){
    shm_seg[i] = rand() % 100;
    printf("%d ", shm_seg[i]);
  }
  for(; i < nn; i++){
    shm_seg[i] = 100;
  }
  printf("\n");
  
  /*=initialize*/
  if ((msgid = msgget(key, IPC_CREAT | O_RDWR | O_NONBLOCK | 0660)) < 0){
    perror("msgget: "); 
    _exit(2);
  };
  op_sem(sem_id, &r_unlock[0]);
  op_sem(sem_id, &w_unlock[0]);
	op_sem(sem_id, &work_start[0]);
  for(i = 0; i < nn/2; i++){
    if ((pid = fork()) < 0){ printf("fork %d", i); _exit(2); }
    if (pid == 0){
      while (get_sem_val(sem_id, 3) > 0){
        buf.mtext[0] = 0; buf.mtext[1] = 0;
        op_sem(sem_id, &r_lock[0]);
       /* printf("%d: start reading msg\n", getpid());*/
        while(1){
          if ((count_r = msgrcv(msgid, &buf, sizeof(int)*2, 1, IPC_NOWAIT)) < 0){
            if (errno == EINTR){
              /*printf("%d: get EINTR\n", getpid());*/
              continue;
            }
            if (errno == ENOMSG){
              break;
            }
            perror("rcv: "); 
            _exit(2);
          }else{
            break;
          }
        }
        /*printf("%d: stop reading msg\n", getpid());*/
        op_sem(sem_id, &r_unlock[0]);
        if (count_r < 2){
          /*printf("%d: count_r < 2\n", getpid());*/
          continue;
        }	
        op_sem(sem_id, &iter_unlock[0]);
        /*printf("%d: iter unlock\n", getpid());*/
        if (shm_seg[buf.mtext[0]] > shm_seg[buf.mtext[1]]){
          tmp = shm_seg[buf.mtext[0]];
          op_sem(sem_id, &w_lock[0]);
          /*printf("%d: start writing shm\n", getpid());*/
          shm_seg[buf.mtext[0]] = shm_seg[buf.mtext[1]];
          shm_seg[buf.mtext[1]] = tmp;
         /* printf("%d: stop writing shm\n", getpid());*/
          op_sem(sem_id, &w_unlock[0]);
        }
      }
     /* printf("%d: process died\n", getpid());*/
      _exit(0);
    }
  }
  
  make_mn(nn, nn, 1, msgid, sem_id);
  op_sem(sem_id, &work_stop[0]);
  printf("work == 1\n");
  sleep(30);
  for(i = 0; i < n; i++){
    printf("%d ", shm_seg[i]);
  }
  printf("\n");

  while(die < nn/2);
  
  if (msgctl(msgid, IPC_RMID, 0) < 0){
    perror("delete");
    _exit(2);
  }
  detach_seg((char *)shm_seg);
  close_seg(shm_id);
  close_sem(sem_id);
  return 0;
}
