#ifndef _H_MATC_
#define _H_MATC_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _MatC_{
  int m, n;
  C **ent;
}MatC;

MatC iniMatC(int m, int n);
MatC sumaMatC(MatC A, MatC B);
MatC restaMatC(MatC A, MatC B);
MatC multMatC(MatC A, MatC B);
MatC leeMC(FILE *f);
int escMatC(FILE *f, MatC A);
int LiberaMC(MatC *A);



#ifdef __cplusplus
}
#endif

#endif
