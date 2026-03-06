#ifndef _H_MATH_
#define _H_MATH_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _MATRIZ_{
	int m,n;
	H **ent;
}MatH;

MatH iniMatH(int m, int n);
MatH sumaMatH(MatH A, MatH B);
MatH restaMatH(MatH A, MatH B);
MatH multMatH(MatH A, MatH B);
MatH leeMH(FILE *f);
int escMatH(FILE *f, MatH A);
int LiberaMH(MatH *A);

#ifdef __cplusplus
}
#endif

#endif
