#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int big_simple(unsigned long long x){
	x = rand() % 1000;
	return x;
}


void extended_euclid(int a, int b, int *x, int *y, int *d)
/* calculates a * *x + b * *y = gcd(a, b) = *d */
{
  long q, r, x1, x2, y1, y2;
  if (b == 0) {
    *d = a, *x = 1, *y = 0;
    return;
  }
  x2 = 1, x1 = 0, y2 = 0, y1 = 1;
  while (b > 0) {
    q = a / b, r = a - q * b;
    *x = x2 - q * x1, *y = y2 - q * y1;
    a = b, b = r;
    x2 = x1, x1 = *x, y2 = y1, y1 = *y;
  }
  *d = a, *x = x2, *y = y2;
}

int simple_too(unsigned long long a, int res){
	res = rand() % 1000;
	return res;
}

int main(int argc, char **argv){
	int i,j;
	int tmp1, tmp2, r_size;
	int p, q, e;
	unsigned long long phi, n, nn, num, encoded_num;
	char *buf;
	int fid_in, fid_out, fid_keys;
	fid_in = fopen(argv[1], "r");
	fid_out = fopen(argv[2], "w");
	if (argv[3] = "1"){ /*1 -- encode 0 - decode*/
		fid_keys = fopen("keys", "w");
		p = big_simple(p);
		q = big_simple(q);
		n = p*q;
		phi = (p-1)*(q-1);
		e = simple_too(phi, e);
		extended_euclid(e, phi, d, tmp1, tmp2);
		d = d % phi;
		fprintf(fid_keys, "Secret key: %d-%d\nPublic key: %d-%d\n", d, n, e, n);
	}else{
		fid_keys = fopen("keys", "r");
		if (fscanf(fid_keys, "Secret key: %d-%d\nPublic key: %d-%d\n", &d, &n, &e, &n) < 4){puts("Make keys with param 1 first."); exit(0);};
	}
	nn = 1; r_size = 0;
	while (nn <= n) {nn <<= 8; r_size+=1};
	r_size -= 1;
	if (r_size <= 0){puts("Error: Too small p, q. p*q must be bigger than 255."); exit(0);}
	buf = (char *) malloc(r_size);
	if (argv[3] = "1"){
		while (1){
			fgets(buf, r_size, fid_in);
			num = (unsigned long long) buf[0];
			for(i = 1; i < r_size; i++){
				num <<= 8;
				num += (unsigned long long) buf[i];
			}
			encoded_num = (num * d) % n;
			buf[0] = (char) encoded_num;
			for(i = 1; i < r_size; i++){
				encoded_num >>= 8;
				buf[i] = (char) encoded_num;
			}
			fputs(buf, fid_out);
		}
	}else{
		while (1){
			fgets(buf, r_size, fid_in);
			encoded_num = (unsigned long long) buf[0];
			for(i = 1; i < r_size; i++){
				encoded_num <<= 8;
				encoded_num += (unsigned long long) buf[i];
			}
			num = (encoded_num * e) % n;
			buf[0] = (char) num;
			for(i = 1; i < r_size; i++){
				num >>= 8;
				buf[i] = (char) num;
			}
			fputs(buf, fid_out);
		}
	}
	free(buf);
	fclose(fid_in);
	fclose(fid_out);
	fclose(fid_keys);
	printf("%lu\n", sizeof(a));
	return 0;
}






















