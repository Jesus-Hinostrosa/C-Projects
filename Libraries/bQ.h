#ifndef _H_RACIONAL_
#define _H_RACIONAL_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _racionales_{
  int p, q;
}Q;

Q leeQ(FILE *f);
int escQ(FILE *f, Q a); 
int mcd(int a, int b);
int esCeroQ(Q a); 
int igualQ(Q a, Q b);  
Q simplificaQ(Q a);    
Q creaQ(int num, int den);
Q sumaQ(Q a, Q b);
Q restaQ(Q a, Q b);
Q prodQ(Q a, Q b);
Q divQ(Q a, Q b);


#ifdef __cplusplus
}
#endif

#endif
