#ifndef _H_GAUSSIANO_
#define _H_GAUSSIANO_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Gaussianos_{
int  r,i; 
}G;  

G leeG(FILE *f);
int escG(FILE *f, G a); 
int esCeroG(G a); 
int igualG(G a, G b);     
G creaG(int r, int i);
G sumaG(G a, G b);
G restaG(G a, G b);
G prodG(G a, G b);


#ifdef __cplusplus
}
#endif

#endif
