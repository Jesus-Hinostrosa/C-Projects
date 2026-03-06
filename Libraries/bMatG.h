#ifndef _H_MATG_
#define _H_MATG_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _MATRIZ_{
	int m,n;
	G **ent;
}MatG;

MatG iniMatG(int m, int n);
MatG sumaMatG(MatG A, MatG B);
MatG restaMatG(MatG A, MatG B);
MatG multMatG(MatG A, MatG B);
MatG leeMG(FILE *f);
int escMatG(FILE *f, MatG A);
int LiberaMG(MatG *A);

#ifdef __cplusplus
}
#endif

#endif
