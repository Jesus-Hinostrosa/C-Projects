#include <stdio.h>    /*funciones de entrada y salida est'andar*/
#include <stdlib.h>   /*funciones de la biblioteca est'andar*/   
#include <string.h>
#include <math.h>

#include "bZp.h"

Zp leeZp(FILE *f, int p){
  Zp a;
  a.p=p;
  
  fscanf(f,"%d",&a.n);
  a.n=simpZp(a);
  return a;
}

int escZp(FILE *f, Zp a){
  fprintf(f,"%d",a.n);
  return 0;
}

int simpZp(Zp d){
	
 d.n=((d.n%d.p)+d.p)%d.p;
 return d.n;	
}

Zp creaZp(int n, int p){
	Zp a;
	a.p=p;
	a.n=n;
	simpZp(a);
	
	return a;
}

Zp sumaZp(Zp a, Zp b){
	
  Zp r;
  r.p=a.p;
  r.n=a.n+b.n;
  r.n=simpZp(r);
  return r;	
}

Zp restaZp(Zp a, Zp b){
	
  Zp r;
  r.p=a.p;
  r.n=a.n-b.n;
  r.n=simpZp(r);
  return r;	
}

Zp prodZp(Zp a, Zp b){
	
  Zp r;
  r.p=a.p;
  r.n=a.n*b.n;
  r.n=simpZp(r);
  return r;	
}

Zp invZp(Zp d){
	
   int r,q,s,s0,s_1,a,b,p;	
    a=d.n;
    b=d.p;	
    s0=0;
    s_1=1;
    while((r=a%b)!=0){
      q = a/b;
      a=b;
      b=r;
      s=s0;
      s0=s_1-q*s0;
      s_1=s;
    }
	d.n=s0;
    d.n=simpZp(d);
	s0=((s0%p)+p)%p;
    
    return d;
}

Zp divZp(Zp a, Zp b){
  Zp r;
  b=invZp(b);
  r=prodZp(a,b);
  return r;		
}

