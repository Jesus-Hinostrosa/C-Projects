#include <stdio.h>
#include <stdlib.h>

#include "logo.h"
#include "corner.h"

int anguloCorner;
double longitudCorner;
double limiteCorner;
double miX0Corner;
double miY0Corner;
LOGO *tortugaAuxCorner;

int CornerPoly(int a, double l, int tt, LOGO *tortuga);
int CornerPolystep(int a, double l, LOGO *tortuga);

int iniciaCorner(double s, int a, double l, double x, double y, LOGO *tortuga){
  anguloCorner=a;
  longitudCorner = s;
  limiteCorner=l;
  miX0Corner=x;
  miY0Corner=y;
  tortugaAuxCorner = tortuga;
  
  return 0;
}

int dibujaCorner(void){
  inicia(miX0Corner, miY0Corner, 0, ABAJO, tortugaAuxCorner);

  return CornerPoly(anguloCorner, longitudCorner, 0, tortugaAuxCorner);
}

int CornerPoly(int a, double l, int tt, LOGO *tortuga){
  
  if (l<limiteCorner) return 0;
  
  CornerPolystep(a, l, tortuga);
  tt+=a;
  
  if(tt%360!=0)
  CornerPoly(a, l, tt, tortuga);
  
  return 0;
}

int CornerPolystep(int a, double l, LOGO *tortuga){
  avanza(l, tortuga);
  CornerPoly(-a, l/2, 0, tortuga);
  der(a, tortuga);
  return 0;
}
