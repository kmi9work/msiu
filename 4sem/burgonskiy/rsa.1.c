#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BIG unsigned long long
#define COMPOSITE (0)
#define PRIME (1)
#define TEST (10)

typedef struct key{
  BIG e;
  BIG n;
} key;

BIG my_pow(BIG a, BIG p,BIG n){
  BIG res=1;
  while(p){ 
    if(p&1) {
      res*=a;
      res=res%n;
    }
    a*=a;
    a=a%n;
    p>>=1;
  }
  return res;
}

int witness(BIG a, BIG n){
  BIG d=1,b=n-1,c=0;
  while(b){
    if((b&1)==1){
      d=(a*d)%n;
    }
    c=a;
    a=(a*a)%n;
    b=b>>1;
    if(a==1 && c!=1 && c!=n-1) return COMPOSITE;
  }
  if (d==1) return PRIME;
  else return COMPOSITE;
}

int miller_rabin(BIG n,int s){
  BIG a;
  int j=1;
  for(j=1;j<=s;j++){
    a=rand()%(n-1)+1;
    if(witness(a,n)==COMPOSITE)
      return COMPOSITE;
  }
  return PRIME;
}

long long x,y;
BIG d;

BIG extend_gcd(BIG a,BIG b){
  long long t;
  if(b==0){
    d=a;
    x=1;
    y=0;
    return d;
  }
  extend_gcd(b,a%b);
  t=x-(a/b)*y;
  x=y;
  y=t;
  return d;
}

int size_buf(BIG n){
  int size=-1;
  while((n>>=1)>0) size++;
  return 1;
}

int main(int argc, char** argv){
  BIG p,e,d,fi,n,q,buf,wr,size;
  FILE *sec,*pub;
  int mes,cod;
  int iter;
  struct stat info;
  
  if(argc==4 && argv[1][1]=='g' ){
    srand(getpid());
    //----generate key----
    p=rand()%32767+32768;
    while(miller_rabin(p,TEST)!=PRIME){ p=rand()%32767+32768; /*printf("p=%lld \n",p);*/}
    
    do{
      q=rand()%32767+32768;
      while(miller_rabin(q,TEST)==COMPOSITE){ q=rand()%32767+32768; /*printf("q=%lld \n",q);*/}
    }while (p==q);
    
    printf("p=%lld q=%lld\n",p,q);
    
    n=p*q;
    fi=(p-1)*(q-1);
    e=rand()%1023+1;
    while((e&1)==0 || extend_gcd(e,fi)!=1) e=rand()%1023+1;
    
    if(x<0) x+=fi;
    d=x%fi;
    //---write key---
    if((sec=fopen(argv[2],"w+"))==NULL) {perror("Невозможно создать или открыть файл"); exit(0);}
    if((pub=fopen(argv[3],"w+"))==NULL) {perror("Невозможно создать или открыть файл"); fclose(sec);exit(0);}
    fprintf(sec,"%lld %lld\n",d,n);
    fprintf(pub,"%lld %lld\n",e,n);
    fclose(sec);
    fclose(pub);
    printf("Ключи готовы\n");	
  }else if(argc ==5 && argv[1][1]=='c'){
    
    if((pub=fopen(argv[2],"r+"))==NULL){
      printf("Не найден ключ.\n");
      exit(0);
    }
    
    fscanf(pub,"%lld %lld\n",&e,&n);
    if((mes=open(argv[3],O_RDONLY))<0){
      printf("Не найден файл с сообщением.\n");
      fclose(pub);
      exit(0);
    }
    
    if((cod=open(argv[4],O_CREAT|O_RDWR|O_TRUNC , 0755))<0){
      printf("Не найден файл в который осуществлять запись.\n");
      fclose(pub);
      close(mes);
      exit(0);
    }
    //-----Coding----
    if(fstat(mes,&info)<0){
      perror("ошибка в файле ");
      close(cod);
      fclose(pub);
      close(mes);
      exit(0);
    }
    
    wr=info.st_size%(3*sizeof(char));
    if((write(cod,&wr,sizeof(wr)))<0){
      perror("write ");
      close(mes);
      close(cod);
      fclose(pub);
      exit(0);
		}
    
    while((read(mes,&buf,3*sizeof(char)))!=0){
      wr=my_pow(buf,e,n);
      
      if((write(cod,&wr,sizeof(wr)))<0){
	perror("write ");
	close(mes);
	close(cod);
	fclose(pub);
	exit(0);
      }
    }
    
    printf("Операция кодирования завершена\n");	
    close(mes);
    close(cod);
    fclose(pub);
  }else if(argc ==5 && argv[1][1]=='d'){
    
    if((sec=fopen(argv[2],"r+"))==NULL){
      printf("Не найден ключ.\n");
      exit(0);
    }
    fscanf(sec,"%lld %lld\n",&d,&n);
    
    if((cod=open(argv[3],O_RDONLY))<0){
      printf("Не найден файл с сообщением.\n");
      fclose(sec);
      exit(0);
    }
    
    if((mes=open(argv[4],O_CREAT|O_RDWR|O_TRUNC , 0755))<0){
      printf("Не найден файл в который осуществлять запись.\n");
      fclose(sec);
      close(cod);
      exit(0);
    }
    //-----Decoding----
    if((read(cod,&size,sizeof(wr)))<0){
      perror("чтение ");
    }
    
    if(fstat(cod,&info)<0){
      perror("ошибка в файле ");
      close(cod);
      fclose(sec);
      close(mes);
      exit(0);
    }
    
    iter=info.st_size/(sizeof(wr))-1;
    while((read(cod,&buf,sizeof(wr)))>0){
      wr=my_pow(buf,d,n);
      if(iter==1 && size!=0){
	if((write(mes,&wr,size*sizeof(char)))<0){
	  perror("write ");
	  close(mes);
	  close(cod);
	  fclose(sec);
	  exit(0);
	}
      }else{
	if((write(mes,&wr,3*sizeof(char)))<0){
	  perror("write ");
	  close(mes);
	  close(cod);
	  fclose(sec);
	  exit(0);
	}
      }
      iter--;
    }
    printf("Операция декодирования завершена\n");	
    close(mes);
    close(cod);
    fclose(sec);
  }else{
    printf("Использование: %s КЛЮЧ [ФАЙЛЫ] \n -g секретный_ключ открытый_ключ \t \t \t генерация ключей\n -с открытый_ключ сообщение закодированное_сообщение\t для кодирования\n -d секретный_ключ закодированное_сообщение результат\t декодирование\n",argv[0]);
  } 
  return 0;
}
