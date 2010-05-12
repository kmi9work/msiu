#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#define SEGSIZE 1024

static struct sembuf m_unlock[1] = {{0,1,0}};
static struct sembuf m_lock[1] = {{ 0,-1,0}};
static struct sembuf p_unlock[1] = {{ 1,1,0}};
static struct sembuf p_lock[1] = {{ 1,-1,0}};
static int die = 0;

void sigchldhandler(int signal){
  while ((waitpid(0,NULL,WNOHANG))>0){
    die++;
  }
}

int open_seg(key_t keyval, int segsize){
  int shm_id;
  if (segsize == 0){ 
    if ((shm_id = shmget(keyval, 0, 0)) < 0) {return -1;}  
  }
  if ((shm_id = shmget(keyval,segsize,IPC_CREAT | IPC_EXCL | 0660)) < 0){
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

int *attach_seg(int shm_id){
  int *shm_seg;
  if (*(shm_seg = shmat(shm_id, 0, 0)) < 0) {
    printf("error attaching %d\n",shm_id); 
    exit(2);
  }else{ 
    return shm_seg;
  }
}

void detach_seg(char *seg_ptr){
  if ((shmdt(seg_ptr)) < 0) {
    printf("error detaching %p\n",seg_ptr); 
    exit(2);
  }
}

void close_seg(int shm_id){
  if ((shmctl(shm_id,IPC_RMID,0)) < 0) {
    printf("error deleting seg %d\n",shm_id); 
    exit(2);
  }
}

int open_sem(key_t keyval, int semnum){
  int sem_id;
  if (semnum == 0){ 
    if ((sem_id = semget(keyval, 0, 0)) < 0) {
      return -1;
    }
  }
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

void close_sem(int sem_id){
  if ((semctl(sem_id,0,IPC_RMID)) < 0) {
    printf("error deleting semafor %d\n",sem_id); 
    exit(2);
  }
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

void op_sem(int semid, struct sembuf *sops){
  if (semop(semid,sops,1) < 0) {
    printf("semop error\n");
    exit(2);
  }
}

int main(int argc, char **argv){
  
  key_t key;
  int shm_id,sem_id,pid;
  int n1,m1,n2,m2;
  int *seg_ptr, *buf;
  int size, **mas1, *mas2, *mas_comp;
  int i,j,k,sum;
  struct sigaction sa;
  if (argc < 2) {printf("Usage: shmsem s | c\n");exit(2);}
  
  if ((key = ftok(argv[0],'a')) < 0) {perror("ftok");exit(2);}
  switch (argv[1][0]){
  case ('s'): 
    printf("n1: "); scanf("%d", &n1);
    printf("m1: "); scanf("%d", &m1);
    printf("n2: "); scanf("%d", &n2);
    printf("m2: "); scanf("%d", &m2);
    if (m1 != n2){
      printf("Error: Wrong sizes");
      exit(2);
    }
    size = sizeof(int)*n1*sizeof(int)*m1 + sizeof(int)*n2*sizeof(int)*m2 + 3*sizeof(int) + sizeof(int) * n1 * sizeof(int) * m2;
    if ((shm_id = open_seg(key,size)) < 0){
      printf("open_seg error\n");
      exit(2);
    }
    if ((sem_id = open_sem(key,2)) < 0){
      printf("open_sem error\n");
      exit(2);
    }
    seg_ptr = attach_seg(shm_id);
    buf = seg_ptr;
    seg_ptr[0] = n1;
    seg_ptr[1] = m1;
    seg_ptr[2] = m2;
    
    srand(key);
    for (i = 3; i < n1*m1 + n2*m2 + 3; i++){
      seg_ptr[i] = rand() %10 + 1;
    }
    for (i = 0; i < n1; i++){
      for (j = 0; j < m1; j++){
        printf("%d ", seg_ptr[3 + i*m1 +j]);
      }
      printf("\n");
    }
    printf("\n");
    for (i = 0; i < n2; i++){
      for (j = 0; j < m2; j++){
        printf("%d ", seg_ptr[3 + n1*m1 + i*m2 +j]);
      }
      printf("\n");
    }
    
    op_sem(sem_id,&m_lock[0]);
    seg_ptr += n1*m1 + n2*m2 + 3;
    
    printf("answer:\n");
    for (i = 0; i < n1; i++){
      for (j = 0; j < m2; j++){
        printf("%d ", seg_ptr[i*m2 +j]);
      }
      printf("\n");
    }
    detach_seg((char *)buf);
    close_seg(shm_id);
    close_sem(sem_id);
    break;
  case('c'):
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigchldhandler;
    if (sigaction(SIGCHLD, &sa, 0) < 0){
      perror("sigaction");
      exit(0);
    }
    if ((shm_id = open_seg(key,0)) <0){
      printf("open_seg error\n");
      exit(2);
    }
    seg_ptr = attach_seg(shm_id);
    n1 = seg_ptr[0]; m1 = seg_ptr[1]; n2 = seg_ptr[1]; m2 = seg_ptr[2];
    mas1 = (int **) malloc(sizeof(int) * n1);
    mas2 = (int *) malloc(sizeof(int) * m2);
    mas_comp = (int *) malloc(sizeof(int) * m2);
    for(i = 0; i < n1; i++){
      mas1[i] = (int *) malloc(sizeof(int) * m1);
      for(j = 0; j < m1; j++){
        mas1[i][j] = seg_ptr[3 + i*m1 + j];
      }
    }
    if ((sem_id = open_sem(key,0)) < 0){
      printf("open_sem error\n");
      exit(2);
    }
    op_sem(sem_id,&p_unlock[0]);
    for(i = 0; i < m2; i++){
      if ((pid = fork()) < 0){ exit(0);};
      if (pid == 0){
        for(j = 0; j < n2; j++){
          op_sem(sem_id,&p_lock[0]);
          mas2[j] = seg_ptr[3 + n1*m1 + j*m2 + i];
          op_sem(sem_id,&p_unlock[0]);
        }
        sum = 0;
        for (j = 0; j < n1; j++){
          for (k = 0; k < n2; k++){
            sum += mas1[j][k]*mas2[k];
          }
          op_sem(sem_id,&p_lock[0]);
          seg_ptr[3 + n1*m1 + n2*m2 + j*m2 + i] = sum;
          op_sem(sem_id,&p_unlock[0]);
          sum = 0;
        }
        exit(0);
      }
    }
    while (die < m2);
    printf("done.\n");
    op_sem(sem_id,&m_unlock[0]);
    break;
  default: printf("Usage: shmsem s | c\n");break;
  }
  
  return 0;
}