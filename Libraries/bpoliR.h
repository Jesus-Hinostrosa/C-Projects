#ifndef _H_POLREAL_
#define _H_POLREAL_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Rx_{
  int g;
  double *c;
}Rx;

double leeR(FILE *f);
int escR(FILE *f,double a);

Rx leeP(FILE *f);
Rx suma(Rx a, Rx b);
Rx rest(Rx a, Rx b);
Rx mult(Rx a, Rx b);
Rx multMonomio(Rx a, double c, int e);
Rx divR(Rx a, Rx b, Rx *r);
Rx mcdR(Rx a, Rx b);
Rx derivaR(Rx a);
Rx integraR(Rx a);
double evaluaR( Rx a, double d);
double integraDefR(Rx p, double a, double b);
int esCero(Rx a);
Rx copiaP(Rx a);
Rx copiaMenosP(Rx a);
int  liberaP(Rx *a);

#ifdef __cplusplus
}
#endif

#endif
