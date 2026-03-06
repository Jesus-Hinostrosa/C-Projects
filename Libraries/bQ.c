#include <stdio.h>    /*funciones de entrada y salida est'andar*/
#include <stdlib.h>   /*funciones de la biblioteca est'andar*/   
#include <string.h>
#include <math.h>

#include "bQ.h"

Q leeQ(FILE *f){
	Q a;

   fscanf(f,"%d%d",&a.p,&a.q);
   a=simplificaQ(a);	
  
  return a;
}
int escQ(FILE *f, Q a){

  fprintf(f, "%+d", a.p);
  if (a.q!= 1) fprintf(f, "/%d", a.q);
  
  return 0;
} 
int mcd(int a, int b){
	int r;             

  if (a < 0) a=-a;
  if (b < 0) b=-b;
  if (b == 0) return a;

  while ((r=a%b) != 0){
    a = b;             
    b = r;             
  }                    

  return b;
}   
int esCeroQ(Q a){
	if(a.p==0) return 1;
	else return 0;
}

int igualQ(Q a, Q b){
	if(a.p==b.p	&& a.q==b.q) return 1;
	else return 0;
}
Q simplificaQ(Q a){
	int d;
  Q regreso;

  regreso = a;
  d = mcd (a.p, a.q);
  if (d>1){            
    regreso.p /= d;         
    regreso.q /= d;         
  }                    
  if (regreso.q < 0){       
    regreso.p *= -1;        
    regreso.q *= -1;        
  }

  return regreso;
}    
Q creaQ(int num, int den){
	Q r = {num, den};

  r=simplificaQ(r);

  return r;
}
Q sumaQ(Q a, Q b){
	Q r={p:a.p*b.q + a.q*b.p, q:a.q*b.q};           
	
  return simplificaQ(r);
}
Q restaQ(Q a, Q b){
	Q r={p:a.p*b.q - a.q*b.p, q:a.q*b.q};           

  return simplificaQ(r);
}
Q prodQ(Q a, Q b){
	Q r={a.p*b.p, a.q*b.q};           

  return simplificaQ(r);
}

Q divQ(Q a, Q b){
	Q r={p:a.p*b.q, q:a.q*b.p};           
	
  return simplificaQ(r);
}

