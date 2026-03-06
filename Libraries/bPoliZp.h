#ifndef _H_POLIZP_
#define _H_POLIZP_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct zpx{
  int g;
  Zp *c;
}Zpx;

Zpx leeZpx(FILE *f, int p);
int escZpx(FILE *f, Zpx p);
Zpx sumaZpx(Zpx a, Zpx b);
Zpx restZpx(Zpx a, Zpx b);
Zpx multZpx(Zpx a, Zpx b);
Zpx multMonoZpx(Zpx a, Zp b, int e);
Zpx divZpx(Zpx a, Zpx b, Zpx *res);
Zpx mcdZpx(Zpx a, Zpx b);
Zpx derivaZpx(Zpx a);
Zpx integraZpx(Zpx a);
Zp evaluaZpx(Zpx a, Zp d);
Zp integraDefZpx(Zpx p, Zp a, Zp b);
int esCeroZpx(Zpx a);
Zpx copiaZpx(Zpx a);
Zpx copiaMenosZpx(Zpx a);
int liberaZpx(Zpx *a);

#ifdef __cplusplus
}
#endif

#endif
