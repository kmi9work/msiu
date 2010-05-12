#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>

#define SEGSIZE 1024

static struct sembuf m_lock[2] = {{0,0,0},{0,1,0}};
static struct sembuf m_unlock[1] = {{ 0,-1,0}};
static struct sembuf p_wait[1] = {{ 1,0,0 }};
static struct sembuf p_start[1] = {{ 1,1,0 }};
static struct sembuf p_stop[1] = {{ 1,-1, IPC_NOWAIT}};


int open_seg(key_t keyval, int segsize){
   int shm_id;
   if (segsize == 0){ 
      if ((shm_id = shmget(keyval, 0, 0)) < 0) {return -1;}
      
   }
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

char *attach_seg(int shm_id){
   char *shm_seg;
   if (*(shm_seg = shmat(shm_id, 0, 0)) < 0) {
     printf("error attaching %d\n", shm_id); exit(2);
   }else{ 
     return shm_seg;
   }
}

void detach_seg(char *seg_ptr){
   if ((shmdt(seg_ptr)) < 0) {
     printf("error detaching %p\n",seg_ptr); exit(2);
   }
}

void close_seg(int shm_id){
   if ((shmctl(shm_id,IPC_RMID,0)) < 0) {
     printf("error deleting seg %d\n",shm_id); exit(2);
   }
}

int open_sem(key_t keyval, int semnum){
   int sem_id;
   if (semnum == 0){ 
      if ((sem_id = semget(keyval, 0, 0)) < 0) {return -1;}
      
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
     printf("error deleting semafor %d\n",sem_id); exit(2);
   }
}

int get_sem_val( int sid, int semnum )
{
  return( semctl(sid, semnum, GETVAL, 0));
}

int set_sem_val(int sid, int semnum, int val){
 union semun {
                  int val;
                  struct semid_ds *buf;
                  unsigned short  *array;
              } semarg;
  
  semarg.val = val;
  return (semctl(sid,semnum,SETVAL,semarg));
}

void sem_print(int sem_id, int snum, char *msg){
int i;
for (i=0;i<snum;i++)
	printf("%s -> sem: %d val: %d\n\r", msg, i, get_sem_val( sem_id, i ));
}

int main(int argc, char **argv){

  int i;
  int n1,n2,m1,m2;
  key_t key;
  int shm_id,sem_id;
  char *seg_ptr, *buf;
  
  if (argc < 2) {printf("Usage: shmsem s | c\n");exit(2);}
  
  if ((key = ftok(argv[0],'a')) < 0) {perror("ftok");exit(2);}
  buf = malloc(SEGSIZE);
  switch (argv[1][0]){
  case ('s'):
/*
    printf("n1: "); scanf("%d", &n1);
    printf("m1: "); scanf("%d", &m1);
    printf("n2: "); scanf("%d", &n2);
    printf("m2: "); scanf("%d", &m2);
    arr = (int *) malloc(sizeof(int) * n1 * sizeof(int) * m1 * sizeof(int) + n2 *  sizeof(int) * m2 + 3*sizeof(int));
    arr[0] = n1;
    arr[1] = m1;
    arr[2] = m2;
    size = sizeof(int) * n1 * sizeof(int) * m1 * sizeof(int) + n2 *  sizeof(int) * m2 + 3*sizeof(int) + sizeof(int) * n1 * sizeof(int) * m2;
    srand(key);
    for (i = 0; i < n1*m1+n2*m2; i++){
      arr[i] = rand() %100 + 1;
    }*/
    if ((shm_id = open_seg(key, SEGSIZE)) < 0){
      printf("open_seg error\n");
      exit(2);
    }
    if ((sem_id = open_sem(key,2)) < 0){
      printf("open_sem error\n");
      exit(2);
    }
    seg_ptr = attach_seg(shm_id);
    set_sem_val(sem_id, 0, 0);
    set_sem_val(sem_id, 1, 1);
    do {
      if (semop(sem_id,&p_wait[0],1) < 0) {
        printf("semop error 1\n");
        exit(2);
      }
      if (semop(sem_id,&m_lock[0],2) < 0) {
        perror("semop error 2: ");
        exit(2);
      }
      strcpy(buf,seg_ptr);
      if (semop(sem_id,&m_unlock[0],1) < 0) {
        printf("semop error 3\n");
        exit(2);
      }
      if (strcmp(buf,"exit")) {
        if (semop(sem_id,&p_start[0],1) < 0) {
          printf("semop error 2\n");
          exit(2);
        }
      }
      
    } while (strcmp(buf,"exit"));
    if (semop(sem_id,&p_wait[0],1) < 0) {
      printf("semop error 1\n");
      exit(2);
    }
    detach_seg(seg_ptr);
    close_seg(shm_id);
    close_sem(sem_id);
    break;
  case ('c'):
    if ((shm_id = open_seg(key,0)) <0 ){
      printf("open_seg error\n");
      exit(2);
    }
    
    seg_ptr = attach_seg(shm_id);
    printf("attach at %p\n",seg_ptr);
    
    if ((sem_id = open_sem(key,0)) < 0){
      printf("open_sem error\n");
      exit(2);
    }
    
    /*	printf("---p_start----\n");*/
    /*	if (semop(sem_id,&p_start[0],1) < 0) {*/
    /*		printf("semop error 2\n");*/
    /*		exit(2);*/
    /*	}*/
    sem_print(sem_id,2,"client");
    
    scanf("%s",buf);
    
    printf("---m_lock----\n");
    if (semop(sem_id,&m_lock[0],2) < 0) {
      printf("semop error 1\n");
      exit(2);
    }
    sem_print(sem_id,2,"client");
    
    sprintf(seg_ptr,buf);
    printf("---m_unlock----\n");
    if (semop(sem_id,&m_unlock[0],1) < 0) {
      printf("semop error 3\n");
      exit(2);
    }
    sem_print(sem_id,2,"client");
    free(buf);
    detach_seg(seg_ptr);
    /*	sem_print(sem_id,2,"---m_unlock----\nclient");*/
    if (semop(sem_id,&p_stop[0],1) < 0) {
      printf("semop error 2\n");
      exit(2);
    }
    sem_print(sem_id,2,"client");
    break;
  default: printf("Usage: shmsem s | c\n");break;
  }
  return 0;
}

