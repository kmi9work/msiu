# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
#include <unistd.h>


typedef struct item{
  double L;
  double K;
  double y;
} item;


void Sweep(double (*alpha)(double), double (*beta)(double), double (*gama)(double), double A, double B, double ya, double yb, int N){

  item array[N + 1];
  FILE* file = fopen("progonka.dat", "w");
  double a, b, c, f, x = A ;
  double h = (B - A)/N;

  array[0].L = 0;
  array[0].K = ya;
  array[0].y = ya;
  int i;

  for(i = 1; i < N; i++){
    x = x + h;
    a = 2 - alpha(x) * h;
    b = 2 * h * h * beta(x) - 4;
    c = 2 + alpha(x) * h;
    f = 2 * h * h * gama(x);
    array[i].L = (-c)/(b + a * array[i - 1].L);
    array[i].K = (f - a * array[i-1].K)/(b + a * array[i - 1].L);
  }

  array[i].y = yb;
  fprintf(file,"%g\t%g\n", B, yb);

  for(i -= 1; i > 0; i--){
    array[i].y = array[i].L * array[i + 1].y + array[i].K;
    fprintf(file,"%g\t%g\n", A + ((double)i)*h, array[i].y);
  }

  fprintf(file,"%g\t%g\n", A, ya);

  fclose(file);
}


double alpha(double x){
  return -sin(x);
}


double beta(double x){
  return -1;
}


double gama(double x){
  return x;
}


void Create_gnu(double a, double b, double ya, double yb){
  FILE* file = fopen("progonka.gnu","w");
  fprintf(file, "set xrange[%d:%d]\n", (int)floor(a), floor(b)-b < 0 ? (int)floor(b) + 1 : (int)floor(b));
	fprintf(file,"set title \"Костенчук М.И. (Вариант 8)  y'' - sin(x)*y'- y = x\"\n");
  fprintf(file, "plot 'progonka.dat' title \"");
  fprintf(file, "y'' - sin(x)*y'- y = x, x c [%g;%g], y(%g)=%g, y(%g)=%g.\" with lines\n", a, b, a, ya, b, yb);
  fprintf(file,"pause -1\n");
  fclose(file);
}


void Stream_question(){
  int N = 100;
  double a = 0, b = 2, ya = 0, yb = 1;
  double c;
  char n;

  while(1){
    printf("\nИспользовать значения по умолчанию? (a=%g, b=%g, y(a)=%g, y(b)=%g) (y or n) ",a,b,ya,yb);
    scanf("%c",&n);
    if(n == 'n' || n == 'y') break;
  }

  if (n == 'n') {
    printf("\nВведите a: ");
    scanf("%lf",&a);
  
    while(1){
      printf("Введите b: ");
      scanf("%lf",&b);
      if(b == a) printf("Правый конец  не должен быть равен левому\n");
      else break;
    }
  
    if(a > b){
      c = b;
      b = a;
      a = c;
    }
  
    printf("Введите y(a): ");
    scanf("%lf",&ya);
    printf("Введите y(b): ");
    scanf("%lf",&yb);
    printf("Введите количество узлов: ");
    scanf("%d",&N);
    N+=1;
  }

  Sweep(alpha, beta, gama, a, b, ya, yb, N);
  Create_gnu(a, b, ya, yb);
}


int main(){
  system("clear");
  printf("Решение краевой задачи методом прогонки для уравнения y'' - sin(x)*y'- y = x\n(гр 4361, Костенчук М.И., вариант 8)\n");
  Stream_question();
  system("gnuplot progonka.gnu");
  unlink("progonka.dat");
  unlink("progonka.gnu");
return 0;
}







