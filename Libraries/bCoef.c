#include <stdio.h>    /*funciones de entrada y salida est'andar*/
#include <stdlib.h>   /*funciones de la biblioteca est'andar*/   
#include <string.h>
#include <math.h>

#include "bQ.h"
#include "bR.h"
#include "bC.h"
#include "bZp.h"
#include "bH.h"
#include "bG.h"
#include "bCoef.h"

int muestraA(FILE *f, void *a, void *b, void *suma, enum tipoCoeficiente tipo)
{
  Q (*fRacional)(Q, Q);
  double (*fReal)(double, double);
  C (*fCompleja)(C, C);
  Zp (*fModulo)(Zp, Zp);
  H (*fCuaternion)(H, H);
  G (*fGaussiana)(G, G);
  
  Q racionalA, racionalB,retQ;
  double realA, realB;
  C complejoA, complejoB, retC;
  Zp zpA, zpB, retZp;
  H cuaternionA, cuaternionB, retH;
  G gaussA, gaussB, retG;

  if (tipo==RACIONALES){
    racionalA = *(Q *)a;
    racionalB = *(Q *)b;
    fRacional = suma;
    retQ = fRacional(racionalA, racionalB);
    fprintf(f,"F(");
    escQ(f,racionalA);
    fprintf(f,",");
    escQ(f,racionalB);
    fprintf(f,")=");
    escQ(f,retQ);
    fprintf(f,"\n");
  } else if (tipo==REALES){
    realA = *(double*)a;
    realB = *(double *)b;
    fReal = suma;
    fprintf(f,"F(%g, %g) = %g\n", realA, realB, fReal(realA, realB));
  } else if (tipo==COMPLEJOS){
    complejoA = *(C *)a;
    complejoB = *(C *)b;
    fCompleja = suma;
    retC = fCompleja(complejoA, complejoB);
    fprintf(f,"F(");
    escC(f,complejoA);
    fprintf(f,",");
    escC(f,complejoB);
    fprintf(f,")=");
    escC(f,retC);
    fprintf(f,"\n");
  } else if (tipo==ZP){
    zpA = *(Zp*)a;
    zpB = *(Zp*)b;
    fModulo = suma;
    retZp=fModulo(zpA,zpB);
    fprintf(f,"F(");
    escZp(f,zpA);
    fprintf(f,",");
    escZp(f,zpB);
    fprintf(f,")=");
    escZp(f,retZp);
    fprintf(f,"\n");
  } else if(tipo==CUATERNIONES){
  	cuaternionA = *(H*)a; 
  	cuaternionB = *(H*)b;
  	fCuaternion=suma;
	retH=fCuaternion(cuaternionA,cuaternionB);
	fprintf(f,"F(");
    escH(f,cuaternionA);
    fprintf(f,",");
    escH(f,cuaternionB);
    fprintf(f,")=");
    escH(f,retH);
    fprintf(f,"\n");
  }else if(tipo==GAUSSIANOS){
  	gaussA = *(G*)a;
  	gaussB = *(G*)b;
  	fGaussiana=suma;
  	retG=fGaussiana(gaussA,gaussB);
  	fprintf(f,"F(");
    escG(f,gaussA);
    fprintf(f,",");
    escG(f,gaussB);
    fprintf(f,")=");
    escG(f,retG);
    fprintf(f,"\n");
  }

  return 0;
}

int muestraB(FILE *f, Coeficiente a, Coeficiente  b, void *suma, enum tipoCoeficiente tipo)
{
  Q (*fRacional)(Q, Q);
  double (*fReal)(double, double);
  C (*fCompleja)(C, C);
  Zp (*fModulo)(Zp, Zp);
  H (*fCuaternion)(H, H);
  G (*fGaussiana)(G, G);
  Q racionalA, racionalB, retQ;
  C retC;
  Zp retZp;
  H retH;
  G retG;

  if (tipo==RACIONALES){
    fRacional = suma;
    retQ = fRacional(a.unRacional, b.unRacional);
    fprintf(f,"F(");
    escQ(f,a.unRacional);
    fprintf(f,",");
    escQ(f,b.unRacional);
    fprintf(f,")=");
    escQ(f,retQ);
    fprintf(f,"\n");
  } else if (tipo==REALES){
    fReal = suma;
    fprintf(f,"F(%g, %g) = %g\n", a.unReal, b.unReal, fReal(a.unReal, b.unReal));
  } else if (tipo==COMPLEJOS){
    fCompleja = suma;
    retC = fCompleja(a.unComplejo, b.unComplejo);
    fprintf(f,"F(");
    escC(f,a.unComplejo);
    fprintf(f,",");
    escC(f,b.unComplejo);
    fprintf(f,")=");
    escC(f,retC);
    fprintf(f,"\n");
  } else if (tipo==ZP){
    fModulo = suma;
    retZp=fModulo(a.unZp,b.unZp);
    fprintf(f,"F(");
    escZp(f,a.unZp);
    fprintf(f,",");
    escZp(f,b.unZp);
    fprintf(f,")=");
    escZp(f,retZp);
    fprintf(f,"\n");
  } else if(tipo==CUATERNIONES){
  	fCuaternion=suma;
	retH=fCuaternion(a.unCuate,b.unCuate);
	fprintf(f,"F(");
    escH(f,a.unCuate);
    fprintf(f,",");
    escH(f,b.unCuate);
    fprintf(f,")=");
    escH(f,retH);
    fprintf(f,"\n");
  }else if(tipo==GAUSSIANOS){
  	fGaussiana=suma;
  	retG=fGaussiana(a.unGauss, b.unGauss);
  	fprintf(f,"F(");
    escG(f,a.unGauss);
    fprintf(f,",");
    escG(f,b.unGauss);
    fprintf(f,")=");
    escG(f,retG);
    fprintf(f,"\n");
  }
  
   
  return 0;
}
Coeficiente leeCoef(FILE *f, enum tipoCoeficiente tipo, int p){
	Coeficiente ret;
  
    if (tipo==RACIONALES){
        ret.unRacional=leeQ(f);
  } else if (tipo==REALES){
		fscanf(f,"%lf",&ret.unReal);
  } else if (tipo==CUATERNIONES){
        ret.unCuate=leeH(f);
  } else if (tipo==GAUSSIANOS){
  	    ret.unGauss=leeG(f);
  } else if (tipo==ZP){
        ret.unZp=leeZp(f,p);
  } else if (tipo==COMPLEJOS){
        ret.unComplejo=leeC(f);
  }
  
  return ret;
}

