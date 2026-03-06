#include <stdio.h>
#include <stdlib.h>

#include "logo.h"
#include "sierpinski.h"

int nivelRecursionSierpinski;
double longitudSierpinski;
double miX0Sierpinski;
double miY0Sierpinski;
LOGO *tortugaAuxSierpinski;

int Oneside(int n, double l, LOGO *tortuga);

int iniciaSierpinski(int n, double l, double x, double y, LOGO *tortuga)
{
  nivelRecursionSierpinski=n;
  longitudSierpinski = l;
  miX0Sierpinski=x;
  miY0Sierpinski=y;
  tortugaAuxSierpinski = tortuga;
  
  return 0;
}

int dibujaSierpinski(void){
	int i;
	double diag;
  inicia(miX0Sierpinski, miY0Sierpinski, 0, ABAJO, tortugaAuxSierpinski);
  diag=longitudSierpinski/sqrt(2);
  for(i=0;i<4;i++){
  	Oneside(nivelRecursionSierpinski,longitudSierpinski,tortugaAuxSierpinski);
  	der(45,tortugaAuxSierpinski);
  	avanza(diag,tortugaAuxSierpinski);
  	der(45,tortugaAuxSierpinski);
  }
  return 0;
}

int Oneside(int n, double l, LOGO *tortuga){
	double diag;
	if(n==0) return 0;
	diag=l/sqrt(2);
	
	Oneside(n-1,l,tortuga);
	der(45,tortuga);
	avanza(diag,tortuga);
	der(45,tortuga);
	Oneside(n-1,l,tortuga);
	izq(90,tortuga);
	avanza(l,tortuga);
	izq(90,tortuga);
	Oneside(n-1,l,tortuga);
	der(45,tortuga);
	avanza(diag,tortuga);
	der(45,tortuga);
	Oneside(n-1,l,tortuga);
	
	
	return 0;
}

