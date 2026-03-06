#include<stdio.h>
#include<stdlib.h>
#include<errno.h> 
#include<string.h>

#include "bmatR.h"

double leeR(FILE *f)
{
  double ret;

  fscanf(f, "%lg", &ret);

  return ret;
}

int escR(FILE *f,double a){

  fprintf(f,"%lg ", a);
  return 0;
}


MatR iniMatR(int m, int n)
{
  MatR ret={m:m, n:n, ent:NULL};
  int i, j;

  ret.ent = (double **)malloc(m*sizeof(double*));
  if(ret.ent==NULL) return ret;
  for(i=0; i<m; i++){
    ret.ent[i]=(double*)malloc(n*sizeof(double));
    if(ret.ent[i]==NULL){
      while(--i>=0) free(ret.ent[i]);
      free(ret.ent);
      ret.ent=NULL;
      break;
    }
		for (j=0; j<n; j++) ret.ent[i][j]=0.0;
  }

  return ret;
}
MatR sumaMatR(MatR A, MatR B){
	MatR C;
	int i,j;

	C.m=C.n=0;
	C.ent=NULL;
	
	C=iniMatR(A.m, B.n);
	for(i=0;i<A.m;i++)
		for(j=0;j<A.n;j++){
			C.ent[i][j]=A.ent[i][j]+B.ent[i][j];
		}
	return C;
}

MatR restaMatR(MatR A, MatR B){
	MatR C;
	int i,j;

	C.m=C.n=0;
	C.ent=NULL;
	
	C=iniMatR(A.m, B.n);
	for(i=0;i<A.m;i++)
		for(j=0;j<A.n;j++){
			C.ent[i][j]=A.ent[i][j]-B.ent[i][j];
		}
	return C;
}

MatR multMatR(MatR A, MatR B)
{
  MatR ret={m:0, n:0, ent:NULL};
  int i, j, k, p;

  if (A.n!=B.m) return ret;
  p=A.n;
  ret=iniMatR(A.m, B.n);
  for(i=0; i<ret.m; i++)
    for(j=0; j<ret.n; j++)
      for(k=0; k<p; k++)
	ret.ent[i][j]+=A.ent[i][k]*B.ent[k][j];

  return ret;
}
MatR leeMR(FILE *f){
	int m,n,i,j;
	MatR B;

  fscanf(f, "%d%d", &m, &n);
  B = iniMatR(m, n);
  for(i=0; i<m; i++)
    for(j=0; j<n; j++)
      B.ent[i][j]=leeR(f);
      
   for(i=0; i<m; i++)
    for(j=0; j<n; j++)
      printf("%lg",B.ent[i][j]);
      
return B;	
}
int escMatR(FILE *f, MatR A)
{
  int i, j;

  fprintf(f, " es una matriz de %d x %d igual a:\n", A.m, A.n);
  for(i=0; i<A.m; i++){
    for(j=0; j<A.n; j++)
      escR(f,A.ent[i][j]);
    fprintf(f, "\n");
  }
fprintf(f, "\n");
  return 0;
}

int LiberaMR(MatR *A){
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

