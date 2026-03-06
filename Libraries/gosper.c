#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "logo.h"
#include "gosper.h"

int nivelRecursionGosper;
double longitudGosper;
double miX0Gosper;
double miY0Gosper;
LOGO *tortugaAuxGosper;

int LGosper(int n, double l, LOGO *tortuga);
int RGosper(int n, double l, LOGO *tortuga);

int iniciaGosper(int n, double l, double x, double y, LOGO *tortuga)
{
  nivelRecursionGosper=n;
  longitudGosper = l;
  miX0Gosper=x;
  miY0Gosper=y;
  tortugaAuxGosper = tortuga;
  
  return 0;
}

int dibujaGosper(void){
  inicia(miX0Gosper, miY0Gosper, 0, ABAJO, tortugaAuxGosper);

  return RGosper(nivelRecursionGosper, longitudGosper, tortugaAuxGosper);
}

int RGosper(int n, double l, LOGO *tortuga){
	double unit;
	
	unit=l/sqrt(7);
	
	if(n==0){
		avanza(l,tortuga);
		return 0;
	}
	der(75,tortuga);
	LGosper(n-1,unit,tortuga);
	izq(60,tortuga);
	RGosper(n-1,unit,tortuga);
	RGosper(n-1,unit,tortuga);
	izq(120,tortuga);
	RGosper(n-1,unit,tortuga);
	izq(60,tortuga);
	LGosper(n-1,unit,tortuga);
	der(120,tortuga);
	LGosper(n-1,unit,tortuga);
	der(60,tortuga);
	RGosper(n-1,unit,tortuga);
	izq(15,tortuga);
	
	return 0;
}
int LGosper(int n, double l, LOGO *tortuga){
	double unit;
	
	unit=l/sqrt(7);
	
	if(n==0){
		avanza(l,tortuga);
		return 0;
	}
	der(15,tortuga);
	LGosper(n-1,unit,tortuga);
	izq(60,tortuga);
	RGosper(n-1,unit,tortuga);
	izq(120,tortuga);
	RGosper(n-1,unit,tortuga);
	der(60,tortuga);
	LGosper(n-1,unit,tortuga);
	der(120,tortuga);
	LGosper(n-1,unit,tortuga);
	LGosper(n-1,unit,tortuga);
	der(60,tortuga);
	RGosper(n-1,unit,tortuga);
	izq(75,tortuga);
	
	return 0;
}
