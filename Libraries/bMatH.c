#include<stdio.h>
#include<stdlib.h>
#include<errno.h> 
#include<string.h> 

#include "bH.h"
#include "bMatH.h"


MatH iniMatH(int m, int n){
  MatH ret={m:m, n:n, ent:NULL};
  H ceroH={a:0, b:0, c:0, d:0};
  int i, j;

  ret.ent = (H **)malloc(m*sizeof(H*));
  if(ret.ent==NULL) return ret;
  for(i=0; i<m; i++){
    ret.ent[i]=(H*)malloc(n*sizeof(H));
    if(ret.ent[i]==NULL){
      while(--i>=0) free(ret.ent[i]);
      free(ret.ent);
      ret.ent=NULL;
      break;
    }
    for (j=0; j<n; j++) ret.ent[i][j]=ceroH;
  }

  return ret;
}
MatH sumaMatH(MatH A, MatH B){
	MatH C;
	int i,j;

	C.m=C.n=0;
	C.ent=NULL;
	
	C=iniMatH(A.m, B.n);
	for(i=0;i<A.m;i++)
		for(j=0;j<A.n;j++){
			C.ent[i][j]=sumaH(A.ent[i][j], B.ent[i][j]);
		}
	return C;
}
MatH restaMatH(MatH A, MatH B){
	MatH C;
	int i,j;

	C.m=C.n=0;
	C.ent=NULL;
	
	C=iniMatH(A.m, B.n);
	for(i=0;i<A.m;i++)
		for(j=0;j<A.n;j++){
			C.ent[i][j]=restaH(A.ent[i][j], B.ent[i][j]);
		}
	return C;
}
MatH multMatH(MatH A, MatH B){
  MatH ret={m:0, n:0, ent:NULL};
  int i, j, k, p;

  if (A.n!=B.m) return ret;
  p=A.n;
  ret=iniMatH(A.m, B.n);
  for(i=0; i<ret.m; i++)
    for(j=0; j<ret.n; j++)
      for(k=0; k<p; k++)
	ret.ent[i][j]=sumaH(ret.ent[i][j], multH(A.ent[i][k], B.ent[k][j]));

  return ret;
}
MatH leeMH(FILE *f){
	int m,n,i,j;
	MatH B;

  fscanf(f, "%d%d", &m, &n);
  B = iniMatH(m, n);
  for(i=0; i<m; i++)
    for(j=0; j<n; j++)
      B.ent[i][j]=leeH(f);
      

return B;	
}
int escMatH(FILE *f, MatH A){
	int i, j;

  fprintf(f, " es una matriz de %d x %d igual a:\n", A.m, A.n);
  for(i=0; i<A.m; i++){
    for(j=0; j<A.n; j++)
      escH(f,A.ent[i][j]);
    fprintf(f, "\n");
  }

  return 0;
}
int LiberaMH(MatH *A){
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
