#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> 
#include<string.h> 

#include "bpoliR.h"

double leeR(FILE *f){
  double ret;

  fscanf(f, "%lg", &ret);

  return ret;
}

Rx leeP(FILE *f)
{
  Rx ret;
  int i;

  printf("Por leer el grado\n");
  fscanf(f,"%d", &(ret.g));

  if((ret.c=(double*)malloc((ret.g+1)*sizeof(double)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for (i=0; i<=ret.g; i++)
    ret.c[i]=leeR(f);

  return ret;
}

int escP(FILE *f, Rx p){
  int i;
  
  if(p.g<0){
    fprintf(f, " 0\n\n");
    return 0;
  }

	if (p.c[0]!=0.0) fprintf(f,"%+lg ", p.c[0]);
	if(p.c[1]!=0.0){
  		if(p.c[1]==1.0) fprintf(f,"+x");
    	else fprintf(f,"%+lg x ", p.c[1]);	
		}
		  
  	for(i=2; i<=p.g; i++){
	if (p.c[i]!=0.0){
    	if(p.c[i]==1.0) fprintf(f,"+x^%d ", i);
    	else fprintf(f,"%+lg x^%d ", p.c[i], i);
	} 
  }
    
  fprintf(f,"\n\n");
  
  return 0;
}

Rx suma(Rx a, Rx b)
{
  Rx ret;
  int i, min;

  if (a.g<0){
    return copiaP(b);
  }
  if (b.g<0){
    return copiaP(a);
  }
  if (a.g<b.g){
    min = a.g;
    ret.g = b.g;
  } else{
    min = b.g;
    ret.g = a.g;
  }
  if((ret.c=(double*)malloc((ret.g+1)*sizeof(double)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  for (i=0; i<=min; i++) ret.c[i]=a.c[i]+b.c[i];
  if (a.g==min){
    for (; i<=ret.g; i++) ret.c[i]=b.c[i];
  }
  if (b.g==min){
    for (; i<=ret.g; i++) ret.c[i]=a.c[i];
  }
  while(ret.g>=0 && ret.c[ret.g]==0.0) ret.g--;
  if (ret.g<0){
    free(ret.c);
    ret.c = NULL;
  }
  return ret;
}

Rx rest(Rx a, Rx b)
{
  Rx ret;
  int i, min;

  if (a.g<0){
    return copiaMenosP(b);
  }
  if (b.g<0){
    return copiaP(a);
  }
  if (a.g<b.g){
    min = a.g;
    ret.g = b.g;
  } else{
    min = b.g;
    ret.g = a.g;
  }
  if((ret.c=(double*)malloc((ret.g+1)*sizeof(double)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  for (i=0; i<=min; i++) ret.c[i]=a.c[i]-b.c[i];
  if (a.g==min){
    for (; i<=ret.g; i++) ret.c[i]=-b.c[i];
  }
  if (b.g==min){
    for (; i<=ret.g; i++) ret.c[i]=a.c[i];
  }
  while(ret.g>=0 && ret.c[ret.g]==0.0) ret.g--;
  if (ret.g<0){
    free(ret.c);
    ret.c = NULL;
  }
  return ret;
}

Rx mult(Rx a, Rx b)
{
  int i, j;
  Rx ret;

  ret.g=a.g+b.g;
  if((ret.c=(double*)malloc((ret.g+1)*sizeof(double)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  for (i=0; i<=ret.g; i++) ret.c[i]=0.0;
  for (i=0; i<=a.g; i++)
    for(j=0; j<=b.g; j++)
      ret.c[i+j]+=a.c[i]*b.c[j];

  return ret;
}

Rx multMonomio(Rx a, double c, int e)
{
  int i;
  Rx ret;

  ret.g=a.g+e;
  if((ret.c=(double*)malloc((ret.g+1)*sizeof(double)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for (i=0; i<=ret.g; i++) ret.c[i]=0.0;
  for (i=e; i<=ret.g; i++) ret.c[i]=a.c[i-e]*c;

  return ret;
}

int esCero(Rx a)
{
  return a.g <0;
}


Rx divR(Rx a, Rx b, Rx *r)
{
  Rx q, aux, a_aux;
  double coef;
  int grad, i;
  
  a_aux= copiaP(a);
  a=a_aux;

  if (a.g<b.g){
    q.g=-1;
    q.c=NULL;
    *r = copiaP(a);

    return q;
  }

  q.g=a.g-b.g;
  if((q.c=(double*)malloc((q.g+1)*sizeof(double)))==NULL){
    printf("error al generar espacio.\n");
    q.g = -1;
    return q;
  }
  for (i=0; i<=q.g; i++) q.c[i]=0.0;

  do{
    grad=a.g-b.g;
    q.c[grad] = a.c[a.g]/b.c[b.g];
    aux = multMonomio(b, q.c[grad], grad);
    a_aux = rest(a, aux);
    liberaP(&a);
    liberaP(&aux);
    a = a_aux;
  liberaP(r);
    *r=copiaP(a);
  }while(!esCero(*r) && (r->g>=b.g));


  return q;
}

Rx mcdR(Rx a, Rx b){
	Rx aaux,baux,r={g:-1,c:NULL};
	
	if(esCero(b)){
		return a;
	}
	
	aaux=copiaP(a);
	a=aaux;
	
	baux=copiaP(b);
	b=baux;
	
	divR(aaux,baux,&r);

	while(!esCero(r)){
	   divR(aaux,baux,&r);
	   aaux=copiaP(baux);
	   liberaP(&baux);
	   baux=copiaP(r);
	   liberaP(&r);
	   }
	return baux;
}

Rx derivaR(Rx a){
	Rx ret={g:a.g-1,c:NULL};
	int i;
	
	if((ret.c=(double*)malloc((ret.g+1)*sizeof(double)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
	
	for(i=0;i<=ret.g;i++) ret.c[i]=(i+1)*a.c[i+1];
	
	return ret;
}

Rx integraR(Rx a){
	Rx ret={g:a.g+1,c:NULL};
	int i;
	
	if((ret.c=(double*)malloc((ret.g+1)*sizeof(double)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
    
    ret.c[0]=0.0;
    for(i=1;i<=ret.g;i++) ret.c[i]=a.c[i-1]/i;
	
	return ret;
}

double evaluaR(Rx a, double d){
	double r=0.0;
	int i;

	for(i=0;i<=a.g;i++) r+=a.c[i]*pow(d,i);
	return r;
}

double integraDefR(Rx p, double a, double b){
	double P_b,P_a;
	Rx P;
	
	P=integraR(p);
	P_b=evaluaR(P,b);
	P_a=evaluaR(P,a);
	
	return P_b-P_a;	
}

Rx copiaP(Rx a)
{
  Rx ret;
  int i;

  ret.g = a.g;
  if (ret.g<0){
    ret.c=NULL;
    return ret;
  }
  if((ret.c=(double*)malloc((ret.g+1)*sizeof(double)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for(i=0; i<=ret.g; i++) ret.c[i]=a.c[i];

  return ret;
}

Rx copiaMenosP(Rx a)
{
  Rx ret;
  int i;

  ret.g = a.g;
  if (ret.g<0){
    ret.c=NULL;
    return ret;
  }
  if((ret.c=(double*)malloc((ret.g+1)*sizeof(double)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for(i=0; i<=ret.g; i++) ret.c[i]=-a.c[i];

  return ret;
}

int  liberaP(Rx *a) 
{
  if(a->c!=NULL) free(a->c);
  a->g=-1;
  a->c=NULL;
  return 0;	
}
