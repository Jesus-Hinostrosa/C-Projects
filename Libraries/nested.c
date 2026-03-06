#include <stdio.h>
#include <stdlib.h>

#include "logo.h"
#include "nested.h"

int nivelRecursionNested;
double longitudNested;
double miX0Nested;
double miY0Nested;
LOGO *tortugaAuxNested;

int NestedTriangle(int n, double l, LOGO *tortuga);

int iniciaNested(int n, double l, double x, double y, LOGO *tortuga)
{
  nivelRecursionNested=n;
  longitudNested = l;
  miX0Nested=x;
  miY0Nested=y;
  tortugaAuxNested = tortuga;
  
  return 0;
}

int dibujaNested(void){
  inicia(miX0Nested, miY0Nested, 0, ABAJO, tortugaAuxNested);

  return NestedTriangle(nivelRecursionNested, longitudNested, tortugaAuxNested);
}

int NestedTriangle(int n, double l, LOGO *tortuga){
	int i;
	if(n==0) return 0;
	
	for(i=0;i<3;i++){
		NestedTriangle(n-1,l/2,tortuga);
		avanza(l,tortuga);
		der(120,tortuga);
	}
	return 0;
}

