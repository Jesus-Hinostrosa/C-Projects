#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "logo.h"
#include "hooksnow.h"

int nivelRecursionHooksnow;
double longitudHooksnow;
double miX0Hooksnow;
double miY0Hooksnow;
LOGO *tortugaAuxHooksnow;

int LSnow(int n, double l, LOGO *tortuga);
int RSnow(int n, double l, LOGO *tortuga);

int iniciaHooksnow(int n, double l, double x, double y, LOGO *tortuga)
{
  nivelRecursionHooksnow=n;
  longitudHooksnow = l;
  miX0Hooksnow=x;
  miY0Hooksnow=y;
  tortugaAuxHooksnow = tortuga;
  
  return 0;
}

int dibujaHooksnow(void){
  inicia(miX0Hooksnow, miY0Hooksnow, 0, ABAJO, tortugaAuxHooksnow);

  return RSnow(nivelRecursionHooksnow, longitudHooksnow, tortugaAuxHooksnow);
}

int RSnow(int n, double l, LOGO *tortuga){
	double unit, sunit;
	if(n==0){
		avanza(l,tortuga);
		return 0;
	}
	
	unit=l/3.0;
	sunit=2.0*l*sin(M_PI/3)/9.0;
	
	izq(60,tortuga);
	LSnow(n-1,unit,tortuga);
	RSnow(n-1,unit,tortuga);
	der(60,tortuga);
	RSnow(n-1,unit,tortuga);
	der(60,tortuga);
	RSnow(n-1,unit,tortuga);
	der(150,tortuga);
	RSnow(n-1,sunit,tortuga);
	LSnow(n-1,sunit,tortuga);
	izq(60,tortuga);
	RSnow(n-1,sunit,tortuga);
	izq(60,tortuga);
	LSnow(n-1,sunit,tortuga);
	RSnow(n-1,sunit,tortuga);
	izq(90,tortuga);
	LSnow(n-1,unit,tortuga);
	RSnow(n-1,unit,tortuga);
	
	return 0;
}

int LSnow(int n, double l, LOGO *tortuga){
	double unit, sunit;
	if(n==0){
		avanza(l,tortuga);
		return 0;
	}
	
	unit=l/3.0;
	sunit=2.0*l*sin(M_PI/3)/9.0;
	
	LSnow(n-1,unit,tortuga);
	RSnow(n-1,unit,tortuga);
	der(90,tortuga);
	LSnow(n-1,sunit,tortuga);
	RSnow(n-1,sunit,tortuga);
	der(60,tortuga);
	LSnow(n-1,sunit,tortuga);
	der(60,tortuga);
	RSnow(n-1,sunit,tortuga);
	LSnow(n-1,sunit,tortuga);
	izq(150,tortuga);
	LSnow(n-1,unit,tortuga);
	izq(60,tortuga);
	LSnow(n-1,unit,tortuga);
	izq(60,tortuga);
	LSnow(n-1,unit,tortuga);
	RSnow(n-1,unit,tortuga);
	der(60,tortuga);
	
	return 0;
}

