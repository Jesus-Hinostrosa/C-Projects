#ifndef _H_CUATERNION_
#define _H_CUATERNION_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Cuaterniones_{
double r,i,j,k;	
}H;

H leeH(FILE *f);
int escH(FILE *f, H x); 
int esCeroH(H a); 
int igualH(H a, H b);     
H creaH(double rea, double im, double jim, double kim);
H sumaH(H a, H b);
H restaH(H a, H b);
H prodH(H x, H y);
H invH(H a);
H divH(H a, H b);

#ifdef __cplusplus
}
#endif

#endif
