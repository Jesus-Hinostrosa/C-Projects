#ifndef _H_POLIC_
#define _H_POLIC_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Cx{
   int g;
   C *c;
}Cx;

Cx leeCx(FILE *f);
int escCx(FILE *f, Cx p);
Cx sumaCx(Cx a, Cx b);
Cx restCx(Cx a, Cx b);
Cx multCx(Cx a, Cx b);
Cx multMonoCx(Cx a, C c, int e);
Cx divCx(Cx a, Cx b, Cx *res);
Cx mcdCx(Cx a, Cx b);
Cx derivaCx(Cx a);
Cx integraCx(Cx a);
C evaluaCx(Cx a, C d);
C integraDefCx(Cx p, C a, C b);
int esCeroCx(Cx a);
Cx copiaCx(Cx a);
Cx copiaMenosCx(Cx a);
int  liberaCx(Cx *a);

#ifdef __cplusplus
}
#endif

#endif
