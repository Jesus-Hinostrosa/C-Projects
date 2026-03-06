#include<stdio.h>
#include<stdlib.h>
#include<errno.h> 
#include<string.h> 

typedef struct _Zp_{
	int p,n;
}Zp;

typedef struct _MatZp_{
  int m, n;
  Zp **ent;
}MatZp;

Zp leeZp(FILE *f,int p);
int escZp(FILE *f, Zp a);
Zp simpZp(Zp a);
Zp sumaZp(Zp a,Zp b);
Zp restaZp(Zp a,Zp b);
Zp prodZp(Zp a,Zp b);

MatZp iniMatZp(int m, int n, int p);
MatZp sumaMatZp(MatZp A, MatZp B, int p);
MatZp restaMatZp(MatZp A, MatZp B, int p);
MatZp multMatZp(MatZp A, MatZp B, int p);
MatZp leeMZp(FILE *f,int p);
int escMatZp(FILE *f, MatZp A);
int LiberaMZp(MatZp *A);

int main(int argc, char argv[])
{
  FILE *ent, *sal;
  char *noment="matZp.txt", *nomsal="resultadoZp.txt";
  MatZp A, B, C;
  int m, n, p;

  printf("Por leer el archivo %s.\n", noment);
  ent=fopen(noment, "rt");
  if(ent==NULL){
    int mi_error=errno; 
    printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	   mi_error, strerror(mi_error));
    return -1;
  }
  
  printf("Por leer un primo:");
  fscanf(ent,"%d",&p);
  
  printf("Por leer matriz A.\n");
 A=leeMZp(ent,p);
  
  printf("Por leer matriz B.\n");
  B=leeMZp(ent,p);
  
  /* Suma */
  printf("Por calcular A+B.\n");
  if (A.m!=B.m || A.n!=B.n ){
    printf("No se puede efectuar la suma de matrices\n");
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=sumaMatZp(A,B,p);
  
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
  escMatZp(sal, C);
  LiberaMZp(&C);
  
  /* Resta */
  printf("Por calcular A-B.\n");
  if (A.m!=B.m || A.n!=B.n ){
    printf("No se puede efectuar la suma de matrices\n");
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=restaMatZp(A,B,p);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "La resta");
  escMatZp(sal, C);
  LiberaMZp(&C);
  
  /* Producto */
  printf("Por calcular AB.\n");
  if (A.n!=B.m){
    printf("No se puede efectuar la multiplicacion de matrices\n");
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=multMatZp(A,B,p);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "El producto");
  escMatZp(sal, C);
  LiberaMZp(&C);
  
  fclose(sal);
  fclose(ent); 
  system("PAUSE");
  return 0;
}

Zp leeZp(FILE *f, int p)
{
	Zp a;
	a.p=p;
	
	fscanf(f, "%d",&a.n);
	a=simpZp(a);
	
	return a;
}
int escZp(FILE *f, Zp a)
{char buferTemporal[128];
  int l;

  sprintf(buferTemporal, "%d", a.n);
  l = strlen(buferTemporal);
  fprintf(f,"%3s", buferTemporal);
  return 0;
}
Zp simpZp(Zp a){
	a.n=((a.n%a.p)+a.p)%a.p;
	return a;
}

Zp sumaZp(Zp a,Zp b){
	Zp r;
	
	r.p=a.p;
	r.n=a.n+b.n;
	return simpZp(r);	
}
Zp restaZp(Zp a,Zp b){
	Zp r;
	r.p=a.p;
	r.n=a.n-b.n;
	r=simpZp(r);
	return r;
}
Zp prodZp(Zp a,Zp b){
	Zp r;
	r.p=a.p;
	r.n=a.n*b.n;
	r=simpZp(r);
	return r;
}

MatZp iniMatZp(int m, int n, int p)
{
  MatZp ret={m:m, n:n, ent:NULL};
  Zp ceroZp={p:p, n:0};
  int i, j;

  ret.ent = (Zp **)malloc(m*sizeof(Zp*));
  if(ret.ent==NULL) return ret;
  for(i=0; i<m; i++){
    ret.ent[i]=(Zp*)malloc(n*sizeof(Zp));
    if(ret.ent[i]==NULL){
      while(--i>=0) free(ret.ent[i]);
      free(ret.ent);
      ret.ent=NULL;
      break;
    }
    for (j=0; j<n; j++) ret.ent[i][j]=ceroZp;
  }

  return ret;
}
MatZp sumaMatZp(MatZp A, MatZp B, int p){
	MatZp C;
	int i,j;

	C.m=C.n=0;
	C.ent=NULL;
	
	C=iniMatZp(A.m, B.n,p);
	for(i=0;i<A.m;i++)
		for(j=0;j<A.n;j++){
			C.ent[i][j]=sumaZp(A.ent[i][j], B.ent[i][j]);
		}
	return C;
}

MatZp restaMatZp(MatZp A, MatZp B, int p){
	MatZp C;
	int i,j;

	C.m=C.n=0;
	C.ent=NULL;
	
	C=iniMatZp(A.m, B.n,p);
	for(i=0;i<A.m;i++)
		for(j=0;j<A.n;j++){
			C.ent[i][j]=restaZp(A.ent[i][j], B.ent[i][j]);
		}
	return C;
}

MatZp multMatZp(MatZp A, MatZp B, int p)
{
  MatZp ret={m:0, n:0, ent:NULL};
  int i, j, k, r;

  if (A.n!=B.m) return ret;
  r=A.n;
  ret=iniMatZp(A.m, B.n,p);
  for(i=0; i<ret.m; i++)
    for(j=0; j<ret.n; j++)
      for(k=0; k<r; k++){
      	ret.ent[i][j]=sumaZp(ret.ent[i][j], prodZp(A.ent[i][k], B.ent[k][j]));
	  }
	
  return ret;
}
MatZp leeMZp(FILE *f,int p){
int m,n,i,j;
MatZp B;

  fscanf(f, "%d%d", &m, &n);
  B = iniMatZp(m, n, p);
  for(i=0; i<m; i++)
    for(j=0; j<n; j++)
      B.ent[i][j]=leeZp(f,p);
      
return B;	
}
int escMatZp(FILE *f, MatZp A)
{
  int i, j;

  fprintf(f, " es una matriz de %d x %d igual a:\n", A.m, A.n);
  for(i=0; i<A.m; i++){
    for(j=0; j<A.n; j++)
      escZp(f,A.ent[i][j]);
    fprintf(f, "\n");
  }

  return 0;
}
int LiberaMZp(MatZp *A){
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

