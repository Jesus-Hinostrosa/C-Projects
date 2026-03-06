#ifndef _H_POLIH_
#define _H_POLIH_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Hx{
int g;
H *c;	
}Hx;

Hx leeHx(FILE *f);
int escHx(FILE *f, Hx p);
Hx sumaHx(Hx a, Hx b);
Hx restHx(Hx a, Hx b);
Hx multHx(Hx a, Hx b);
Hx multMonoHx(Hx a, H c, int e);
Hx divHx(Hx a, Hx b, Hx *res);
Hx mcdHx(Hx a, Hx b);
Hx derivaHx(Hx a);
Hx integraHx(Hx a);
H evaluaHx(Hx a, H d);
H integraDefHx(Hx p, H a, H b);
int esCeroHx(Hx a);
Hx copiaHx(Hx a);
Hx copiaMenosHx(Hx a);
int  liberaHx(Hx *a);

#ifdef __cplusplus
}
#endif

#endif
