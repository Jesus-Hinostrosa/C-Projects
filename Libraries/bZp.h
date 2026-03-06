#ifndef _H_ZP_
#define _H_ZP_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ZP_{
   int p,n;
}Zp;

Zp leeZp(FILE *f, int p);
int escZp(FILE *f, Zp a);
int simpZp(Zp d);
Zp creaZp(int n, int p);
Zp sumaZp(Zp a, Zp b);
Zp restaZp(Zp a, Zp b);
Zp prodZp(Zp a, Zp b);
Zp invZp(Zp d);
Zp divZp(Zp a, Zp b);

#ifdef __cplusplus
}
#endif

#endif
