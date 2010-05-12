#include "stdio.h"
#include "stdlib.h"

#define max3(a,b,c) ((a) > (b) ? ((a) > (c) ? (a) : (c)) : ((b) > (c) ? (b) : (c)))
int **sum(int **arr1, int **arr2, int **res, int i1, int j1, int i2, int j2, int ir, int jr, int nn){
	int i,j;
	for(i = 0; i < nn; i++){
		for(j = 0; j < nn; j++){
			res[ir+i][jr+j] = arr1[i1+i][j1+j] + arr2[i2+i][j2+j];
		}
	}
	return res;
}

int **sub(int **arr1, int **arr2, int **res, int i1, int j1, int i2, int j2, int ir, int jr, int nn){
	int i,j;
	for(i = 0; i < nn; i++){
		for(j = 0; j < nn; j++){
			res[ir+i][jr+j] = arr1[i1+i][j1+j] - arr2[i2+i][j2+j];
		}
	}
	return res;
}

int **mult(int **arr1, int **arr2, int **res, int i1, int j1, int i2, int j2, int nn){
	int **tmp1, **tmp2;
	int iter, iter2;
	int **buf[7];
	if (nn == 1){
		res[0][0] = arr1[0][0] * arr2[0][0];
	}else{
		
		tmp1 = (int **) malloc(sizeof(int) * nn/2);
		tmp2 = (int **) malloc(sizeof(int) * nn/2);
		for (iter = 0; iter < nn/2; iter++){
			tmp1[iter] = (int *) malloc(sizeof(int) * nn/2);
			tmp2[iter] = (int *) malloc(sizeof(int) * nn/2);
		}
		for (iter = 0; iter < 7; iter++){
			buf[iter] = (int **) malloc(sizeof(int) * nn/2);
			for (iter2 = 0; iter2 < nn/2; iter2++){
				buf[iter][iter2] = (int *) malloc(sizeof(int) * nn/2);
			}
		}
		tmp1 = sum(arr1, arr1, tmp1, i1, j1, i1+nn/2, j1+nn/2, 0, 0, nn/2); 
		tmp2 = sum(arr2, arr2, tmp2, i2, j2, i2+nn/2, j2+nn/2, 0, 0, nn/2);
		buf[0] = mult(tmp1, tmp2, buf[0], 0, 0, 0, 0, nn/2);                       //P1 = (A11+A22)*(B11+B22)
		tmp1 = sum(arr1, arr1, tmp1, i1+nn/2, j1, i1+nn/2, j1+nn/2, 0, 0, nn/2);
		buf[1] = mult(tmp1, arr2, buf[1], 0, 0, i2, j2, nn/2);                     //P2 = (A21+A22)*(B11)
		tmp2 = sub(arr2, arr2, tmp2, i2, j2+nn/2, i2+nn/2, j2+nn/2, 0, 0, nn/2);
		buf[2] = mult(arr1, tmp2, buf[2], i1, j1, 0, 0, nn/2);                     //P3 = (A11)*(B12-B22)
		tmp2 = sub(arr2, arr2, tmp2, i2+nn/2, j2, i2, j2, 0, 0, nn/2);
		buf[3] = mult(arr1, tmp2, buf[3], i1+nn/2, j1+nn/2, 0, 0, nn/2);           //P4 = (A22)*(B21-B11)
		tmp1 = sum(arr1, arr1, tmp1, i1, j1, i1, j1+nn/2, 0, 0, nn/2);
		buf[4] = mult(tmp1, arr2, buf[4], 0, 0, i2+nn/2, j2+nn/2, nn/2);           //P5 = (A11+A12)*(B22)
		tmp1 = sub(arr1, arr1, tmp1, i1+nn/2, j1, i1, j1, 0, 0, nn/2);
		tmp2 = sum(arr2, arr2, tmp2, i2, j2, i2, j2+nn/2, 0, 0, nn/2);
		buf[5] = mult(tmp1, tmp2, buf[5], 0, 0, 0, 0, nn/2);		                   //P6 = (A21-A11)*(B11+B12)	
		tmp1 = sub(arr1, arr1, tmp1, i1, j1+nn/2, i1+nn/2, j1+nn/2, 0, 0, nn/2);
		tmp2 = sum(arr2, arr2, tmp2, i2+nn/2, j2, i2+nn/2, j2+nn/2, 0, 0, nn/2);
		buf[6] = mult(tmp1, tmp2, buf[6], 0, 0, 0, 0, nn/2);                       //P7 = (A12-A22)*(B21+B22)
		
		tmp1 = sum(buf[0], buf[3], tmp1, 0, 0, 0, 0, 0, 0, nn/2);
		tmp2 = sub(tmp1, buf[4], tmp2, 0, 0, 0, 0, 0, 0, nn/2);
		res = sum(tmp2, buf[6], res, 0, 0, 0, 0, 0, 0, nn/2);        //С11 = (P1 + P4) - P5 + P7 
		res = sum(buf[2], buf[4], res, 0, 0, 0, 0, 0, nn/2, nn/2);   //C12 = (P3 + P5)
		res = sum(buf[1], buf[3], res, 0, 0, 0, 0, nn/2, 0, nn/2);   //C21 = (P2 + P4)
		tmp1 = sub(buf[0], buf[1], tmp1, 0, 0, 0, 0, 0, 0, nn/2);
		tmp2 = sum(buf[2], buf[5], tmp2, 0, 0, 0, 0, 0, 0, nn/2);
		res = sum(tmp1, tmp2, res, 0, 0, 0, 0, nn/2, nn/2, nn/2);    //C22 = (P1 - P2) + (P3 + P6)
	}
	return res;
}

int **mmult(int **arr1, int **arr2, int **res, int n){
	if (n < 1){
		return NULL;
	}
	if (n == 1){
		res[0][0] = arr1[0][0] * arr2[0][0];
		return res;
	}
	return mult(arr1, arr2, res, 0, 0, 0, 0, n);
}


int main(){
	int i,j;
	int n1, m1, n2, m2, nn;
	int **arr1, **arr2, **res;
	printf("n1: "); scanf("%d", &n1);
  printf("m1: "); scanf("%d", &m1);
  printf("n2: "); scanf("%d", &n2);
  printf("m2: "); scanf("%d", &m2);
	if (m1 != n2){
    printf("Error: Wrong sizes\n");
    exit(2);
  }
	for(nn = 1; nn < max3(n1, m1, m2); nn <<= 1);
	srand(123);
	arr1 = (int **) malloc(sizeof(int) * nn);
	res = (int **) malloc(sizeof(int) * nn);
	for (i = 0; i < n1; i++){
		arr1[i] = (int *) malloc(sizeof(int) * nn);
		res[i] = (int *) malloc(sizeof(int) * nn);
    for (j = 0; j < m1; j++){
			arr1[i][j] = rand() % 2;
		}
		for (; j < nn; j++){
			arr1[i][j] = 0;
		}
	}
	for (; i < nn; i++){
		arr1[i] = (int *) malloc(sizeof(int) * nn);
		res[i] = (int *) malloc(sizeof(int) * nn);
		for (j = 0; j < nn; j++){
			arr1[i][j] = 0;
		}
	}
	arr2 = (int **) malloc(sizeof(int) * nn);
	for (i = 0; i < n2; i++){
		arr2[i] = (int *) malloc(sizeof(int) * nn);
    for (j = 0; j < m2; j++){
			arr2[i][j] = rand() % 2;
		}
		for (; j < nn; j++){
			arr2[i][j] = 0;
		}
	}
	for (; i < nn; i++){
		arr2[i] = (int *) malloc(sizeof(int) * nn);
		for (j = 0; j < nn; j++){
			arr2[i][j] = 0;
		}
	}
	
	printf("A:\n");
	for (i = 0; i < n1; i++){
		for (j = 0; j < m1; j++){
			printf("%d ", arr1[i][j]);
		}
		printf("\n");
	}
	printf("B:\n");
	for (i = 0; i < n2; i++){
		for (j = 0; j < m2; j++){
			printf("%d ", arr2[i][j]);
		}
		printf("\n");
	}
	printf("C\n");
	for (i = 0; i < n1; i++){
		for (j = 0; j < m2; j++){
			printf("%d ", res[i][j]);
		}
		printf("\n");
	}
	
	res = mmult(arr1, arr2, res, nn);
	printf("C = A * B:\n");
	for (i = 0; i < n1; i++){
		for (j = 0; j < m2; j++){
			printf("%d ", res[i][j]);
		}
		printf("\n");
	}
	return 0;
}

