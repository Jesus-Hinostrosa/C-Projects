#ifndef _HIIPERCUBO_H_
#define _HIIPERCUBO_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef struct _R4_{
  double x, y, z, w;	
}R4;

typedef struct _R2_{
  double x, y;
}R2;

R2 proyecta(R4);
R4 rotaXY(double, R4);
R4 rotaXZ(double, R4);
R4 rotaXW(double, R4);
R4 rotaYZ(double, R4);
R4 rotaYW(double, R4);
R4 rotaZW(double, R4);

int dibujaHipercubo(void (*ds)(double, double, double, double), double);



#ifdef __cplusplus
}
#endif

#endif
