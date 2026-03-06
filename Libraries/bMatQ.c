#include<stdio.h>
#include<stdlib.h>
#include<errno.h> 
#include<string.h> 

#include "bRac.h"
#include "bMatQ.h"

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
