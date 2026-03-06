#include <stdio.h>    /*funciones de entrada y salida est'andar*/
#include <stdlib.h>   /*funciones de la biblioteca est'andar*/   
#include <string.h>
#include <math.h>

#include "bG.h"

G leeG(FILE *f){
	G a;

   fscanf(f,"%d%d",&a.r,&a.i);	
  
  return a;
}
int escG(FILE *f, G a){
	if(a.r==0 &&a.i==0) fprintf(f,"0");
     else{
     	if(a.r==0);
     	else fprintf(f,"%+d",a.r);
     	if (a.i==0);
     	else{
     		if(a.i==1) fprintf(f,"+i");
     		else{
     			if(a.i==-1) fprintf(f,"-i");
     		    else fprintf(f,"%+di",a.i);	
			 }
     		
		 }
	 }
	return 0;
} 
int esCeroG(G a){
	if(a.r==0 && a.i==0) return 1;
	else return 0;
} 
int igualG(G a, G b){
	if(a.r==b.r	&& a.i==b.i) return 1;
	else return 0;
}     
G creaG(int rea, int ima){
	G r = {r:rea, i:ima};

  return r;
}
G sumaG(G a, G b){
	G r={r:a.r+b.r, i:a.i+b.i};           
	
  return r;
}
G restaG(G a, G b){
	G r={r:a.r-b.r, i:a.i-b.i};           
	
  return r;
}
G prodG(G a, G b){
	G r={r:a.r*b.r-a.i*b.i, i:a.r*b.i+a.i*b.r};           
	
  return r;
}

