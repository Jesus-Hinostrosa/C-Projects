#include <stdio.h>    
#include <stdlib.h>  
#include <time.h>     
#include <string.h>  


typedef struct _Gaussianos_{
int  r,i; 
}G;  
typedef struct _MATRIZ_{
	int m,n;
	G **ent;
}MatG;

G leeG(FILE *f);
int escG(FILE *f,G a);
G sumaG(G x, G y);
G restaG(G x, G y);
G prodG(G x, G y);

MatG iniMatG(int m, int n);
MatG sumaMatG(MatG A, MatG B);
MatG restaMatG(MatG A, MatG B);
MatG multMatG(MatG A, MatG B);
MatG leeMG(FILE *f);
int escMatG(FILE *f, MatG A);
int LiberaMG(MatG *A);

int main(int argc, char *argv[]) {
	FILE *ent, *sal;
  char *noment="matG.txt", *nomsal="resultado.txt";
  MatG A, B, C;
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
  A=leeMG(ent);
  
  printf("Por leer matriz B.\n");
  B=leeMG(ent);
  
  /* Suma */
  printf("Por calcular A+B.\n");
  if (A.m!=B.m || A.n!=B.n ){
    printf("No se puede efectuar la suma de matrices\n");
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=sumaMatG(A,B);
  
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
  escMatG(sal, C);
  LiberaMG(&C);
  
  /* Resta */
  printf("Por calcular A-B.\n");
  if (A.m!=B.m || A.n!=B.n ){
    printf("No se puede efectuar la suma de matrices\n");
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=restaMatG(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "La resta");
  escMatG(sal, C);
  LiberaMG(&C);
   
  /* Producto */
  printf("Por calcular AB.\n");
  if (A.n!=B.m){
    printf("No se puede efectuar la multiplicacion de matrices (%d!=%d)\n", A.n, B.m);
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=multMatG(A, B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "El producto");
  escMatG(sal, C);
  LiberaMG(&C);
  LiberaMG(&A);
  LiberaMG(&B);
  
    fclose(sal);
	fclose(ent);	
	system("PAUSE");
  return 0;
}

G leeG(FILE *f){
	G ret;

  fscanf(f, "%d%d", &ret.r, &ret.i);
  return ret;
}
int escG(FILE *f,G a){
if(a.r==0 && a.i==0) fprintf(f,"  0");
	else{
        if(a.r==0) fprintf(f,"   ");
	    else fprintf(f,"%3d",a.r);
        if(a.i==0) fprintf(f,"   ");
        else {
    	    if(a.i==1) fprintf(f," +i");
    	    else{
    	    	if(a.i==-1) fprintf(f," -i");
    	        else fprintf(f,"%+3di",a.i);
			  }
	        }
   }
	
   fprintf(f,"   ");
  return 0;
}
G sumaG(G x, G y){
	G z;

	z.r=x.r+y.r;
	z.i=x.i+y.i;
	return z;
}
G restaG(G x, G y){
	G z;

	z.r=x.r-y.r;
	z.i=x.i-y.i;
	return z;
}
G prodG(G x, G y){
	G z;
	
	z.r=x.r*y.r-x.i*y.i;
	z.i=x.r*y.i+y.r*x.i;
	return z;
}

MatG iniMatG(int m, int n){
	MatG ret={m:m, n:n, ent:NULL};
  G ceroG={r:0, i:0};
  int i, j;

  ret.ent = (G **)malloc(m*sizeof(G*));
  if(ret.ent==NULL) return ret;
  for(i=0; i<m; i++){
    ret.ent[i]=(G*)malloc(n*sizeof(G));
    if(ret.ent[i]==NULL){
      while(--i>=0) free(ret.ent[i]);
      free(ret.ent);
      ret.ent=NULL;
      break;
    }
    for (j=0; j<n; j++) ret.ent[i][j]=ceroG;
  }

  return ret;
}
MatG sumaMatG(MatG A, MatG B){
	MatG C;
	int i,j;

	C.m=C.n=0;
	C.ent=NULL;
	
	C=iniMatG(A.m, B.n);
	for(i=0;i<A.m;i++)
		for(j=0;j<A.n;j++){
			C.ent[i][j]=sumaG(A.ent[i][j], B.ent[i][j]);
		}
	return C;
}
MatG restaMatG(MatG A, MatG B){
	MatG C;
	int i,j;

	C.m=C.n=0;
	C.ent=NULL;
	
	C=iniMatG(A.m, B.n);
	for(i=0;i<A.m;i++)
		for(j=0;j<A.n;j++){
			C.ent[i][j]=restaG(A.ent[i][j], B.ent[i][j]);
		}
	return C;
}
MatG multMatG(MatG A, MatG B){
	MatG ret={m:0, n:0, ent:NULL};
  int i, j, k, p;

  if (A.n!=B.m) return ret;
  p=A.n;
  ret=iniMatG(A.m, B.n);
  for(i=0; i<ret.m; i++)
    for(j=0; j<ret.n; j++)
      for(k=0; k<p; k++)
	ret.ent[i][j]=sumaG(ret.ent[i][j], prodG(A.ent[i][k], B.ent[k][j]));

  return ret;
}
MatG leeMG(FILE *f){
	int m,n,i,j;
	MatG B;

  fscanf(f, "%d%d", &m, &n);
  B = iniMatG(m, n);
  for(i=0; i<m; i++)
    for(j=0; j<n; j++)
      B.ent[i][j]=leeG(f);
      
return B;	
}
int escMatG(FILE *f, MatG A){
	int i, j;

  fprintf(f, " es una matriz de %d x %d igual a:\n", A.m, A.n);
  for(i=0; i<A.m; i++){
    for(j=0; j<A.n; j++)
      escG(f,A.ent[i][j]);
    fprintf(f, "\n");
  }

  return 0;
}
int LiberaMG(MatG *A){
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
