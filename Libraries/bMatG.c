#include <stdio.h>    
#include <stdlib.h>  
#include <time.h>     
#include <string.h>  

#include "bGauss.h"
#include "bMatG.h"


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
