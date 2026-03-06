#include<stdio.h>
#include<stdlib.h>
#include<errno.h> 
#include<string.h> 

typedef struct _C_{
  double r,i;
}C;

typedef struct _MatC_{
  int m, n;
  C **ent;
}MatC;

C leeC(FILE *f);
int escC(FILE *f,C a);
C sumaC(C a, C b);
C restaC(C a, C b);
C multC(C a, C b);

MatC iniMatC(int m, int n);
MatC sumaMatC(MatC A, MatC B);
MatC restaMatC(MatC A, MatC B);
MatC multMatC(MatC A, MatC B);
MatC leeMC(FILE *f);
int escMatC(FILE *f, MatC A);
int LiberaMC(MatC *A);


int main(int argc, char *argv[]) {
  FILE *ent, *sal;
  char *noment="matC.txt", *nomsal="resultado.txt";
  MatC A, B, C;
  int m, n, i, j;

  printf("Por leer el archivo %s.\n", noment);
  ent=fopen(noment, "rt");
  if(ent==NULL){
    int mi_error=errno; 
    printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	   mi_error, strerror(mi_error));
    return -1;
  }
  printf("Por leer matriz A.\n");
  A=leeMC(ent);
  
  printf("Por leer matriz B.\n");
  B=leeMC(ent);
  
  /* Suma */
  printf("Por calcular A+B.\n");
  if (A.m!=B.m || A.n!=B.n ){
    printf("No se puede efectuar la suma de matrices\n");
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=sumaMatC(A,B);
  
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  sal=fopen(nomsal, "wt");
  if (sal==NULL){
    int mi_error=errno; 
    printf("Hubo un error en la escritura del archivo: %d <<%s>>\nPor finalizar la ejecucion del programa.\n", 
      mi_error, strerror(mi_error));

    fclose(ent);
    return -1;
  }
  fprintf(sal, "La suma");
  escMatC(sal, C);
  LiberaMC(&C);
  
   /* Resta */
  printf("Por calcular A-B.\n");
  if (A.m!=B.m || A.n!=B.n ){
    printf("No se puede efectuar la suma de matrices\n");
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=restaMatC(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "La resta");
  escMatC(sal, C);
  LiberaMC(&C);
   
  /* Producto */
  printf("Por calcular AB.\n");
  if (A.n!=B.m){
    printf("No se puede efectuar la multiplicacion de matrices (%d!=%d)\n", A.n, B.m);
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=multMatC(A, B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "El producto");
  escMatC(sal, C);
  LiberaMC(&C);
  
  
  fclose(sal);
  fclose(ent); 
	return 0;
}

C leeC(FILE *f){
  C ret;

  fscanf(f, "%lg%lg", &ret.r, &ret.i);
  return ret;
}

int escC(FILE *f,C a){
  char buferTemporal[128];
  int l;

  if(a.r==0.0){
  		if(a.i==1.0) sprintf(buferTemporal,"i");
		else{
			if(a.i==-1.0) sprintf(buferTemporal,"-i");
			else sprintf(buferTemporal, "%lgi",a.i);
			}
	}
  else{
  	if(a.i==0.0) sprintf(buferTemporal, "%lg",a.r);
	else{
		if(a.i==1.0) sprintf(buferTemporal,"%lg+i",a.r);
		else{
			if(a.i==-1.0) sprintf(buferTemporal,"%lg-i",a.r);
			else{
				sprintf(buferTemporal,"%lg%+-lgi",a.r,a.i);
			}
		}
	}	
  }
	fprintf(f,"%9s", buferTemporal);
  return 0;
}

C sumaC(C a, C b){
	C c;

	c.r=a.r+b.r;
	c.i=a.i+b.i;
	return c;
}

C restaC(C a, C b){
	C c;

	c.r=a.r-b.r;
	c.i=a.i-b.i;
	return c;
}

C multC(C a, C b){	
	C c;
	
	c.r=a.r*b.r-a.i*b.i;
	c.i=a.r*b.i+b.r*a.i;
	return c;
}

MatC iniMatC(int m, int n)
{
  MatC ret={m:m, n:n, ent:NULL};
  C ceroC={r:0, i:0};
  int i, j;

  ret.ent = (C **)malloc(m*sizeof(C*));
  if(ret.ent==NULL) return ret;
  for(i=0; i<m; i++){
    ret.ent[i]=(C*)malloc(n*sizeof(C));
    if(ret.ent[i]==NULL){
      while(--i>=0) free(ret.ent[i]);
      free(ret.ent);
      ret.ent=NULL;
      break;
    }
    for (j=0; j<n; j++) ret.ent[i][j]=ceroC;
  }

  return ret;
}

MatC sumaMatC(MatC A, MatC B){
	MatC C;
	int i,j;

	C.m=C.n=0;
	C.ent=NULL;
	
	C=iniMatC(A.m, B.n);
	for(i=0;i<A.m;i++)
		for(j=0;j<A.n;j++){
			C.ent[i][j]=sumaC(A.ent[i][j], B.ent[i][j]);
		}
	return C;
}

MatC restaMatC(MatC A, MatC B){
	MatC C;
	int i,j;

	C.m=C.n=0;
	C.ent=NULL;
	
	C=iniMatC(A.m, B.n);
	for(i=0;i<A.m;i++)
		for(j=0;j<A.n;j++){
			C.ent[i][j]=restaC(A.ent[i][j], B.ent[i][j]);
		}
	return C;
}

MatC multMatC(MatC A, MatC B){
  MatC ret={m:0, n:0, ent:NULL};
  int i, j, k, p;

  if (A.n!=B.m) return ret;
  p=A.n;
  ret=iniMatC(A.m, B.n);
  for(i=0; i<ret.m; i++)
    for(j=0; j<ret.n; j++)
      for(k=0; k<p; k++)
	ret.ent[i][j]=sumaC(ret.ent[i][j], multC(A.ent[i][k], B.ent[k][j]));

  return ret;
}
MatC leeMC(FILE *f){
int m,n,i,j;
MatC B;

  fscanf(f, "%d%d", &m, &n);
  B = iniMatC(m, n);
  for(i=0; i<m; i++)
    for(j=0; j<n; j++)
      B.ent[i][j]=leeC(f);
      
return B;	
}
int escMatC(FILE *f, MatC A)
{
  int i, j;

  fprintf(f, " es una matriz de %d x %d igual a:\n", A.m, A.n);
  for(i=0; i<A.m; i++){
    for(j=0; j<A.n; j++)
      escC(f,A.ent[i][j]);
    fprintf(f, "\n");
  }

  return 0;
}

int LiberaMC(MatC *A){
	int i;
	
	for(i=0;i<A->m;i++){
		free(A->ent[i]);
		A->ent[i]=NULL;
	}
	free(A->ent);
	A->ent=NULL;
	A->m=A->n=0;
	return 0;
}

