#include <stdio.h>
#include <stdlib.h>

#include "logo.h"
#include "Ccurve.h"

int nivelRecursionC;
double longitudC;
double miX0C;
double miY0C;
LOGO *tortugaAuxC;

int C(int n, double l, LOGO *tortuga);

int iniciaC(int n, double l, double x, double y, LOGO *tortuga)
{
  nivelRecursionC=n;
  longitudC = l;
  miX0C=x;
  miY0C=y;
  tortugaAuxC = tortuga;
  
  return 0;
}

int dibujaC(void){
  inicia(miX0C, miY0C, 0, ABAJO, tortugaAuxC);

  return C(nivelRecursionC, longitudC, tortugaAuxC);
}

int C(int n, double l, LOGO *tortuga){
	if(n==0){
		avanza(l,tortuga);
		return 0;
	}
	C(n-1,l,tortuga);
	der(90,tortuga);
	C(n-1,l,tortuga);
	izq(90,tortuga);
	return 0;
}

