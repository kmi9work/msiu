# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>

# define WFIL 0
# define WGFIL 1
# define ENDINGS 3

# define XY 1
# define YZ 2
# define XZ 3
# define D3 4
# define FPR2 "%lf %lf\n"
# define FPR3 "%lf %lf %lf\n"

double fi(double x, double y, double z){
  return x*exp(-z);
}

double psi(double x, double y, double z){
  return 1.0/(1 + x*x + y*y);
}

int euler(double x0, double y0, double z0, double a, double b, int number_of_cell, char* str, int proection){
  char *fpr;
  double h = (b-a)/(double)number_of_cell;
  double h0 = h;
  double x = x0, y = y0, z = z0, yn = y0;
  double *first, *second, *third = &z;
  switch(proection){
  case XY:
    first = &x; second = &y; fpr = FPR2;
    break;
  case YZ:
    first = &y; second = &z; fpr = FPR2;
    break;
  case XZ:
    first = &x; second = &z; fpr = FPR2;
    break;
  case D3:
    first = &x; second = &y; fpr = FPR3;
    break;
  default:
    first = &x; second = &y; fpr = FPR2;
    break;
  }    
  FILE* file1 = fopen(str,"w+");
  if(!file1) return 0;
  if(x0 == a){
    for(x = a; x <= b ;x = x + h){
      fprintf(file1,fpr,*first,*second,*third);
      yn = y;
      y=y + h * fi(x, y, z);
      z=z + h * psi(x, yn, z);
    }
  }
  fprintf(file1,"\n\n\n");
  
  if(x0 == b){
    for(x = b; x >= a ; x = x - h){
      fprintf(file1,fpr,*first,*second,*third);
      yn = y;
      y=y - h*fi(x,y,z);
      z=z - h*psi(x,yn,z);
    }
  }
  fprintf(file1,"\n\n\n");
  fclose(file1);
  return 1;
}

int runge_kutt(double x0,double y0,double z0,double a,double b,int number_of_cell, char* str,int proection){
  char* fpr;
  double h = (b-a)/(double)number_of_cell;
  double h0 = h;
  double x = x0, y = y0 ,z = z0;
  double k1,k2,k3,k4,q1,q2,q3,q4;
  double *first, *second, *third = &z;
  switch(proection){
  case XY:
    first = &x; second = &y; fpr = FPR2;
    break;
  case YZ:
    first = &y; second = &z; fpr = FPR2;
    break;
  case XZ:
    first = &x; second = &z; fpr = FPR2;
    break;
  case D3:
    first = &x; second = &y; fpr = FPR3;
    break;
  default:
    first = &x; second = &y; fpr = FPR2;
    break;
  }    
  FILE* file1 = fopen(str,"w+");
  if(!file1) return 0;
  if(x0 == b){    
    for(x = b; x >= a; x = x - h){
      k1 = fi(x, y, z);
      q1 = psi(x, y, z);
      k2 = fi(x - h/2.0, y - h/2.0 * k1, z - h/2.0 * q1);
      q2 = psi(x - h/2.0, y - h/2.0 * k1, z - h/2.0 * q1);
      k3 = fi(x - h/2.0, y - h/2.0 * k2, z-h/2.0 * q2);
      q3 = psi(x - h/2.0, y - h/2.0 * k2, z - h/2.0 * q2);
      k4 = fi(x - h, y - h * k3, z - h * q3);
      q4 = psi(x - h, y - h * k3, z - h * q3);
      y = y - h/6 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
      z = z - h/6 * (q1 + 2.0 * q2 + 2.0 * q3 + q4); 
      fprintf(file1, fpr, *first, *second, *third);
    }
  }
  if(x0 == a){    
    for(x = a; x <= b; x = x + h){
      k1 = fi(x, y, z);
      q1 = psi(x, y, z);
      k2 = fi(x + h/2.0, y + h/2.0 * k1, z + h/2.0 * q1);
      q2 = psi(x + h/2.0, y + h/2.0 * k1, z + h/2.0 * q1);
      k3 = fi(x + h/2.0, y + h/2.0 * k2, z + h/2.0 * q2);
      q3 = psi(x + h/2.0, y + h/2.0 * k2, z + h/2.0 * q2);
      k4 = fi(x + h, y + h * k3, z + h * q3);
      q4 = psi(x + h, y + h * k3, z + h * q3);
      y = y + h/6 * (k1 + 2.0*k2 + 2.0 * k3 + k4);
      z = z + h/6 * (q1 + 2.0 * q2 + 2.0 * q3 + q4); 
      fprintf(file1,fpr,*first,*second,*third);
    }
  }
  fclose(file1);
  return 1;
}

void error(int err){
  switch(err){
  case WFIL:
    fprintf(stderr,"Ошибка записи файла: не могу создать system.dat\n");
    break;
  case WGFIL:
    fprintf(stderr,"Ошибка записи файла: не могу создать system.gnu\n");
    break;
  case ENDINGS:
    fprintf(stderr,"Ошибка значения: левый конец отрезка равен правому\n");
    break;
  default:
    fprintf(stderr,"Неизвестная ошибка\n");
    break;
  }
  return;
}

void scan_num(double* a,double* b,double* x0,double* y0,double* z0,int* cell){
  printf("Введите a -> ");
  scanf("%lf",a);
  printf("Введите b -> ");
  scanf("%lf",b);
  if(*a==*b){
    error(ENDINGS);
    exit(11);
  }
  
  *x0 = *a;
  if(*a > *b){
    *a=*a+*b;
    *b=*a-*b;
    *a=*a-*b;
  }
  
  printf("Введите y0 ->");
  scanf("%lf",y0);
  printf("Введите z0 -> ");
  scanf("%lf",z0);
  while(1){
    printf("Введите кол-во ячеек -> ");
    scanf("%d",cell);
    if(*cell >= 10) break;
    printf("Слишком маленькое кол-во ячеек, для данной задачи лучше использовать не меньше 10!\n");
  }

  return;
}  

void create_gnu(double x0,double y0,double z0,double a,double b,int mode){
  FILE* file2 = fopen("system.gnu","w+");
  if(!file2) {
    error(WGFIL);
    return;
  }
  fprintf(file2,"set title \"y' = x*e^(-z) ; z' = 1/(1+x^2+y^2); x0=%f, y0=%f, z0=%f, x c [%f,%f].\"\n",x0,y0,z0,a,b);
  switch(mode){
  case XY:
    fprintf(file2,"set xlabel \"x\"\n");
    fprintf(file2,"set ylabel \"y\"\n");
    fprintf(file2,"plot 'system1.dat' title \"Метод Эйлера\" with lines, 'system2.dat' title \"Метод Рунге-Кутта\" with lines\n");
    break;
  case YZ:
    fprintf(file2,"set xlabel \"y\"\n");
    fprintf(file2,"set ylabel \"z\"\n");
    fprintf(file2,"plot 'system1.dat' title \"Метод Эйлера\" with lines, 'system2.dat' title \"Метод Рунге-Кутта\" with lines\n");
    break;
  case XZ:
    fprintf(file2,"set xlabel \"x\"\n");
    fprintf(file2,"set ylabel \"z\"\n");
    fprintf(file2,"plot 'system1.dat' title \"Метод Эйлера\" with lines, 'system2.dat' title \"Метод Рунге-Кутта\" with lines\n");
    break;
  case D3:
    fprintf(file2,"set parametric\n");
    fprintf(file2,"splot 'system1.dat' title \"Метод Эйлера\" with lines, 'system2.dat' title \"Метод Рунге-Кутта\" with lines\n");
    break;
  }  
  fprintf(file2,"pause -1\n");
  fclose(file2);
  return;
}

int visualize(void){
  printf("\ny' = x*e^(-z)\nz' = 1/(1+x^2+y^2)\ny0 = 1 \nz0 = 0 \nx c [0,1].\n"); 
  int cell = 100, mode;
  char y_n = 'y';
  double a = 0.0, b = 1.0, x0 = 0.0, y0 = 1.0, z0 = 0.0;

  while(1){
    printf("\nИспользовать значения по умолчанию? (y or n) ");
    scanf("%c",&y_n);
    if(y_n == 'n' || y_n == 'y') break;
  }


  if(y_n == 'n') scan_num(&a, &b, &x0, &y0, &z0, &cell);

  printf("График отобразить в проекции на:\n");
  printf("XY - 1\n");
  printf("YZ - 2\n");
  printf("XZ - 3\n");
  printf("3D - 4\n");
  scanf("%d",&mode);
  
  if(!euler(x0, y0, z0, a, b, cell, "system1.dat", mode)) {
    error(WFIL);
    return 0;
  }
  if(!runge_kutt(x0,y0,z0,a,b,cell, "system2.dat", mode)) {
    error(WFIL);
    return 0;
  }
  create_gnu(x0, y0, z0, a, b, mode);
  return 1;
}

int main(void){
  system("clear");
  printf("Решение задачи Коши для системы двух дифференциальных уравнений методом Рунге-Кутта 4-го порядка точности.\n(гр 4361, Костенчук М.И., вариант 8)");
  visualize();
  system("gnuplot system.gnu");
  unlink("system.gnu");
  unlink("system1.dat");
  unlink("system2.dat");
  return 0;
}


