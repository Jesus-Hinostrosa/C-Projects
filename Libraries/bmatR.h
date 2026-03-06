#ifndef _H_POLREAL_
#define _H_POLREAL_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _MatR_{
  int m, n;
  double **ent;
}MatR;

double leeR(FILE *f);
int escR(FILE *f,double a);

MatR iniMatR(int m, int n);
MatR sumaMatR(MatR A, MatR B);
MatR restaMatR(MatR A, MatR B);
MatR multMatR(MatR A, MatR B);
MatR leeMR(FILE *f);
int escMatR(FILE *f, MatR A);
int LiberaMR(MatR *A);

#ifdef __cplusplus
}
#endif

#endif
