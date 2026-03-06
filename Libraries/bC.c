#include <stdio.h>    /*funciones de entrada y salida est'andar*/
#include <stdlib.h>   /*funciones de la biblioteca est'andar*/   
#include <string.h>
#include <math.h>

#include "bC.h"

C leeC(FILE *f){
	C a;

   fscanf(f,"%lg%lg",&a.r,&a.i);	
  
  return a;
}
int escC(FILE *f, C a){
	if(a.r==0.0 &&a.i==0.0) fprintf(f,"0");
     else{
     	if(a.r==0.0);
     	else fprintf(f,"%+lg",a.r);
     	if (a.i==0.0);
     	else{
     		if(a.i==1.0) fprintf(f,"+i");
     		else{
     			if(a.i==-1.0) fprintf(f,"-i");
     		    else fprintf(f,"%+lgi",a.i);	
			 }
     		
		 }
	 }
	 return 0;
} 
int esCeroC(C a){
	if(a.r==0.0 && a.i==0.0) return 1;
	else return 0;
} 
int igualC(C a, C b){
	if(a.r==b.r	&& a.i==b.i) return 1;
	else return 0;
}     
C creaC(int num, int den){
	C r = {num, den};

  return r;
}
C sumaC(C a, C b){
	C r={r:a.r+b.r, i:a.i+b.i};           
	
  return r;
}
C restaC(C a, C b){
	C r={r:a.r-b.r, i:a.i-b.i};           
	
  return r;
}
C prodC(C a, C b){
	C r={r:a.r*b.r-a.i*b.i, i:a.r*b.i+a.i*b.r};           
	
  return r;
}
C invC(C a){
	C c; 
	double n;
	
	n=a.r*a.r+a.i*a.i;
	c.r=a.r/n;
	c.i=-a.i/n;
	
	return c;
}
C divC(C a, C b){
	C c;
	
	b=invC(b);
	c=prodC(a,b);
	
	return c;
}

