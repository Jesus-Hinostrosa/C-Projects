#include <stdio.h>
#include <stdlib.h>

#include "logo.h"
#include "weave.h"

int nivelRecursionWeave;
double longitudWeave;
double parityWeave;
double equisWeave;
double miX0Weave;
double miY0Weave;
LOGO *tortugaAuxWeave;

int Maze(int n, double l, double p, int z, LOGO *tortuga);
int interior(double l, double p, int z, LOGO *tortuga);

int iniciaWeave(int n, double l, double p, int z, double x, double y, LOGO *tortuga)
{
  nivelRecursionWeave=n;
  longitudWeave = l;
  parityWeave=p;
  equisWeave=z;
  miX0Weave=x;
  miY0Weave=y;
  tortugaAuxWeave = tortuga;
  
  return 0;
}

int dibujaWeave(void){
  inicia(miX0Weave, miY0Weave, 0, ABAJO, tortugaAuxWeave);

  return Maze(nivelRecursionWeave, longitudWeave, parityWeave, equisWeave, tortugaAuxWeave);
}

int Maze(int n, double l, double p, int z, LOGO *tortuga){
	double unit;
	int i;
	
	if(n==0){
		interior(l,p,z,tortuga);
		return 0;
	}
	unit=l/3.0;
	Maze(n-1,unit,p,z,tortuga);
	izq(90,tortuga);
	Maze(n-1,unit,p,z,tortuga);
	for(i=0;i<3;i++){
		der(90,tortuga);
		Maze(n-1,unit,p,z,tortuga);
	}
	for(i=0;i<3;i++){
		izq(90,tortuga);
		Maze(n-1,unit,p,z,tortuga);
	}
	der(90,tortuga);
	Maze(n-1,unit,p,z,tortuga);
	
	return 0;
}

int interior(double l, double p, int z, LOGO *tortuga){
	double unit;
	
	p=-p;
	unit=l/5.0;
	if(z){
		p=1;
		izq(45,tortuga);
	}
	avanza(4*unit,tortuga);
	der(90*p,tortuga);
	avanza(3*unit,tortuga);
	der(90*p,tortuga);
	avanza(2*unit,tortuga);
	der(90*p,tortuga);
	avanza(unit,tortuga);
	der(90*p,tortuga);
	avanza(unit,tortuga);
	izq(90*p,tortuga);
	avanza(unit,tortuga);
	izq(90*p,tortuga);
	avanza(2*unit,tortuga);
	izq(90*p,tortuga);
	avanza(3*unit,tortuga);
	izq(90*p,tortuga);
	avanza(4*unit,tortuga);
	izq(90*p,tortuga);
	avanza(4*unit,tortuga);
	der(90*p,tortuga);
	if(z){
		der(90,tortuga);
		avanza(4*unit,tortuga);
		izq(45,tortuga);
	}
	return 0;
}

