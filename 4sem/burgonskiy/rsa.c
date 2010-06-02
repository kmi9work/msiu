#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DEBUG

unsigned long long gcd(unsigned long long a, unsigned long long b){
  unsigned long long gcd, n1 = abs(a), n2 = abs(b);
  for (gcd = (n1 < n2) ? n1 : n2; gcd > 0; gcd--)
    if (!(n1 % gcd || n2 % gcd))
      break;
  return gcd;
}

void extended_euclid(unsigned long long a, unsigned long long b, unsigned long long *x, unsigned long long *y, unsigned long long *d)
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

unsigned long long witness(unsigned long long a, unsigned long long n){
  unsigned long long d;
  unsigned long long b;
  long c;
  d=1;
  b=n-1;
  for(; b!=0; b>>=1){
    if (b&1){
      d = (d*a)%n;
    }
    c = a;
    a = (a*a)%n;
    if ((a == 1) && (c != 1) && (c != n-1)) return 1;
  }
  if (d == 1) return 0; 
  return 1;
}
 
unsigned long long miller_rabin(unsigned long long n, unsigned long long s){
  unsigned long long i;
  unsigned long long a;
  
  for(i = 0 ; i < s ; i++){
    a = rand()%(n-1);
    if(witness(a, n) == 1){
      return 0;
    }
  }
  return 1;
}

unsigned long long prime(void){
  unsigned long long p;
  unsigned long long i = 1;
  unsigned long long s = 1000;
  while(i){
    p = rand() % 65536;
    i = !(miller_rabin(p, s));
  }
  return p;
}

unsigned long long prime_too(unsigned long long a){
  unsigned long long res;
  res = 1;
  while (1){
    res = rand() % 65536;
    if (gcd(a, res) == 1){
      return res;
    }
  } 
  return res;
}

unsigned long long crypt(unsigned long long d, unsigned long long e, unsigned long long n){
  unsigned long long r=1;
  for(; e > 0 ; e >>= 1){
    if ((e%2)==1) {
      r=(r*d)%n;
    }
    d=(d*d)%n;
  }
  return r;
}


int main(int argc, char **argv){
  unsigned long long i,j;
  unsigned long long tmp1, tmp2, r_size;
  unsigned long long p, q, e, d, a;
  unsigned long long phi, n, nn, num, encoded_num;
  unsigned long long buf;
  FILE *fid_keys;
  int fid_in, fid_out, r_count;
  fid_in = open(argv[1], O_RDONLY);
  fid_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 00755);
  if (strcmp(argv[3], "1") == 0){ /*1 -- encode 0 - decode*/
    fid_keys = fopen("keys", "w");
    p = prime();
    q = prime();
    n = p*q;
    phi = (p-1)*(q-1);
    e = prime_too(phi);
    extended_euclid(e, phi, &d, &tmp1, &tmp2);
    d = d % phi;
    fprintf(fid_keys, "Secret key: %llu-%llu\nPublic key: %llu-%llu\n", d, n, e, n);
  }else{

    fid_keys = fopen("keys", "r");
    if (fscanf(fid_keys, "Secret key: %llu-%llu\nPublic key: %llu-%llu\n", &d, &n, &e, &n) < 4){puts("Make keys with param 1 first."); exit(0);};
  }
  nn = 1; r_size = 0;
  while (nn <= n) {nn <<= 8; r_size+=1;};
  r_size -= 1;
  if (r_size <= 0){puts("Error: Too small p, q. p*q must be bigger than 255."); exit(0);}
  printf("%d\n", r_size);
  if (strcmp(argv[3], "1") == 0){
    num = 0;
    while (read(fid_in, &num, r_size) > 0){
      encoded_num = crypt(num, d, n);
      printf("%llu, %llu\n", num, encoded_num);
      write(fid_out, &encoded_num, r_size + 1);
    }
  }else{
    encoded_num = 0;
    while (read(fid_in, &encoded_num, r_size + 1) > 0){
      num = crypt(encoded_num, e, n);
      write(fid_out, &num, r_size);
    }
  }
  if (close(fid_in) < 0){perror("fid_in"); exit(0);};
  if (close(fid_out) < 0){perror("fid_out"); exit(0);};
  fclose(fid_keys);
  return 0;
}
