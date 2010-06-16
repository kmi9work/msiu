#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>


#define YES 1
#define NO 0


double Function(double x, double y) {
  return exp((-1)*(x*x+y*y))*sin(x);
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
    y = y - h*Function(x, y);
    x = x - h;
    fprintf(tmp,"%g\t%g\n", x, y);
  }

  invert_copy(file, tmp);

  x = x_0; y = y_0;
  fprintf(file,"%g\t%g\n", x_0, y_0);

  while(x < x_end){
    y = y + h*Function(x, y);
    x = x + h;
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
    y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
    x = x - h;
    fprintf(tmp,"%g\t%g\n", x, y);
  }

  invert_copy(file, tmp);

  x = x_0; y = y_0;
  fprintf(file,"%g\t%g\n", x_0, y_0);

  while (x < x_end) {
    y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
    x = x + h;
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
    k2 = Function(x - h/2, y - h/2*k1);
    k3 = Function(x - h/2, y - h/2*k2);
    k4 = Function(x - h, y - h*k3);

    y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
    x = x - h;
    fprintf(tmp,"%g\t%g\n", x, y);
  }

  invert_copy(file, tmp);

  x = x_0; y = y_0;
  fprintf(file,"%g\t%g\n", x_0, y_0);  

  while (x < x_end) {
    k1 = Function(x, y);
    k2 = Function(x + h/2, y + h/2*k1);
    k3 = Function(x + h/2, y + h/2*k2);
    k4 = Function(x + h, y + h*k3);

    y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
    x = x + h;
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
  fprintf(file,"set title \"Костенчук М.И. (Вариант 8)  y'= e^(-(x^2+y^2))*sin(x)\"\n");
  fprintf(file,"plot");
  if (method[0] == YES) {
    fprintf(file,"'euler' title \"Метод Эйлера\" with lines");
  }
  if (method[1] == YES) {
    if (method[0] == YES) fprintf(file,", ");
    fprintf(file,"'runge_kutt_2' title \"Метор Рунге-Кутта 2-ого порядка точности\" with lines");
  }
  if (method[2] == YES) {
    if (method[0] == YES || method[1] == YES) fprintf(file,", ");
    fprintf(file,"'runge_kutt_4' title \"Метор Рунге-Кутта 4-ого порядка точности\" with lines");
  }
  fprintf(file,"\npause -1\n");

  fclose(file);
}


void init(){
  int N, method[3];
  float x_0, y_0, x_end, x_start, alpha, h;
  char n;
  float ptr;
  FILE * file;



  method[0] = method[1] = method[2] = YES;  
  printf("1. Метод Эйлера \n2. Метод Рунге-Кутта 2-го порядка точности \n3. Метод Рунге-Кутта 4-го порядка точности \n\n");
  while(1){
    printf("\nИспользовать значения по умолчанию (0<=x<=2, y(0)=1) ? (y or n) ");
    scanf("%c",&n);
    if(n == 'n' || n == 'y') break;
  }

  if (n == 'n') {

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
      if (x_0 < x_start || x_0 > x_end) printf("\nТочка должна находиться внутри отрезка!\n");
      else break;
    } 
    printf("Введите y0: ");
    scanf("%f",&y_0);

    while(1){
      printf("Введите количество узлов: ");
      scanf("%d",&N);
      if(N >= 10 && N <= 100000) break;
      else printf("\n> 10, но < 100000)\n\n");
    }

    while(1){
      printf("Введите alpha: ");
      scanf("%f",&alpha);
      if(alpha > 0 && alpha <= 1) break; 
      else printf("\nalpha должно принадлежать интервалу: (0, 1]\n\n");
    }
  }
  else {
    N = 20;
    x_start = 0;
    x_end = 2;
    x_0 = 0;
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
  printf("Решение задачи Коши для уравнения y'= e^(-(x^2+y^2))*sin(x); \nгр. 4361, Костенчук М.И., вариант 8\n");
  init();
  system("gnuplot gnu_title");
  return 0;
}
