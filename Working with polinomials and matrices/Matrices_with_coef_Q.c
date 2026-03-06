#include<stdio.h>
#include<stdlib.h>
#include<errno.h> 
#include<string.h> 

typedef struct _Q_{
  int p, q;
}Q;

typedef struct _MatQ_{
  int m, n;
  Q **ent;
}MatQ;

Q leeQ(FILE *f);
int escQ(FILE *f, Q a); 
int mcd(int a, int b);
int esCeroQ(Q a); 
int igualQ(Q a, Q b);  
Q simplificaQ(Q a);    
Q creaQ(int num, int den);
Q sumaQ(Q a, Q b);
Q restaQ(Q a, Q b);
Q prodQ(Q a, Q b);

MatQ iniMatQ(int m, int n);
MatQ sumaMatQ(MatQ A, MatQ B);
MatQ restaMatQ(MatQ A, MatQ B);
MatQ multMatQ(MatQ A, MatQ B);
MatQ leeMQ(FILE *f);
int escMatQ(FILE *f, MatQ A);
int LiberaMQ(MatQ *A);

int main(int argc, char argv[])
{
  FILE *ent, *sal;
  char *noment="matQ.txt", *nomsal="resultado.txt";
  MatQ A, B, C;
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
 A=leeMQ(ent);
  
  printf("Por leer matriz B.\n");
  B=leeMQ(ent);
  
  /* Suma */
  printf("Por calcular A+B.\n");
  if (A.m!=B.m || A.n!=B.n ){
    printf("No se puede efectuar la suma de matrices\n");
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=sumaMatQ(A,B);
  
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
  escMatQ(sal, C);
  LiberaMQ(&C);
  
  /* Resta */
  printf("Por calcular A-B.\n");
  if (A.m!=B.m || A.n!=B.n ){
    printf("No se puede efectuar la suma de matrices\n");
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=restaMatQ(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "La resta");
  escMatQ(sal, C);
  LiberaMQ(&C);
   
  /* Producto */
  printf("Por calcular AB.\n");
  if (A.n!=B.m){
    printf("No se puede efectuar la multiplicacion de matrices (%d!=%d)\n", A.n, B.m);
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=multMatQ(A, B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "El producto");
  escMatQ(sal, C);
  LiberaMQ(&C);

  
  fclose(ent); 
  fclose(sal);

  return 0;
}


int mcd(int a, int b)
{
  int r;

  if (a<0) a=-a;
  if (b<0) b=-b;
  if (b==0) return a;
  while((r=a%b)!=0){
    a=b;
    b=r;
  }

  return b;
}

Q simplificaQ(Q r)
{
  Q ret={p:r.p, q:r.q};
  int d=mcd(r.p, r.q);

  ret.p/=d;
  ret.q/=d;
  if(ret.q<0){
    ret.p=-ret.p;
    ret.q=-ret.q;
  }

  return ret;
}

Q leeQ(FILE *f)
{
  Q ret;

  fscanf(f, "%d%d", &ret.p, &ret.q);

  return simplificaQ(ret);
}

int escQ(FILE *f,Q a){
  char buferTemporal[128];
  int l;

  sprintf(buferTemporal, "%d", a.p);
  l = strlen(buferTemporal);
  if (a.q!= 1) sprintf(buferTemporal+l, "/%d", a.q);
  fprintf(f,"%7s", buferTemporal);
  return 0;
}
Q sumaQ(Q a, Q b)
{
  Q ret={p:a.p*b.q+a.q*b.p, q:a.q*b.q};

  return simplificaQ(ret);
}

Q restaQ(Q a, Q b){
	Q r;           

  r.p = a.p*b.q - a.q*b.p;
  r.q = a.q*b.q;
  r=simplificaQ(r);

  return r;
}

Q prodQ(Q a, Q b)
{
  Q ret={p:a.p*b.p, q:a.q*b.q};

  return simplificaQ(ret);
}
// funciones MatQ //
MatQ iniMatQ(int m, int n)
{
  MatQ ret={m:m, n:n, ent:NULL};
  Q ceroQ={p:0, q:1};
  int i, j;

  ret.ent = (Q **)malloc(m*sizeof(Q*));
  if(ret.ent==NULL) return ret;
  for(i=0; i<m; i++){
    ret.ent[i]=(Q*)malloc(n*sizeof(Q));
    if(ret.ent[i]==NULL){
      while(--i>=0) free(ret.ent[i]);
      free(ret.ent);
      ret.ent=NULL;
      break;
    }
    for (j=0; j<n; j++) ret.ent[i][j]=ceroQ;
  }

  return ret;
}

MatQ sumaMatQ(MatQ A, MatQ B){
	MatQ C;
	int i,j;

	C.m=C.n=0;
	C.ent=NULL;
	
	C=iniMatQ(A.m, B.n);
	for(i=0;i<A.m;i++)
		for(j=0;j<A.n;j++){
			C.ent[i][j]=sumaQ(A.ent[i][j], B.ent[i][j]);
		}
	return C;
}

MatQ restaMatQ(MatQ A, MatQ B){
	MatQ C;
	int i,j;

	C.m=C.n=0;
	C.ent=NULL;
	
	C=iniMatQ(A.m, B.n);
	for(i=0;i<A.m;i++)
		for(j=0;j<A.n;j++){
			C.ent[i][j]=restaQ(A.ent[i][j], B.ent[i][j]);
		}
	return C;
}

MatQ multMatQ(MatQ A, MatQ B)
{
  MatQ ret={m:0, n:0, ent:NULL};
  int i, j, k, p;

  if (A.n!=B.m) return ret;
  p=A.n;
  ret=iniMatQ(A.m, B.n);
  for(i=0; i<ret.m; i++)
    for(j=0; j<ret.n; j++)
      for(k=0; k<p; k++)
	ret.ent[i][j]=sumaQ(ret.ent[i][j], prodQ(A.ent[i][k], B.ent[k][j]));

  return ret;
}
MatQ leeMQ(FILE *f){
int m,n,i,j;
MatQ B;

  fscanf(f, "%d%d", &m, &n);
  B = iniMatQ(m, n);
  for(i=0; i<m; i++)
    for(j=0; j<n; j++)
      B.ent[i][j]=leeQ(f);
      
return B;	
}
int escMatQ(FILE *f, MatQ A)
{
  int i, j;

  fprintf(f, " es una matriz de %d x %d igual a:\n", A.m, A.n);
  for(i=0; i<A.m; i++){
    for(j=0; j<A.n; j++)
      escQ(f,A.ent[i][j]);
    fprintf(f, "\n");
  }

  return 0;
}

int LiberaMQ(MatQ *A){
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


