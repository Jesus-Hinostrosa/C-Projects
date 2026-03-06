#ifndef _H_POLIQ_
#define _H_POLIQ_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Qx{
  int g;
  Q *c;
}Qx;

Qx leeQx(FILE *f);
int escQx(FILE *f, Qx p);
Qx sumaQx(Qx a, Qx b);
Qx restQx(Qx a, Qx b);
Qx multQx(Qx a, Qx b);
Qx multMonoQx(Qx a, Q c, int e);
Qx divQx(Qx a, Qx b, Qx *r);
Qx mcdQx(Qx a, Qx b);
Qx derivaQx(Qx a);
Qx integraQx(Qx a);
Q evaluaQx(Qx a, Q d);
Q integraDefQx(Qx p, Q a, Q b);
int esCeroQx(Qx a);
Qx copiaQx(Qx a);
Qx copiaMenosQx(Qx a);
int  liberaQx(Qx *a);

#ifdef __cplusplus
}
#endif

#endif
