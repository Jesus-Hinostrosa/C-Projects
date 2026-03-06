#ifndef _H_COMPLEJOS_
#define _H_COMPLEJOS_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct C{
   double r,i;
}C;

C leeC(FILE *f);
int escC(FILE *f, C a); 
int esCeroC(C a); 
int igualC(C a, C b);     
C creaC(int num, int den);
C sumaC(C a, C b);
C restaC(C a, C b);
C prodC(C a, C b);
C invC(C a);
C powC(C a, int g);
C divC(C a, C b);

#ifdef __cplusplus
}
#endif

#endif
