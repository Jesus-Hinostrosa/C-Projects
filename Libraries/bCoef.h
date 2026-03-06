#ifndef _H_COEFICIENTE_
#define _H_COEFICIENTE_

#ifdef __cplusplus
extern "C" {
#endif

enum tipoCoeficiente {RACIONALES, REALES, CUATERNIONES, GAUSSIANOS, ZP, COMPLEJOS, TOTAL};

typedef union _coeficiente_{
  Q unRacional;
  double unReal;
  C unComplejo;
  Zp unZp;
  H unCuate;
  G unGauss;
  
}Coeficiente;

int muestraA(FILE *f, void *a, void *b, void *suma, enum tipoCoeficiente tipo);
int muestraB(FILE *f, Coeficiente a, Coeficiente b, void *suma, enum tipoCoeficiente tipo);
Coeficiente leeCoef(FILE *f, enum tipoCoeficiente tipo, int p);

#ifdef __cplusplus
}
#endif

#endif
