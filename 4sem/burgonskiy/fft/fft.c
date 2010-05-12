#include "stdio.h"
#include "stdlib.h"
typedef struct cnum {
	int x;
	int y;
} cnum;
cnum sum(cnum a, cnum b){
	cnum buf;
/*	buf = (cnum *) malloc(sizeof(cnum));*/
	buf.x = a.x + b.x;
	buf.y = a.y + b.y;
	return buf;
}

cnum subs(cnum a, cnum b){
	cnum buf;
/*	buf = (cnum *) malloc(sizeof(cnum));*/
	buf.x = a.x + b.x;
	buf.y = a.y + b.y;
	return buf;
}

cnum mult(cnum a, cnum b){
	cnum buf;
/*	buf = (cnum *) malloc(sizeof(cnum));*/
	buf.x = a.x*b.x - a.y*b.y;
	buf.y = b.x*a.y + a.x * b.y;
	return buf;
}

cnum divis(cnum a, cnum b){
	cnum buf;
	/*buf = (cnum *) malloc(sizeof(cnum));*/
	buf.x = (a.x*b.x + a.y*b.y)/(b.x*b.x + b.y*b.y);
	buf.y = (b.x*a.y - a.x*b.y)/(b.x*b.x + b.y*b.y);
	return buf;
}

int main(){
	
	
}