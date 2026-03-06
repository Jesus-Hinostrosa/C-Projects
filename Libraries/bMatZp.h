#ifndef _H_MATZP_
#define _H_MATZP_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _MatZp_{
  int m, n;
  Zp **ent;
}MatZp;

MatZp iniMatZp(int m, int n, int p);
MatZp sumaMatZp(MatZp A, MatZp B, int p);
MatZp restaMatZp(MatZp A, MatZp B, int p);
MatZp multMatZp(MatZp A, MatZp B, int p);
MatZp leeMZp(FILE *f,int p);
int escMatZp(FILE *f, MatZp A);
int LiberaMZp(MatZp *A);


#ifdef __cplusplus
}
#endif

#endif
