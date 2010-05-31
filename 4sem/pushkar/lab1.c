#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

#define YES 1
#define NO 0

double Function(double x, double y) {
  return exp(-(x*x+y*y))*sin(x);
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
  
  for (j = i - 1; j >= 0; j--){ 
        if(index(buf[j].x, 'e')!=NULL){
      strcpy(buf[j].x, "0");
     }
    if(index(buf[j].y, 'e')!=NULL){
      strcpy(buf[j].y, "0");
    } 
    fprintf(file,"%s\t%s\n", buf[j].x, buf[j].y);
  }
}


void Euler(double h, double x_0, double y_0, double x_start, double x_end ){
  double x = x_0, y = y_0;  
  FILE* tmp = fopen("tmp", "w+");
  FILE* file = fopen("euler", "a");
      
  while(x > x_start){    
    if (y < 0) break;
    y = y - h*Function(x, y);
    x = x - h;
    if (y < 0) break;
    fprintf(tmp,"%g\t%g\n", x, y);
  }
  
  invert_copy(file, tmp);
       
  x = x_0; y = y_0;
  fprintf(file,"%g\t%g\n", x_0, y_0);
  
  while(x < x_end){
    if (y < 0) break;
    y = y + h*Function(x, y); 
    x = x + h;
    if (y < 0) break;
    fprintf(file,"%g\t%g\n", x, y);
  }
  
  fclose(file);
  fclose(tmp);
  unlink("tmp");
}

void Runge_Kutt_2(double h, double x_0, double y_0, double alpha, double x_start, double x_end ){
  double x = x_0, y = y_0;
  
  FILE* tmp = fopen("tmp", "w+");
  FILE* file = fopen("runge_kutt_2", "a");
  
  while (x > x_start) {
    if (y - h/(2*alpha)*Function(x, y) < 0) break;
    y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
    x = x - h;
    if (y < 0) break;
    fprintf(tmp,"%g\t%g\n", x, y);
  }

  invert_copy(file, tmp);
  
  x = x_0; y = y_0;
  fprintf(file,"%g\t%g\n", x_0, y_0);  

  while (x < x_end) {
    if (y + h/(2*alpha)*Function(x, y) < 0) break;
    y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
    x = x + h;
    if (y < 0) break;
    fprintf(file,"%g\t%g\n", x, y);
  }  
  
  fclose(file);
  fclose(tmp);
  unlink("tmp");
}

void Runge_Kutt_4(double h, double x_0, double y_0, double x_start, double x_end ){
  double k1, k2, k3, k4;
  double x = x_0, y = y_0;

  FILE* tmp = fopen("tmp", "w+");
  FILE* file = fopen("runge_kutt_4", "a");

  while (x > x_start) {
    k1 = Function(x, y);
    if (y - h/2*k1 < 0) break;
    k2 = Function(x - h/2, y - h/2*k1);
    if (y - h/2*k2 < 0) break;
    k3 = Function(x - h/2, y - h/2*k2);
    if (y - h*k3 < 0) break;
    k4 = Function(x - h, y - h*k3);
    
    y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
    x = x - h;
    if (y < 0) break;
    fprintf(tmp,"%g\t%g\n", x, y);
  }

  invert_copy(file, tmp);
  
  x = x_0; y = y_0;
  fprintf(file,"%g\t%g\n", x_0, y_0);  

  while (x < x_end) {
    k1 = Function(x, y);
    if (y + h/2*k1 < 0) break;
    k2 = Function(x + h/2, y + h/2*k1);
    if (y + h/2*k2 < 0) break;
    k3 = Function(x + h/2, y + h/2*k2);
    if (y + h*k3 < 0) break;
    k4 = Function(x + h, y + h*k3);
    
    y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
    x = x + h;
    if (y < 0) break;
    fprintf(file,"%g\t%g\n", x, y);
  }
  
  fclose(file);
  fclose(tmp);
  unlink("tmp");
}



void gnu_title(double x_start, double x_end, int *method){
  FILE *file;
  
  file = fopen("gnu_title", "w");
  fprintf(file, "set xrange[%d:%d]\n", (int)floor(x_start), (int)ceil(x_end));
  fprintf(file,"set title \" Лабораторная работа 1, Костенчук М., 8-ой вариант. y'=e^(−(x*x+y*y))*sin(x)\"\n");
  fprintf(file,"plot");
  if (method[0] == YES) {
    fprintf(file,"'euler' title \"Метод Эйлера\" with lines"); 
  }
  if (method[1] == YES) {
    if (method[0] == YES) fprintf(file,", ");
    fprintf(file,"'runge_kutt_2' title \"Метод Рунге-Кутта 2-ого порядка\" with lines");
  }
  if (method[2] == YES) {
    if (method[0] == YES || method[1] == YES) fprintf(file,", ");
    fprintf(file,"'runge_kutt_4' title \"Метод Рунге-Кутта 4-ого порядка\" with lines");
  }
  fprintf(file,"\npause -1\n"); 

  fclose(file);
}


void init(){
  int N, method[3]; 
  float x_0, y_0,x_end, x_start,alpha, h;
  char n;
  float ptr;
  FILE * file;

  
  method[0] = method[1] = method[2] = NO;
   
  while(1){
    printf("\nИспользовать данные по-умолчанию:  x e [1,2], y(2)=1 ? (y or n) ");
    scanf("%c",&n);
    if(n == 'n' || n == 'y') break;
  }

  printf("\t1. Метод Эйлера\n\t2. Метод Рунге-Кутта 2-ого порядка \n\t3. Метод Рунге-Кутта 4-ого порядка \n\n");
  
  method[0] = method[1] = method[2] = YES;
  if (n == 'n') {

    printf("\n");
    printf("Введите начальную точку отрезка a: ");
    scanf("%f",&x_start);
    
    printf("Введите конечную точку отрезка b: ");
    scanf("%f",&x_end);
    
    if (x_end <= x_start){
      ptr = x_end;
      x_end = x_start;
      x_start = ptr;
    }
    
    while(1) {
      printf("Введите точку x0: ");
      scanf("%f",&x_0);
      if (x_0 < x_start || x_0 > x_end) printf("\nТочка должна принадлежать отрезку [a,b]\n");
      else break;
    } 
    while(1) {
      printf("Введите точку y0: ");
      scanf("%f",&y_0);
    }
    
    while(1){    
      printf("Введите колличество точек: ");
      scanf("%d",&N);
      if(N >= 10 && N <= 100000) break;
      else printf("\nКоличество точек должно быть в промежутке: [10,100 000]\n\n");
    }
    
    while(1){
      printf("Input alpha: ");
      scanf("%f",&alpha);
      if(alpha > 0 && alpha <= 1) break; 
      else printf("\nАльфа должна лежать в промежутке: [0,1]\n\n");
    }
  }
  else {
    N = 20;
    x_start = 1;
    x_end = 2;
    x_0 = 2;
    y_0 = 1;
    alpha = 1;
  }

  h = fabs((x_end - x_start)/N);

  file = fopen("euler", "w");
  fclose(file);
  file = fopen("runge_kutt_2", "w");
  fclose(file);
  file = fopen("runge_kutt_4", "w");
  fclose(file);
  
  if (method[0] == YES){
    Euler(h, x_0, y_0, x_start, x_end);
  }
  if (method[1] == YES){
    Runge_Kutt_2(h, x_0, y_0, alpha, x_start, x_end);
  }
  if (method[2] == YES){
    Runge_Kutt_4(h, x_0, y_0, x_start, x_end );
  }

  gnu_title(x_start, x_end, method);
}
  
int main(){
  system("clear");
  
  printf("\n\t Студент: Костенчук М.\n\t Группа: 4361 \n\t Вариант: 8 \n\t Численное решение задачи Коши для уравнения y'=e^(−(x*x+y*y))*sin(x)\n");

  init();
  system("gnuplot gnu_title");

  return 0;
}
