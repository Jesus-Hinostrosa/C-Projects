#include <math.h>
#include "hc.h"

#define G2R (M_PII/180.0)
#define OriPla 5
#define PlaObs 5
#define OriObs (OriPla+PlaObs)

typedef struct _aristaHC_{
  R4 A, B;
}aristaHC;

typedef R4 (*frotar)(double, R4);


R4 rotaXY(double a, R4 p)
{
  R4 ret;
  double arad=a*G2R;
  
  ret.x = p.x;
  ret.y = p.y;
  ret.z =  p.z*cos(arad)+p.w*sin(arad);
  ret.w = -p.z*sin(arad)+p.w*cos(arad);
  
  return ret;
}

R4 rotaXZ(double a, R4 p)
{
  R4 ret;
  double arad=a*G2R;
  
  ret.x = p.x;
  ret.y =  p.y*cos(arad)+p.w*sin(arad);
  ret.z = p.z;
  ret.w = -p.y*sin(arad)+p.w*cos(arad);
  
  return ret;
}

R4 rotaXW(double a, R4 p)
{
  R4 ret;
  double arad=a*G2R;
  
  ret.x = p.x;
  ret.y =  p.y*cos(arad)+p.z*sin(arad);
  ret.z = -p.y*sin(arad)+p.z*cos(arad);
  ret.w = p.w;
  
  return ret;
}

R4 rotaYZ(double a, R4 p)
{
  R4 ret;
  double arad=a*G2R;
  
  ret.x =  p.x*cos(arad)+p.w*sin(arad);
  ret.y = p.y;
  ret.z = p.z;
  ret.w = -p.x*sin(arad)+p.w*cos(arad);
  
  return ret;
}

R4 rotaYW(double a, R4 p)
{
  R4 ret;
  double arad=a*G2R;
  
  ret.x =  p.x*cos(arad)+p.z*sin(arad);
  ret.y = p.y;
  ret.z = -p.x*sin(arad)+p.z*cos(arad);
  ret.w = p.w;
  
  return ret;
}

R4 rotaZW(double a, R4 p)
{
  R4 ret;
  double arad=a*G2R;
  
  ret.x =  p.x*cos(arad)+p.y*sin(arad);
  ret.y = -p.x*sin(arad)+p.y*cos(arad);
  ret.z = p.z;
  ret.w = p.w;
  
  return ret;
}



R2 proyecta(R4 p)
{
  R2 ret;
  R4 aux=p;
  
  aux = rotaXY(30, aux);
  //aux = rotaZW(-15, aux);
  ret.x = (aux.y*PlaObs)/(OriObs-aux.x);
  ret.y = (aux.z*PlaObs)/(OriObs-aux.x);

  return ret;
}

int dibujaHipercubo(void (*ds)(double, double, double, double), double teta)
{
  frotar rotar[]={rotaXY, rotaXZ, rotaXW, rotaYZ, rotaYW, rotaZW}; /**/
  int indxEscogidos[]={1, 4}, topeIIndxEscogidos=2;
  int tope=32, i, idx;
  R2 auxA, auxB;
  static int m=0;
  static aristaHC seg[]={
    {{1, 1, 1, 1}, {1, 1, 1, -1}},
    {{1, 1, 1, 1}, {1, 1, -1, 1}},
    {{1, 1, 1, 1}, {1, -1, 1, 1}},
    {{1, 1, 1, 1}, {-1, 1, 1, 1}},
    
    {{-1, -1, -1, -1}, {-1, -1, -1, 1}},
    {{-1, -1, -1, -1}, {-1, -1, 1, -1}},
    {{-1, -1, -1, -1}, {-1, 1, -1, -1}},
    {{-1, -1, -1, -1}, {1, -1, -1, -1}},
    
    {{-1, -1, 1, 1}, {-1, -1, 1, -1}},
    {{-1, -1, 1, 1}, {1, -1, 1, 1}},
    {{-1, -1, 1, 1}, {-1, 1, 1, 1}},
    {{-1, -1, 1, 1}, {-1, -1, -1, 1}},
    
    {{1, 1, -1, -1}, {1, 1, -1, 1}},
    {{1, 1, -1, -1}, {1, -1, -1, -1}},
    {{1, 1, -1, -1}, {-1, 1, -1, -1}},
    {{1, 1, -1, -1}, {1, 1, 1, -1}},
    
    {{1, -1, 1, -1}, {-1, -1, 1, -1}},
    {{1, -1, 1, -1}, {1, 1, 1, -1}},
    {{1, -1, 1, -1}, {1, -1, -1, -1}},
    {{1, -1, 1, -1}, {1, -1, 1, 1}},
    
    {{-1, 1, 1, -1}, {-1, -1, 1, -1}},
    {{-1, 1, 1, -1}, {-1, 1, 1, 1}},
    {{-1, 1, 1, -1}, {1, 1, 1, -1}},
    {{-1, 1, 1, -1}, {-1, 1, -1, -1}},
    
    {{-1, 1, -1, 1}, {-1, 1, -1, -1}},
    {{-1, 1, -1, 1}, {-1, -1, -1, 1}},
    {{-1, 1, -1, 1}, {-1, 1, 1, 1}},
    {{-1, 1, -1, 1}, {1, 1, -1, 1}},
    
    
    {{1, -1, -1, 1}, {1, -1, -1, -1}},
    {{1, -1, -1, 1}, {1, 1, -1, 1}},
    {{1, -1, -1, 1}, {1, -1, 1, 1}},
    {{1, -1, -1, 1}, {-1, -1, -1, 1}},
  };
  
  idx=indxEscogidos[m++%topeIIndxEscogidos];

  int ini=0, fin=32;
  
  for(i=ini; i<fin; i++){
  	seg[i].A = rotar[idx](teta, seg[i].A);
  	seg[i].B = rotar[idx](teta, seg[i].B);
  	auxA = proyecta(seg[i].A);
  	auxB = proyecta(seg[i].B);
  	ds(auxA.x, auxA.y, auxB.x, auxB.y);
  }
  
  return 0;
  
}

