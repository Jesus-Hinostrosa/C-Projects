#include<stdio.h>
#include<stdlib.h>
#include<errno.h> 
#include<string.h> 

#include "bComp.h"
#include "bMatC.h"


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

