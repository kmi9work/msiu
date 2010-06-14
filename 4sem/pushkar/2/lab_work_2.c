#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>


#define YES 1
#define NO 0

double  err = 0.0000001;  


double Function(double x, double y) {
  return y*tan(x)+1/cos(x);
}

struct point{
  char x[10],y[10];
} buf[100001];


void invert_copy(FILE *file, FILE *tmp) {
  int i = 0, j;
  char *word, *str;
  char buffer[255];
  
  fseek(tmp, 0, SEEK_SET);
  
  do {
    if((str = fgets (buffer, 255, tmp)) != NULL){
      word = strtok(str,"\t\n");
      strcpy(buf[i].x, word);
      word = strtok(NULL,"\t\n");
      strcpy(buf[i++].y, word);
    }
  } while (!feof(tmp));
  
  for (j = i - 2; j >= 0; j--){ 
    
    fprintf(file,"%s\t%s\n", buf[j].x, buf[j].y);
  }
}

double search(double x, int flag){
  int k = 0;
  if(flag==1)
    for(; x > M_PI/2+k*(M_PI); k++);
  else if(flag==-1)
    for(; x < -M_PI/2+k*(-M_PI); k++);
  
  return (flag*M_PI/2)+k*(flag*M_PI);
}


void Euler(double h, double x_0, double y_0, double x_start, double x_end, double e ){
  double x = x_0, y = y_0, h_start = h;
  double left, right;
  FILE* tmp = fopen("tmp", "w+");
  FILE* file = fopen("method1", "a");

  if(x_0 > 0){
    right = search(x_0,1);
    left = right - M_PI;
  }else if(x_0 < 0){
    left = search(x_0,-1);
    right = left + M_PI;
  }else{
    left = -M_PI/2;
    right = M_PI/2;
  }

  /*printf("x_0 = %lf \n",x_0);*/
  
  /*printf(" left = %lf, right = %lf\n",left,right);*/
  
  if(x_start > left ){
      while(x-h > x_start){    
      y = y - h*Function(x, y);
      x = x - h;
      fprintf(tmp,"%lf\t%lf\n", x, y);
    }
    y = y - h*Function(x_start, y);
    fprintf(tmp,"%lf\t%lf\n", x_start, y);

  }else{
      while(x - left > e){    
      if(x - left < h_start+err) h /= 2;
      y = y - h*Function(x, y);
      x = x - h;
      if(x > left)fprintf(tmp,"%lf\t%lf\n", x, y);
    }    
  }

  invert_copy(file, tmp);
  
  x = x_0; y = y_0; h = h_start;
  fprintf(file,"%lf\t%lf\n", x_0, y_0);

  if(x_end < right){
     while(x+h < x_end){ 
      y = y + h*Function(x, y); 
      x = x + h;
      if(x < right)fprintf(file,"%lf\t%lf\n", x, y);
    }
    y = y + h*Function(x_end, y); 
    fprintf(file,"%lf\t%lf\n", x_end, y);
  }else{
      while(x < right - e){
      if(right - x < h_start+err) h /= 2;
      y = y + h*Function(x, y); 
      x = x + h;
      fprintf(file,"%lf\t%lf\n", x, y);
    }
  }
  fclose(file);
  fclose(tmp);
  unlink("tmp");
}



void Runge_Kutt_2(double h, double x_0, double y_0, float alpha, double x_start, double x_end, double e ){
  double x = x_0, y = y_0, h_start = h;
  double left, right;
  FILE* tmp = fopen("tmp", "w+");
  FILE* file = fopen("method2", "a");

  if(x_0 > 0){
    right = search(x_0,1);
    left = right - M_PI;
  }else if(x_0 < 0){
    left = search(x_0,-1);
    right = left + M_PI;
  }else{
    left = -M_PI/2;
    right = M_PI/2;
  }

  /*printf(" left = %lf, right = %lf\n",left,right);*/
  
  if(x_start > left ){
    while(x-h > x_start){
      y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
      x = x - h;
      fprintf(tmp,"%lf\t%lf\n", x, y);
    }
      y = y - h*((1 - alpha)*Function(x_start, y) + alpha*Function(x_start - h/(2*alpha), y - h/(2*alpha)*Function(x_start, y)));
      fprintf(tmp,"%lf\t%lf\n", x_start, y);

  }else{
     while(x - left > e){    
      if(x - left < h_start+err) h /= 2;
      y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
      x = x - h;
      if(x > left)fprintf(tmp,"%lf\t%lf\n", x, y);
    }    
  }

  invert_copy(file, tmp);
  
  x = x_0; y = y_0; h = h_start;
  fprintf(file,"%lf\t%lf\n", x_0, y_0);

  if(x_end < right){
    while(x+h < x_end){ 
      y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
      x = x + h;
      fprintf(file,"%lf\t%lf\n", x, y);
    }
    y = y + h*((1 - alpha)*Function(x_end, y) + alpha*Function(x_end + h/(2*alpha), y + h/(2*alpha)*Function(x_end, y)));
    fprintf(file,"%lf\t%lf\n", x_end, y);
  }else{
    while(x < right - e){
      if(right - x < h_start+err) h /= 2;
      y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
      x = x + h;
      if(x < right)fprintf(file,"%lf\t%lf\n", x, y);
    }
  }


  fclose(file);
  fclose(tmp);
  unlink("tmp");
}

void Runge_Kutt_4(double h, double x_0, double y_0, double x_start, double x_end,double e ){
  double k1, k2, k3, k4;
  double x = x_0, y = y_0, h_start = h;
  double left, right;
  FILE* tmp = fopen("tmp", "w+");
  FILE* file = fopen("method3", "a");

  if(x_0 > 0){
    right = search(x_0,1);
    left = right - M_PI;
  }else if(x_0 < 0){
    left = search(x_0,-1);
    right = left + M_PI;
  }else{
    left = -M_PI/2;
    right = M_PI/2;
  }

  /*printf(" left = %lf, right = %lf\n",left,right);*/
 
  if(x_start > left ){
    while(x-h > x_start){
      k1 = Function(x, y);
      k2 = Function(x - h/2, y - h/2*k1);
      k3 = Function(x - h/2, y - h/2*k2);
      k4 = Function(x - h, y - h*k3);
      
      y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
      x = x - h;
      
      fprintf(tmp,"%lf\t%lf\n", x, y);
    }
    k1 = Function(x, y);
    k2 = Function(x_start - h/2, y - h/2*k1);
    k3 = Function(x_start - h/2, y - h/2*k2);
    k4 = Function(x_start - h, y - h*k3);
    y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
    fprintf(tmp,"%lf\t%lf\n", x_start, y);
  }else{
    while(x - left > e){
      if(x-left < h_start+err) h /= 2;
      k1 = Function(x, y);
      k2 = Function(x - h/2, y - h/2*k1);
      k3 = Function(x - h/2, y - h/2*k2);
      k4 = Function(x - h, y - h*k3);
      
      y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
      x = x - h;
      if(x > left )fprintf(tmp,"%lf\t%lf\n", x, y);
    }    
  }

  invert_copy(file, tmp);
  
  x = x_0; y = y_0; h = h_start;
  fprintf(file,"%lf\t%lf\n", x_0, y_0);

  if(x_end < right){
    while(x+h < x_end){ 
      k1 = Function(x, y);
      k2 = Function(x + h/2, y + h/2*k1);
      k3 = Function(x + h/2, y + h/2*k2);
      k4 = Function(x + h, y + h*k3);
      
      y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
      x = x + h;
      
      fprintf(file,"%lf\t%lf\n", x, y);
    }
    
    k1 = Function(x_end, y);
    k2 = Function(x_end + h/2, y + h/2*k1);
    k3 = Function(x_end + h/2, y + h/2*k2);
    k4 = Function(x_end + h, y + h*k3);
    
    y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
    
    fprintf(file,"%lf\t%lf\n", x_end, y);
  }else{
    while(x < right - e){
      if(right-x < h_start+err) h /= 2;
      k1 = Function(x, y);
      k2 = Function(x + h/2, y + h/2*k1);
      k3 = Function(x + h/2, y + h/2*k2);
      k4 = Function(x + h, y + h*k3);
      
      y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
      x = x + h;
      if(x < right) fprintf(file,"%lf\t%lf\n", x, y);
      
    }
  }



  fclose(file);
  fclose(tmp);
  unlink("tmp");
}



void gnu_title(double x_start, double x_end){
  FILE *file;
  
  file = fopen("gnu_title", "w");
  fprintf(file, "set xrange[%d:%d]\n", (int)floor(x_start), (int)ceil(x_end));
  fprintf(file,"set title \"Isaev Egor. Variant 2. y'= ytg(x) + 1/cos(x) x c [1,2]\"\n");
  fprintf(file,"plot 'method1' title \"Mthod Elara\" with lines,'method2' title \"Mthod Runge-Kuta 2-go poriadka\" with lines,'method3' title \"Mthod Runge-Kuta 4-go poriadka\" with lines\n");
  fprintf(file,"pause -1\n"); 

  fclose(file);
}





void init(){
  int N, method[3]; 
  float x_0, y_0,x_end, x_start,alpha, h,e;
  char n;
  float ptr;

  FILE * file;
  
  
  method[0] = method[1] = method[2] = YES;


    while(1){
    printf("\nВводить данные с терминала (y or n)? ");
    scanf("%c",&n);
    if(n == 'n' || n == 'y') break;
  }

  printf("\t1. Метод Эйлера\n\t2. Метод Рунге-Кутта второго порядка точности\n\t3. Метод Рунге-Кутта четвертого порядка точности \n\n");

  
  if (n == 'y') {
    x_start = 0;
    x_end = 1;
    printf("\nВведите начало отрезка a: ");
    scanf("%f",&x_start);
    
    printf("Введите конец отрезка b: ");
    scanf("%f",&x_end);
    if (x_end <= x_start){
      ptr = x_end;
      x_end = x_start;
      x_start = ptr;
    }
    while(1) {
      printf("Введите x0: ");
      scanf("%f",&x_0);
      if (x_0 < x_start || x_0 > x_end) printf("\nТочка должна находиться внутри отрезка\n");
      else break;
    } 
    
    while(1) {
      printf("Введите y0: ");
      scanf("%f",&y_0);
      break;
    }
    
    while(1){    
      printf("Введите количество узлов: ");
      scanf("%d",&N);
      if(N >= 10 && N <= 100000) break;
      else printf("\nЖелательно, больше 10 (но менее 100 000)\n\n");
    }
    
    while(1){
      printf("Введите alpha: ");
      scanf("%f",&alpha);
      if(alpha > 0 && alpha <= 1){
        if(alpha < 0.5)alpha = 0.6;
        break; 
     }else printf("\nalpha должно принадлежать интервалу: (0, 1]\n\n");
    }
    
    printf("Введите e: ");
    scanf("%f",&e);

  } else {
    N = 100; x_start = 1; x_end = 2; x_0 = 1; y_0 = 0; alpha = 1; e = 0.01;
  }
  
  h = fabs((x_end - x_start)/N);


  file = fopen("method1", "w");
  fclose(file);
  file = fopen("method2", "w");
  fclose(file);
  file = fopen("method3", "w");
  fclose(file);

  /*printf("x_0 = %lf \n",x_0);*/

  
  if (method[0] == YES){
    Euler(h, x_0, y_0, x_start, x_end, e);
  }
  if (method[1] == YES){
    Runge_Kutt_2(h, x_0, y_0, alpha, x_start, x_end, e);
  }
  if (method[2] == YES){
    Runge_Kutt_4(h, x_0, y_0, x_start, x_end, e);
  }


  gnu_title(x_start, x_end);

}
  
int main(){
  system("clear");
  
  printf("\n\t Студент: Исаев Егор \n\t Группа:  4361 \n\t Вариант: 2 \n\t Решение задачи Коши для уравнения y' = y*tg(x)+1/cos(x) x c [1;2]\n");

  init();
  system("gnuplot gnu_title"); 
  return 0;
}
 
