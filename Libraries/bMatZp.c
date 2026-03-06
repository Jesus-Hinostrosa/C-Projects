#include<stdio.h>
#include<stdlib.h>
#include<errno.h> 
#include<string.h> 

#include "bZp.h"
#include "bMatZp.h"

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

