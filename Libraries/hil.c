#include <stdio.h>
#include <stdlib.h>

#include "logo.h"
#include "hil.h"

int nivelRecursionHil;
double longitudHil;
double parityHil;
double miX0Hil;
double miY0Hil;
LOGO *tortugaAuxHil;

int Hilbert(int n, double l, double p, LOGO *tortuga);

int iniciaHil(int n, double l, double p, double x, double y, LOGO *tortuga)
{
  nivelRecursionHil=n;
  longitudHil = l;
  parityHil=p;
  miX0Hil=x;
  miY0Hil=y;
  tortugaAuxHil = tortuga;
  
  return 0;
}

int dibujaHil(void){
  inicia(miX0Hil, miY0Hil, 0, ABAJO, tortugaAuxHil);

  return Hilbert(nivelRecursionHil, longitudHil, parityHil, tortugaAuxHil);
}

int Hilbert(int n, double l, double p, LOGO *tortuga){
	if(n==0) return 0;
	
	izq(p*90,tortuga);
	Hilbert(n-1,l,-p,tortuga);
	avanza(l,tortuga);
	der(p*90,tortuga);
	Hilbert(n-1,l,p,tortuga);
	avanza(l,tortuga);
	Hilbert(n-1,l,p,tortuga);
	der(p*90,tortuga);
	avanza(l,tortuga);
	Hilbert(n-1,l,-p,tortuga);
	izq(p*90,tortuga);
	
	return 0;
}

