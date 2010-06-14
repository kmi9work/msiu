#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

#define YES 1
#define NO 0
#define M_PI 3.14159
#define ANTILOOP_LIMIT 1000
double  err = 0.000001;

double Function(double x, double y) {
  return exp(1.0/y)/sin(x);
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
      word = strtok(str,"\t");
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
  if(flag == 1)
    for(; x > k*(M_PI); k++);
  else if(flag==-1)
    for(; x < k*((-1)*M_PI); k++);
  return k*(flag*M_PI);
}

void Euler(double h, double x_0, double y_0, double x_start, double x_end, double e ){
  double x = x_0, y = y_0, h_start = h;
  double left, right;
  FILE* tmp = fopen("tmp", "w+");
  FILE* file = fopen("method_Euler", "w");
  double yprev;
  int antiloop;

  if(x_0 > 0){
    right = search(x_0,1);
    left = right - M_PI;
  }else if(x_0 < 0){
    left = search(x_0,-1);
    right = left + M_PI;
  }else{
    left = 0;
    right = 0;
  }
/*printf("INFO:\nleft %g, right %g, x_0 %g, y_0 %g,\n",left,right,x_0,y_0);*/
  if(x_0==left || x_0==right){
    printf("\nВ точке x_0=%lf особенность\n", x_0);
    exit(1);
  }

/*
  if( x_start >= left && right >= x_end ){
    printf("в интервале особенности нет\n");exit(1);
  }

  if( x_start <= left && left <= x_end ){
    x_point = left;
  }else{
    x_point = right;
  }

  printf("Точка с особенностью: %lf \n\n",x_point);

  if( x_point < x_0 ){//go left
    
  }else{//go right
    
  }
*/

  yprev=0;
  antiloop = 0;
  if(x_start > left){
    while(x-h > x_start+e){/*идём влево от точки пока не уткнемся в заданный пользователем левый конец области...*/
      /*checking by zero on Y*/
      yprev=y;
      y = y - h*Function(x, y);
      x = x - h;

      if( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){
        while( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){        
          while((yprev<0 && y>0) || (yprev>0 && y<0) ){
            h /= 2;
            y = y - h*Function(x, y);
            if( antiloop++ > ANTILOOP_LIMIT )break;
          }
          if((yprev<0 && y>0) || (yprev>0 && y<0) )break;
          fprintf(tmp,"%lf\t%lf\n", x, y);
          if( abs(y) < e ) break;
          yprev=y;
          y = y - h*Function(x, y);
          x = x - h;
          
        }
        break;
      }

      fprintf(tmp,"%lf\t%lf\n", x, y);
    }
    if ( !((yprev<0 && y>0) || (yprev>0 && y<0) || y==0) ){
      y = y - h*Function(x_start, y);
      fprintf(tmp,"%lf\t%lf\n", x_start, y);
    }

  }else{/*строим график слева от точки... тут мы знаем, что особенность слева и надо приближаться с заданной точностью; если приблизились к точке, то начинаем увеличивать */
        /*точность пока не упрёмся в нужную пользователю...*/
    while(x > left+e){

      if(x  < left+h_start+err){
        h /= 2;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }

      yprev=y;
      y = y - h*Function(x, y);
      x = x - h;
/*      printf("left precis[%lf,%lf]\n\n",x,y);*/
      if( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){
        while( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){        
/*          printf("right precis stupe y %lf\n\n",y);*/
          while((yprev<0 && y>0) || (yprev>0 && y<0) ){
            h /= 2;
            y = y - h*Function(x, y);
            if( antiloop++ > ANTILOOP_LIMIT )break;
/*            printf("h/2\n");*/
          }
          if((yprev<0 && y>0) || (yprev>0 && y<0) )break;
          fprintf(tmp,"%lf\t%lf\n", x, y);
          if( abs(y) < e ) break;
/*          printf("---\n");*/
          yprev=y;
          y = y - h*Function(x, y);
          x = x - h;
          
        }
        break;
      }

      if(x > left) fprintf(tmp,"%lf\t%lf\n", x, y);
    }
  }

  invert_copy(file, tmp);
  
  x = x_0; y = y_0; h = h_start;
  fprintf(file,"%lf\t%lf\n", x_0, y_0);

  yprev=0;
  antiloop = 0;
  if(x_end < right){/*просто идём вправо без всякой точности*/
    while(x+h < x_end){

      yprev=y;
      y = y + h*Function(x, y);
      x = x + h;
/*      printf("right [%lf,%lf]\n\n",x,y);*/
      if( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){
        while( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){        
/*          printf("right precis stupe y %lf\n\n",y);*/
          while((yprev<0 && y>0) || (yprev>0 && y<0) ){
            h /= 2;
            y = y + h*Function(x, y);
            if( antiloop++ > ANTILOOP_LIMIT )break;
/*            printf("h/2\n");*/
          }
          if((yprev<0 && y>0) || (yprev>0 && y<0) )break;
          fprintf(tmp,"%lf\t%lf\n", x, y);
          if( abs(y) < e ) break;
/*          printf("---\n");*/
          yprev=y;
          y = y + h*Function(x, y);
          x = x + h;
          
        }
        break;
      }


      fprintf(file,"%lf\t%lf\n", x, y);
    }
    if ( !((yprev<0 && y>0) || (yprev>0 && y<0) || y==0) ){
      y = y + h*Function(x_start, y);
      fprintf(tmp,"%lf\t%lf\n", x_end, y);
    }
  }else{/*справа особенность - идём туда с точностью, нужной пользователю*/
    while(x < right - e){

      if(right < x+h_start+err){
        h /= 2;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }
      yprev=y;
      y = y + h*Function(x, y); 
      x = x + h;

/*      printf("right precis [%lf,%lf]\n\n",x,y);*/
      if( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){
        while( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){        
/*          printf("right precis stupe y %lf\n\n",y);*/
          while((yprev<0 && y>0) || (yprev>0 && y<0) ){
            h /= 2;
            y = y + h*Function(x, y);
            if( antiloop++ > ANTILOOP_LIMIT )break;
/*            printf("h/2\n");*/
          }
          if((yprev<0 && y>0) || (yprev>0 && y<0) )break;
          fprintf(tmp,"%lf\t%lf\n", x, y);
          if( abs(y) < e ) break;
/*          printf("---\n");*/
          yprev=y;
          y = y + h*Function(x, y);
          x = x + h;
          
        }
        break;
      }

      if(x < right) fprintf(file,"%lf\t%lf\n", x, y);
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
  FILE* file = fopen("method_Runge_Kutt_2", "w");
  double yprev;
  int antiloop;

  if(x_0 > 0){
    right = search(x_0,1);
    left = right - M_PI;
  }else if(x_0 < 0){
    left = search(x_0,-1);
    right = left + M_PI;
  }else{
    left = 0;
    right = 0;
  }
/*printf("INFO:\nleft %g, right %g, x_0 %g, y_0 %g,\n",left,right,x_0,y_0);*/
  if(x_0==left || x_0==right){
    printf("\nВ точке x_0=%lf особенность\n", x_0);
    exit(1);
  }

  yprev=0;
  antiloop = 0;
  if(x_start > left){
    while(x-h > x_start+e){/*идём влево от точки пока не уткнемся в заданный пользователем левый конец области...*/
      yprev=y;
/*      if(y==0)break;*/
      y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
      x = x - h;

      if( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){
        while( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){    
          while((yprev<0 && y>0) || (yprev>0 && y<0) ){
            h /= 2;
            y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
            if( antiloop++ > ANTILOOP_LIMIT )break;
          }
          if((yprev<0 && y>0) || (yprev>0 && y<0) )break;
          fprintf(tmp,"%lf\t%lf\n", x, y);
          printf("LEFT-Y--->[%lf %lf]\n", x, y);
          if( abs(y) < e ) break;
          yprev=y;
          y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
          x = x - h;
          
        }
        break;
      }


/*      if ((yprev<0 && y>0) || (yprev>0 && y<0)) break;*/
      fprintf(tmp,"%lf\t%lf\n", x, y);
      printf("LEFT--->[%lf %lf]\n", x, y);
    }
/*
    if ( !((yprev<0 && y>0) || (yprev>0 && y<0) || y==0) ){
      y = y - h*((1 - alpha)*Function(x_start, y) + alpha*Function(x_start - h/(2*alpha), y - h/(2*alpha)*Function(x_start, y)));
      fprintf(tmp,"%lf\t%lf\n", x_start, y);
      printf("LEFT-LAST-->[%lf %lf]\n", x, y);
    }
*/
  }else{/*строим график слева от точки... тут мы знаем, что особенность слева и надо приближаться с заданной точностью; если приблизились к точке, то начинаем увеличивать */
        /*точность пока не упрёмся в нужную пользователю...*/
    while(x > left+e){
      if(x  < left+h_start+err){
        h /= 2;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }
      yprev=y;
/*      if(y==0)break;*/
      y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
      x = x - h;

      if( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){
        while( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){        
          while((yprev<0 && y>0) || (yprev>0 && y<0) ){
            h /= 2;
            y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
            if( antiloop++ > ANTILOOP_LIMIT )break;
          }
          if((yprev<0 && y>0) || (yprev>0 && y<0) )break;
          fprintf(tmp,"%lf\t%lf\n", x, y);
          printf("LEFT-PREC-Y--->[%lf %lf]\n", x, y);
          if( abs(y) < e ) break;
          yprev=y;
          y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
          x = x - h;
          
        }
        break;
      }

/*      if ((yprev<0 && y>0) || (yprev>0 && y<0)) break;*/
      if(x > left){ fprintf(tmp,"%lf\t%lf\n", x, y);printf("LEFT_PREC--->[%lf %lf]\n", x, y);}
    }
  }

  invert_copy(file, tmp);
  
  x = x_0; y = y_0; h = h_start;
  fprintf(file,"%lf\t%lf\n", x_0, y_0);
  printf("CENTRAL--->[%lf %lf]\n", x, y);

  yprev=0;
  antiloop = 0;
  if(x_end < right){/*просто идём вправо без всякой точности*/
    while(x+h < x_end){
      yprev=y;
/*      if(y==0)break;*/
      y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
      x = x + h;


      if( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){
        while( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){        
          while((yprev<0 && y>0) || (yprev>0 && y<0) ){
            h /= 2;
            y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
            if( antiloop++ > ANTILOOP_LIMIT )break;
          }
          if((yprev<0 && y>0) || (yprev>0 && y<0) )break;
          fprintf(tmp,"%lf\t%lf\n", x, y);
          printf("RIGHT_Y--->[%lf %lf]\n", x, y);
          if( abs(y) < e ) break;
          yprev=y;
          y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
          x = x + h;
          
        }
        break;
      }



/*      if ((yprev<0 && y>0) || (yprev>0 && y<0)) break;*/
      fprintf(file,"%lf\t%lf\n", x, y);
      printf("RIGHT--->[%lf %lf]\n", x, y);
    }
/*
    if ( !((yprev<0 && y>0) || (yprev>0 && y<0) || y==0) ){
      y = y + h*((1 - alpha)*Function(x_end, y) + alpha*Function(x_end + h/(2*alpha), y + h/(2*alpha)*Function(x_end, y)));
      fprintf(file,"%lf\t%lf\n", x_end, y);
      printf("RIGHT-LAST--->[%lf %lf]\n", x, y);
    }
*/
  }else{/*справа особенность - идём туда с точностью, нужной пользователю*/
    while(x < right - e){
      if(right < x+h_start+err){
        h /= 2;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }
      yprev=y;
/*      if(y==0)break;*/
      y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
      x = x + h;
/*      if ((yprev<0 && y>0) || (yprev>0 && y<0)) break;*/

      if( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){
        while( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){        
          while((yprev<0 && y>0) || (yprev>0 && y<0) ){
            h /= 2;
            y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
            if( antiloop++ > ANTILOOP_LIMIT )break;
          }
          if((yprev<0 && y>0) || (yprev>0 && y<0) )break;
          fprintf(tmp,"%lf\t%lf\n", x, y);
          printf("RIGHT-PREC-->[%lf %lf]\n", x, y);
          if( abs(y) < e ) break;
          yprev=y;
          y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
          x = x + h;
          
        }
        break;
      }


      if(x < right){ fprintf(file,"%lf\t%lf\n", x, y); printf("RIGHT-PREC-->[%lf %lf]\n", x, y);}
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
  FILE* file = fopen("method_Runge_Kutt_4", "w");
  double yprev;
  int antiloop;

  if(x_0 > 0){
    right = search(x_0,1);
    left = right - M_PI;
  }else if(x_0 < 0){
    left = search(x_0,-1);
    right = left + M_PI;
  }else{
    left = 0;
    right = 0;
  }

  if(x_0==left || x_0==right){
    printf("\nВ точке x_0=%lf особенность\n", x_0);
    exit(1);
  }

  yprev=0;
  antiloop = 0;
  if(x_start > left){
    while(x-h > x_start+e){/*идём влево от точки пока не уткнемся в заданный пользователем левый конец области...*/
/*      if(y==0)break;*/
      k1 = Function(x, y);
      k2 = Function(x - h/2, y - h/2*k1);
      k3 = Function(x - h/2, y - h/2*k2);
      k4 = Function(x - h, y - h*k3);
      yprev=y;
      y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
      x = x - h;

/*      if ((yprev<0 && y>0) || (yprev>0 && y<0)) break;*/
      if( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){
        while( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){        
          while((yprev<0 && y>0) || (yprev>0 && y<0) ){
            h /= 2;
            k1 = Function(x, y);
            k2 = Function(x - h/2, y - h/2*k1);
            k3 = Function(x - h/2, y - h/2*k2);
            k4 = Function(x - h, y - h*k3);
            y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
            if( antiloop++ > ANTILOOP_LIMIT )break;
          }
          if((yprev<0 && y>0) || (yprev>0 && y<0) )break;
          fprintf(tmp,"%lf\t%lf\n", x, y);
          printf("LEFT-Y-->[%lf %lf]\n", x, y);
          if( abs(y) < e ) break;
          k1 = Function(x, y);
          k2 = Function(x - h/2, y - h/2*k1);
          k3 = Function(x - h/2, y - h/2*k2);
          k4 = Function(x - h, y - h*k3);
          yprev=y;
          y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
          x = x - h;
        }
        break;
      }

      fprintf(tmp,"%lf\t%lf\n", x, y);
      printf("LEFT--->[%lf %lf]\n", x, y);
    }
/*
    if ( !((yprev<0 && y>0) || (yprev>0 && y<0) || y==0) ){
      k1 = Function(x, y);
      k2 = Function(x_start - h/2, y - h/2*k1);
      k3 = Function(x_start - h/2, y - h/2*k2);
      k4 = Function(x_start - h, y - h*k3);
      y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
      fprintf(tmp,"%lf\t%lf\n", x_start, y);
    }
*/

  }else{/*строим график слева от точки... тут мы знаем, что особенность слева и надо приближаться с заданной точностью; если приблизились к точке, то начинаем увеличивать */
        /*точность пока не упрёмся в нужную пользователю...*/
    while(x > left+e){
      if(x  < left+h_start+err){
        h /= 2;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }

      k1 = Function(x, y);
      k2 = Function(x - h/2, y - h/2*k1);
      k3 = Function(x - h/2, y - h/2*k2);
      k4 = Function(x - h, y - h*k3);
      yprev=y;
      y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
      x = x - h;
/*      if(y==0)break;*/


      if( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){
        while( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){        
          while((yprev<0 && y>0) || (yprev>0 && y<0) ){
            h /= 2;
            k1 = Function(x, y);
            k2 = Function(x - h/2, y - h/2*k1);
            k3 = Function(x - h/2, y - h/2*k2);
            k4 = Function(x - h, y - h*k3);
            yprev=y;
            y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
            if( antiloop++ > ANTILOOP_LIMIT )break;
          }
          if((yprev<0 && y>0) || (yprev>0 && y<0) )break;
          fprintf(tmp,"%lf\t%lf\n", x, y);
          printf("LEFT-PREC-Y-->[%lf %lf]\n", x, y);
          if( abs(y) < e ) break;
          k1 = Function(x, y);
          k2 = Function(x - h/2, y - h/2*k1);
          k3 = Function(x - h/2, y - h/2*k2);
          k4 = Function(x - h, y - h*k3);
          yprev=y;
          y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
          x = x - h;
          
        }
        break;
      }



/*      if ((yprev<0 && y>0) || (yprev>0 && y<0)) break;*/
      if(x > left){ fprintf(tmp,"%lf\t%lf\n", x, y); printf("LEFT-PREC-->[%lf %lf]\n", x, y); }
    }
  }

  invert_copy(file, tmp);
  
  x = x_0; y = y_0; h = h_start;
  fprintf(file,"%lf\t%lf\n", x_0, y_0);

  yprev=0;
  antiloop = 0;
  if(x_end < right){/*просто идём вправо без всякой точности*/
    while(x+h < x_end){
/*      if(y==0)break;*/
      k1 = Function(x, y);
      k2 = Function(x + h/2, y + h/2*k1);
      k3 = Function(x + h/2, y + h/2*k2);
      k4 = Function(x + h, y + h*k3);
      yprev=y;
      y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
      x = x + h;

      if( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){
        while( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){        
          while((yprev<0 && y>0) || (yprev>0 && y<0) ){
            h /= 2;
            k1 = Function(x, y);
            k2 = Function(x + h/2, y + h/2*k1);
            k3 = Function(x + h/2, y + h/2*k2);
            k4 = Function(x + h, y + h*k3);
            yprev=y;
            y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
            if( antiloop++ > ANTILOOP_LIMIT )break;
          }
          if((yprev<0 && y>0) || (yprev>0 && y<0) )break;
          fprintf(tmp,"%lf\t%lf\n", x, y);
          printf("RIGHT-PREC-->[%lf %lf]\n", x, y);
          if( abs(y) < e ) break;
          k1 = Function(x, y);
          k2 = Function(x + h/2, y + h/2*k1);
          k3 = Function(x + h/2, y + h/2*k2);
          k4 = Function(x + h, y + h*k3);
          yprev=y;
          y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
          x = x + h;
          
        }
        break;
      }


/*      if ((yprev<0 && y>0) || (yprev>0 && y<0)) break;*/
      fprintf(file,"%lf\t%lf\n", x, y);
      printf("RIGHT-PREC-->[%lf %lf]\n", x, y);
    }
/*
    if ( !((yprev<0 && y>0) || (yprev>0 && y<0) || y==0) ){
      k1 = Function(x_end, y);
      k2 = Function(x_end + h/2, y + h/2*k1);
      k3 = Function(x_end + h/2, y + h/2*k2);
      k4 = Function(x_end + h, y + h*k3);
      y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
      fprintf(file,"%lf\t%lf\n", x_end, y);
    }
*/
  }else{/*справа особенность - идём туда с точностью, нужной пользователю*/
    while(x < right - e){
      if(right < x+h_start+err){
        h /= 2;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }
      k1 = Function(x, y);
      k2 = Function(x + h/2, y + h/2*k1);
      k3 = Function(x + h/2, y + h/2*k2);
      k4 = Function(x + h, y + h*k3);
      yprev=y;
      y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
      x = x + h;

      if( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){
        while( ((yprev<0 && y>0) || (yprev>0 && y<0)) /*&& abs(y) > e*/ ){        
          while((yprev<0 && y>0) || (yprev>0 && y<0) ){
            h /= 2;
            k1 = Function(x, y);
            k2 = Function(x + h/2, y + h/2*k1);
            k3 = Function(x + h/2, y + h/2*k2);
            k4 = Function(x + h, y + h*k3);
            yprev=y;
            y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
            if( antiloop++ > ANTILOOP_LIMIT )break;
          }
          if((yprev<0 && y>0) || (yprev>0 && y<0) )break;
          fprintf(tmp,"%lf\t%lf\n", x, y);
          printf("RIGHT-PREC-Y-->[%lf %lf]\n", x, y);
          if( abs(y) < e ) break;
          k1 = Function(x, y);
          k2 = Function(x + h/2, y + h/2*k1);
          k3 = Function(x + h/2, y + h/2*k2);
          k4 = Function(x + h, y + h*k3);
          yprev=y;
          y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
          x = x + h;
          
        }
        break;
      }


/*      if(y==0)break;*/
/*      if ((yprev<0 && y>0) || (yprev>0 && y<0)) break;*/




      if(x < right){ fprintf(file,"%lf\t%lf\n", x, y);printf("RIGHT-PREC-->[%lf %lf]\n", x, y); }
    }
  }
  fclose(file);
  fclose(tmp);
  unlink("tmp");
}











void Runge_Kutt_2_(double h, double x_0, double y_0, float alpha, double x_start, double x_end, double e ){
  double x = x_0, y = y_0, h_start = h;
  double left, right;
  FILE* tmp = fopen("tmp", "w+");
  FILE* file = fopen("method_Runge_Kutt_2", "w");
  double yprev;
  int antiloop;

  if(x_0 > 0){
    right = search(x_0,1);
    left = right - M_PI;
  }else if(x_0 < 0){
    left = search(x_0,-1);
    right = left + M_PI;
  }else{
    left = 0;
    right = 0;
  }

printf("INFO:\nleft %g, right %g, x_0 %g, y_0 %g,\n",left,right,x_0,y_0);

  if(x_0==left || x_0==right){
    printf("\nВ точке x_0=%lf особенность\n", x_0);
    exit(1);
  }

  yprev=0;
  antiloop = 0;
  if(x_start > left ){
    while(x-h > x_start){
      yprev=y;
      y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
      x = x - h;
      if ((yprev<0 && y>0) || (yprev>0 && y<0)) break;
      fprintf(tmp,"%lf\t%lf\n", x, y);
    }
    if (!((yprev<0 && y>0) || (yprev>0 && y<0)) ){
      y = y - h*((1 - alpha)*Function(x_start, y) + alpha*Function(x_start - h/(2*alpha), y - h/(2*alpha)*Function(x_start, y)));
      fprintf(tmp,"%lf\t%lf\n", x_start, y);
    }
  }else{
    while(x - left > e){
      if(x - left < h_start+err){ 
        h /= 2;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }
      yprev=y;
      y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
      x = x - h;
      if ((yprev<0 && y>0) || (yprev>0 && y<0)) break;
      if( x > left )fprintf(tmp,"%lf\t%lf\n", x, y);
    }
  }

  invert_copy(file, tmp);

  x = x_0; y = y_0; h = h_start;
  fprintf(file,"%lf\t%lf\n", x_0, y_0);

  yprev=0;
  antiloop = 0;
  if(x_end < right){
  printf("\n%g\n\n",x_end);
  printf("YYY\n");
    while(x+h < x_end){
      yprev=y;
      y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
      x = x + h;
      if ((yprev<0 && y>0) || (yprev>0 && y<0)) break;
      fprintf(file,"%lf\t%lf\n", x, y);
    }
    if ( !((yprev<0 && y>0) || (yprev>0 && y<0)) ){
      y = y + h*((1 - alpha)*Function(x_end, y) + alpha*Function(x_end + h/(2*alpha), y + h/(2*alpha)*Function(x_end, y)));
      fprintf(file,"%lf\t%lf\n", x_end, y);
    }
  }else{
  printf("XXX\n");
    while(x < right - e){
      if(right - x < h_start+err){
        h /= 2;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }
      yprev=y;
      y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
      x = x + h;
      if ((yprev<0 && y>0) || (yprev>0 && y<0)) break;
      if(x < right)fprintf(file,"%lf\t%lf\n", x, y);
    }
  }

  fclose(file);
  fclose(tmp);
  unlink("tmp");
}

void Runge_Kutt_2__(double h, double x_0, double y_0, float alpha, double x_start, double x_end, double e ){
  double x = x_0, y = y_0, h_start = h;
  double left, right;
  FILE* tmp = fopen("tmp", "w+");
  FILE* file = fopen("method_Runge_Kutt_2", "w");
  double yprev;
  int antiloop;

  if(x_0 > 0){
    right = search(x_0,1);
    left = right - M_PI;
  }else if(x_0 < 0){
    left = search(x_0,-1);
    right = left + M_PI;
  }else{
    left = 0;
    right = 0;
  }

  if(x_0==left || x_0==right){
    printf("\nВ точке x_0=%lf особенность\n", x_0);
    exit(1);
  }

  yprev=0;
  antiloop = 0;
  if(x_start > left ){
    while(x-h > x_start){
      yprev=y;
      y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
      x = x - h;
      /*if ((y_old<0 && y>0) || (y_old>0 && y<0))// || (y<0.1 && y>-0.1))*/
      /*  break;*/

      if(y>0)fprintf(tmp,"%lf\t%lf\n", x, y);
      if(y<0 || yprev<0 || yprev - h/(2*alpha)*Function(x, yprev) < 0){
        y=yprev;
        x+=h;
        h/=100;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }else if(y>0 && y<e)break;
    }
    if(!(y<0 || y - h/(2*alpha)*Function(x, y) < 0)){
      y = y - h*((1 - alpha)*Function(x_start, y) + alpha*Function(x_start - h/(2*alpha), y - h/(2*alpha)*Function(x_start, y)));
      fprintf(tmp,"%lf\t%lf\n", x_start, y);
    }
  }else{
    while(x - left > e){
      if(x - left < h_start+err) h /= 2;
      yprev=y;
      y = y - h*((1 - alpha)*Function(x, y) + alpha*Function(x - h/(2*alpha), y - h/(2*alpha)*Function(x, y)));
      x = x - h;
      if(x > left && y>0)fprintf(tmp,"%lf\t%lf\n", x, y);
      if(y<0 || yprev<0 || yprev - h/(2*alpha)*Function(x, yprev) < 0){
        y=yprev;
        x+=h;
        h/=100;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }else if(y>0 && y<e)break;
    }
  }

  invert_copy(file, tmp);

  x = x_0; y = y_0; h = h_start;
  fprintf(file,"%lf\t%lf\n", x_0, y_0);

  yprev=0;
  antiloop = 0;
  if(x_end < right){
    while(x+h < x_end){
      yprev=y;
      y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
      x = x + h;
      if(y>0)fprintf(file,"%lf\t%lf\n", x, y);
      if(y<0 || yprev<0 || yprev + h/(2*alpha)*Function(x, yprev) < 0){
        y=yprev;
        x-=h;
        h/=100;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }else if(y>0 && y<e)break;
    }
    if(!(y<0 || y + h/(2*alpha)*Function(x, y) < 0)){
      y = y + h*((1 - alpha)*Function(x_end, y) + alpha*Function(x_end + h/(2*alpha), y + h/(2*alpha)*Function(x_end, y)));
      fprintf(file,"%lf\t%lf\n", x_end, y);
    }
  }else{
    while(x < right - e){
      if(right - x < h_start+err) h /= 2;
      yprev=y;
      y = y + h*((1 - alpha)*Function(x, y) + alpha*Function(x + h/(2*alpha), y + h/(2*alpha)*Function(x, y)));
      x = x + h;
      if(x < right && y>0)fprintf(file,"%lf\t%lf\n", x, y);
      if(y<0 || yprev<0 || yprev + h/(2*alpha)*Function(x, yprev) < 0){
        y=yprev;
        x-=h;
        h/=100;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }else if(y>0 && y<e)break;
    }
  }


  fclose(file);
  fclose(tmp);
  unlink("tmp");
}


void Runge_Kutt_4__(double h, double x_0, double y_0, double x_start, double x_end,double e ){
  double k1, k2, k3, k4;
  double x = x_0, y = y_0, h_start = h;
  double left, right;
  FILE* tmp = fopen("tmp", "w+");
  FILE* file = fopen("method_Runge_Kutt_4", "w");
  double yprev;
  int antiloop;

  if(x_0 > 0){
    right = search(x_0,1);
    left = right - M_PI;
  }else if(x_0 < 0){
    left = search(x_0,-1);
    right = left + M_PI;
  }else{
    left = 0;
    right = 0;
  }

  if(x_0==left || x_0==right){
    printf("\nВ точке x_0=%lf особенность\n", x_0);
    exit(1);
  }

  yprev=0;
  antiloop = 0;
  if(x_start > left ){
    while(x-h > x_start){
      k1 = Function(x, y);
      k2 = Function(x - h/2, y - h/2*k1);
      k3 = Function(x - h/2, y - h/2*k2);
      k4 = Function(x - h, y - h*k3);
      yprev=y;
      y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
      x = x - h;
      
      if(y>0)fprintf(tmp,"%lf\t%lf\n", x, y);
      if(y<0 || yprev - h/2*k1 < 0 || yprev - h/2*k2 < 0 || yprev - h*k3 < 0){
        y=yprev;
        x+=h;
        h/=100;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }else if(y>0 && y<e)break;
      if(yprev<e)break;
    }
    k1 = Function(x, y);
    k2 = Function(x_start - h/2, y - h/2*k1);
    k3 = Function(x_start - h/2, y - h/2*k2);
    k4 = Function(x_start - h, y - h*k3);
    if(!(y<0 || y - h/2*k1 < 0 || y - h/2*k2 < 0 || y - h*k3 < 0)){
      y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
      fprintf(tmp,"%lf\t%lf\n", x_start, y);
    }
  }else{
    while(x - left > e){
      if(x-left < h_start+err) h /= 2;
      k1 = Function(x, y);
      k2 = Function(x - h/2, y - h/2*k1);
      k3 = Function(x - h/2, y - h/2*k2);
      k4 = Function(x - h, y - h*k3);
      yprev=y;
      y = y - h/6*(k1 + 2*k2 + 2*k3 + k4);
      x = x - h;
      if(x > left && y>0)fprintf(tmp,"%lf\t%lf\n", x, y);
      if(y<0 || yprev - h/2*k1 < 0 || yprev - h/2*k2 < 0 || yprev - h*k3 < 0){
        y=yprev;
        x+=h;
        h/=2;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }else if(y>0 && y<e)break;
      if(yprev<e)break;
    }
  }

  invert_copy(file, tmp);
  
  x = x_0; y = y_0; h = h_start;
  fprintf(file,"%lf\t%lf\n", x_0, y_0);

  yprev=0;
  antiloop=0;
  if(x_end < right){
    while(x+h < x_end){ 
      k1 = Function(x, y);
      k2 = Function(x + h/2, y + h/2*k1);
      k3 = Function(x + h/2, y + h/2*k2);
      k4 = Function(x + h, y + h*k3);
      yprev=y;
      y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
      x = x + h;
      
      if(y>0)fprintf(file,"%lf\t%lf\n", x, y);

      if(y<0 || yprev + h/2*k1 < 0 || yprev + h/2*k2 < 0 || yprev + h*k3 < 0){
        y=yprev;
        x-=h;
        h/=100;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }else if(y>0 && y<e)break;
      if(yprev<e)break;
    }
    
    k1 = Function(x_end, y);
    k2 = Function(x_end + h/2, y + h/2*k1);
    k3 = Function(x_end + h/2, y + h/2*k2);
    k4 = Function(x_end + h, y + h*k3);
    if(!(y<0 || y + h/2*k1 < 0 || y + h/2*k2 < 0 || y + h*k3 < 0)){
      y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
    
      fprintf(file,"%lf\t%lf\n", x_end, y);
    }
  }else{
    while(x < right - e){
      if(right-x < h_start+err) h /= 2;
      k1 = Function(x, y);
      k2 = Function(x + h/2, y + h/2*k1);
      k3 = Function(x + h/2, y + h/2*k2);
      k4 = Function(x + h, y + h*k3);
      yprev=y;
      y = y + h/6*(k1 + 2*k2 + 2*k3 + k4);
      x = x + h;
      if(x < right && y>0) fprintf(file,"%lf\t%lf\n", x, y);
      if(y<0 || yprev + h/2*k1 < 0 || yprev + h/2*k2 < 0 || yprev + h*k3 < 0){
        y=yprev;
        x-=h;
        h/=2;
        if( antiloop++ > ANTILOOP_LIMIT )break;
      }else if(y>0 && y<e)break;
      if(yprev<e)break;
    }
  }

  fclose(file);
  fclose(tmp);
  unlink("tmp");
}


void gnuplot_input(double x_start, double x_end, int *method){
  FILE *file;

  file = fopen("gnuplot_input", "w");
  fprintf(file, "set xrange[%d:%d]\n", (int)floor(x_start), (int)ceil(x_end));
  fprintf(file,"set title \"Костенчук М.И. (вариант 8) y'*sin(x)=e^(1/y).\"\n");
  fprintf(file,"plot ");
  if (method[0] == YES) {
    fprintf(file,"'method_Euler' title \"Euler's Method\" with lines");
  }
  if (method[1] == YES) {
    if (method[0] == YES) fprintf(file,", ");
    fprintf(file,"'method_Runge_Kutt_2' title \"Runge-Kutta methods of order 2\" with points");
  }
  if (method[2] == YES) {
    if (method[0] == YES || method[1] == YES) fprintf(file,", ");
    fprintf(file,"'method_Runge_Kutt_4' title \"Runge-Kutta methods of order 4\" with points");
  }
  fprintf(file," \npause -1\n"); 

  fclose(file);
}


void init(){
  int N, method[3];
  float x_0, y_0,x_start,x_end,alpha, h,e;
  float ptr;
  double left, right;
  char n;

  method[0] = NO;
  method[1] = YES;
  method[2] = NO;
/*
  N = 10000;
  x_start = -1;
  x_end = 0;
  x_0 = -1;
  y_0 = 1;
  alpha = 1;
  e=0.001;
*/


  N = 20;
  x_start = -2;
  x_end = 2;
  x_0 = 2;
  y_0 = 2;
  alpha = 1;
  e=0.001;


  printf("1. Метод Эйлера \n2. Метод Рунге-Кутта 2-го порядка точности \n3. Метод Рунге-Кутта 4-го порядка точности \n\n");

  while(1){
    printf("\nИспользовать значения по умолчанию? (-1<=x<0, y(-1)=%d) (y or n) ",(int)y_0);
    scanf("%c",&n);
    if(n == 'n' || n == 'y') break;
  }


  if (n == 'n') {
    while(1){
      printf("\nВведите начало отрезка a ");
      scanf("%f",&x_start);

      printf("Введите конец отрезка b ");
      scanf("%f",&x_end);
      if (x_end <= x_start){
        ptr = x_end;
        x_end = x_start;
        x_start = ptr;
      }
      break;
    }
    while(1){

      while(1) {
        printf("Введите x0 -> ");
        scanf("%f",&x_0);
        if (x_0 < x_start || x_0 > x_end){
          printf("\nТочка должна находиться внутри отрезка\n");
        }else{
          if(x_0 > 0){
            right = search(x_0, 1);
            left = right - M_PI;
          }else if(x_0 < 0){
            left = search(x_0,-1);
            right = left + M_PI;
          }else{
            left  = 0;
            right = 0;
          }
          if(x_0==left || x_0==right){
            printf("\nВ точке x_0 = %lf особенность\n", x_0);
          }else{
            break;
          }
        }
      }

      while(1) {
        printf("Введите y0 -> ");
        scanf("%f",&y_0);
        break;
      }

      printf("Введите нeдоход до особенности -> ");
      scanf("%f",&e);

      /*if(x_0 < e+left){*/
        /*Если близко х0 к особенности о тем не менее надо черить график -  страная причина отказа*/
      /*  printf("\n Особенность слева\n");*/
      /*  printf("\nleft = %f\n", left);*/
      /*}*/
      /*else if (x_0 > right-e){*/
        /*Если близко х0 к особенности о тем не менее надо черить график -  странная причина отказа*/
      /*  printf("\nТочка x_0=%lf слишком близка к особенности\n", x_0);*/
      /*}else{*/
        break;
      /*}*/

    }

    while(1){
      printf("Введите параметр \"альфа\" -> ");
      scanf("%f",&alpha);
      if(alpha > 0 && alpha <= 1){
        /*if(alpha < 0.5) alpha = 0.5;*/
        break; 
      }else printf("\nПараметр \"альфа\" должен принадлежать интервалу (0, 1]\n\n");
    }

    while(1){    
      printf("Введите количество узлов: ");
      scanf("%d",&N);
      if(N >= 10 && N <= 100000) break;
      else printf("\n> 10, но < 100000)\n\n");
    }
  }


  /*N*=10;*/
  h = fabs((x_end - x_start)/N);

  if (method[0] == YES){
    Euler(h, x_0, y_0, x_start, x_end, e);
  }
  if (method[1] == YES){
    Runge_Kutt_2(h, x_0, y_0, alpha, x_start, x_end, e);
  }
  if (method[2] == YES){
    Runge_Kutt_4(h, x_0, y_0, x_start, x_end, e);
  }


  gnuplot_input(x_start, x_end, method);

}

int main(){
  system("clear");
  printf("Решение задачи Коши для уравнения y'*sin(x)=e^(1/y), -1<=x<0, y(-1)=+-1  \n(гр 4361, Костенчук М.И., вариант 8)\n");
  init();
  system("gnuplot gnuplot_input");
  return 0;
}
