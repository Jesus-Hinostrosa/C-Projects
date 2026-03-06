#include <stdio.h>    /*funciones de entrada y salida est'andar*/
#include <stdlib.h>   /*funciones de la biblioteca est'andar*/   
#include <string.h>
#include <math.h>

#include "bH.h"

#define EPSILON 1e-15

H leeH(FILE *f){
	H a;

   fscanf(f,"%lg%lg%lg%lg",&a.r,&a.i,&a.j,&a.k);	
  
  return a;
}
int escH(FILE *f, H x){
	if(esCeroH(x)){
		fprintf(f,"0");
	 	return 0;	
	}
	
	if(x.r==0.0);
	else fprintf(f,"%lg",x.r);
    if(x.i==0.0);
    else {
    if(x.i==1.0) fprintf(f,"+i");
    else{
    	if(x.i==-1.0) fprintf(f,"-i");
    	else fprintf(f,"%+lgi",x.i);
		}
	}
    if(x.j==0.0);
	else {
    	if(x.j==1.0) fprintf(f,"+j");
    	else{
    	    if(x.j==-1.0) fprintf(f,"-j");
    	    else fprintf(f,"%+lgj",x.j);
    	    }
	    }
    if(x.k==0.0);
    else{
    	if(x.k==1.0) fprintf(f,"+k");
    	else{
			if(x.k==-1.0) fprintf(f,"-k");
    	    else fprintf(f,"%+lgk",x.k);
			} 
	    }
	return 0;	 
} 
int esCeroH(H a){
	if(a.r==0.0 && a.i==0.0 && a.j==0.0 && a.k==0.0) return 1;
	else return 0;
} 
int igualH(H a, H b){
	if(a.r==b.r && a.i==b.i && a.j==b.j && a.k==b.k) return 1;
	else return 0;
}     
H creaH(double rea, double im, double jim, double kim){
	H ret={r:rea, i:im, j:jim, k: kim};
	return ret;
}
H sumaH(H a, H b){
	H ret={r:a.r+b.r, i:a.i+b.i, j:a.j+b.j, k:a.k+b.k}; 
	return ret;
}
H restaH(H a, H b){
	H ret={r:a.r-b.r, i:a.i-b.i, j:a.j-b.j, k:a.k-b.k}; 
	return ret;
}
H prodH(H x, H y){
	H ret={ x.r*y.r - x.i*y.i - x.j*y.j - x.k*y.k,
    		x.r*y.i + x.i*y.r + x.j*y.k - x.k*y.j,
    		x.r*y.j - x.i*y.k + x.j*y.r + x.k*y.i,
    		x.r*y.k + x.i*y.j - x.j*y.i + x.k*y.r};

  if (-EPSILON <= ret.r && ret.r <= EPSILON) ret.r = 0.0;
  if (-EPSILON <= ret.i && ret.i <= EPSILON) ret.i = 0.0;
  if (-EPSILON <= ret.j && ret.j <= EPSILON) ret.j = 0.0;
  if (-EPSILON <= ret.k && ret.k <= EPSILON) ret.k = 0.0;

  return ret;
}
H invH(H a){
	double norm2=a.r*a.r+a.i*a.i+a.j*a.j+a.k*a.k;
  H ret={a.r, -a.i, -a.j, -a.k};

  if (norm2==0.0) return a;
  ret.r/=norm2;
  ret.i/=norm2;
  ret.j/=norm2;
  ret.k/=norm2;

  if (-EPSILON <= ret.r && ret.r <= EPSILON) ret.r = 0.0;
  if (-EPSILON <= ret.i && ret.i <= EPSILON) ret.i = 0.0;
  if (-EPSILON <= ret.j && ret.j <= EPSILON) ret.j = 0.0;
  if (-EPSILON <= ret.k && ret.k <= EPSILON) ret.k = 0.0;

  return ret;
}

H divH(H a, H b){
	H r;
	
	return prodH(a, invH(b)); 
}
