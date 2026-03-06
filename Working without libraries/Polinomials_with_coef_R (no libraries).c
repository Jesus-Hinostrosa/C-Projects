#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> /*archivo de cabecera para manejo de errores*/
#include<string.h> /*archivo de cabecera para la funcion strerror()*/

typedef struct _Rx_{
  int g;
  double *c;
}Rx;

double leeR(FILE *f);
int escR(FILE *f,double a);

Rx leeP(FILE *f);
Rx suma(Rx a, Rx b);
Rx rest(Rx a, Rx b);
Rx mult(Rx a, Rx b);
Rx multMonomio(Rx a, double c, int e);
Rx divR(Rx a, Rx b, Rx *r);
Rx mcdR(Rx a, Rx b);
Rx derivaR(Rx a);
Rx integraR(Rx a);
double evaluaR( Rx a, double d);
double integraDefR(Rx p, double a, double b);
int esCero(Rx a);
Rx copiaP(Rx a);
Rx copiaMenosP(Rx a);
int  liberaP(Rx *a);

int main(int argc, char *argv[]) {
	FILE *ent, *sal;
  char *noment="poliR.txt", *nomsal="resultado.txt";
  Rx A, B, C, R={c:NULL, g:-1};
  int m, n;
  double  r=0.0, a=0.0, b=0.0;
  
  printf("Por leer el archivo %s.\n", noment);
  ent=fopen(noment,"rt");
  if(ent==NULL){
    int mi_error=errno; 
	printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	mi_error, strerror(mi_error));
    return -1;
  }
  printf("Por leer el polinomio A(x).\n");
   A=leeP(ent);

  printf("Por leer el polinomio B(x).\n");
  B=leeP(ent);
  /* Suma */
  printf("Por calcular A(x)+B(x).\n");
  C=suma(A,B);
  
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  sal=fopen(nomsal, "wt");
  if (sal==NULL){
    int mi_error=errno; 
    printf("Hubo un error en la escritura del archivo: %d <<%s>>\nPor finalizar la ejecucion del programa.\n", 
      mi_error, strerror(mi_error));

    fclose(ent);
    return -1;
  }
  fprintf(sal, "A(x)=");
  escP(sal, A);
  fprintf(sal, "B(x)=");
  escP(sal, B);
  fprintf(sal, "A(x)+B(x)=");
  escP(sal, C);
  liberaP(&C);
  
  /* Resta */
  printf("Por calcular A(x)-B(x).\n");
  C=rest(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)-B(x)=");
  escP(sal, C);
  liberaP(&C);
  
  /* Producto */
  printf("Por calcular A(x)B(x).\n");
  C=mult(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)*B(x)=");
  escP(sal, C);
  liberaP(&C);
    
 /* Cociente y residuo */
  printf("Por calcular A(x)/B(x) y R(x).\n");
  C=divR(A,B,&R);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)/B(x)=");
  escP(sal, C);
  fprintf(sal, "Residuo=");
  escP(sal, R);
  liberaP(&C);
  liberaP(&R);
  
  /* MCD */
  printf("Por calcular mcd(A(x),B(x)).\n");
  C=mcdR(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "mcd(A(x),B(x))=");
  escP(sal, C);
  liberaP(&C);
  
  /* Derivada */
  printf("Por calcular A'(x).\n");
  C=derivaR(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A'(x)=");
  escP(sal, C);
  liberaP(&C);
  
  /* Integral indefinida*/
  printf("Por calcular la integral indefinida de A(x)\n");
  C=integraR(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "Integral indefinida de A(x)=");
  escP(sal, C);
  liberaP(&C);
  
  /* Evaluar */
  printf("Por evaluar A(x).\n");
  a=leeR(ent);
  r=evaluaR(A, a);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"A(%lg) es: %lg\n",a,r);
  
  /* Integral definida*/
  printf("Por calcular la integral definida de A(x).\n");
  a=leeR(ent);
  b=leeR(ent);
  r=integraDefR(A,a,b);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"El polinomio A(x) integrado de %lg a %lg es: %lg\n",a,b,r);

  fclose(sal);
  fclose(ent);
  system("PAUSE"); 
	return 0;
}

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
