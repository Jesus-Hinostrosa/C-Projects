#ifndef _H_MATQ_
#define _H_MATQ_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _MatQ_{
  int m, n;
  Q **ent;
}MatQ;

MatQ iniMatQ(int m, int n);
MatQ sumaMatQ(MatQ A, MatQ B);
MatQ restaMatQ(MatQ A, MatQ B);
MatQ multMatQ(MatQ A, MatQ B);
MatQ leeMQ(FILE *f);
int escMatQ(FILE *f, MatQ A);
int LiberaMQ(MatQ *A);

#ifdef __cplusplus
}
#endif

#endif
