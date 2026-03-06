#include<stdio.h>
#include<stdlib.h>
#include<errno.h> 
#include<string.h> 

typedef struct _Cuater_{
double a,b,c,d;	
}H;

typedef struct _MATRIZ_{
	int m,n;
	H **ent;
}MatH;

H leeH(FILE *f);
int escH(FILE *f,H x);
H sumaH(H x, H y);
H restaH(H x, H y);
H multH(H x, H y);

MatH iniMatH(int m, int n);
MatH sumaMatH(MatH A, MatH B);
MatH restaMatH(MatH A, MatH B);
MatH multMatH(MatH A, MatH B);
MatH leeMH(FILE *f);
int escMatH(FILE *f, MatH A);
int LiberaMH(MatH *A);


int main(int argc, char *argv[]) {
	FILE *ent, *sal;
  char *noment="matH.txt", *nomsal="resultado.txt";
  MatH A, B, C;
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
  A=leeMH(ent);
  
  printf("Por leer matriz B.\n");
  B=leeMH(ent);
   
  printf("Por calcular A+B.\n");
  if (A.m!=B.m || A.n!=B.n ){
    printf("No se puede efectuar la suma de matrices\n");
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=sumaMatH(A,B);
  
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
  escMatH(sal, C);
  LiberaMH(&C);
  
   /* Resta */
  printf("Por calcular A-B.\n");
  if (A.m!=B.m || A.n!=B.n ){
    printf("No se puede efectuar la suma de matrices\n");
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=restaMatH(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "La resta");
  escMatH(sal, C);
  LiberaMH(&C);
   
  /* Producto */
  printf("Por calcular AB.\n");
  if (A.n!=B.m){
    printf("No se puede efectuar la multiplicacion de matrices (%d!=%d)\n", A.n, B.m);
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=multMatH(A, B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "El producto");
  escMatH(sal, C);
  LiberaMH(&C); 
  		
  fclose(sal);  
  fclose(ent);
	return 0;
}


H leeH(FILE *f){
	H ret;

  fscanf(f,"%lg%lg%lg%lg", &ret.a, &ret.b, &ret.c, &ret.d);
  return ret;
}
int escH(FILE *f,H x){;
	
	if(x.a==0.0&&x.b==0.0&&x.c==0.0&&x.d==0.0) fprintf(f,"0");
	else{
        if(x.a==0.0) fprintf(f,"   ");
	    else fprintf(f,"%3lg",x.a);
        if(x.b==0.0) fprintf(f,"   ");
        else {
    	    if(x.b==1) fprintf(f," +i");
    	    else{
    	    	if(x.b==-1) fprintf(f," -i");
    	        else fprintf(f,"%+2lgi",x.b);
			  }
	        }
        if(x.c==0.0) fprintf(f,"   ");
	    else {
    	    if(x.c==1) fprintf(f," +j");
    	    else{
    	        if(x.c==-1) fprintf(f," -j");
    	        else fprintf(f,"%+2lgj",x.c);
    	        }
	        }
        if(x.d==0.0) fprintf(f,"   ");
        else{
    	     if(x.d==1) fprintf(f," +k");
    	     else{
			    if(x.d==-1) fprintf(f," -k");
    	        else fprintf(f,"%+2lgk",x.d);
			  }
    	     
	        }
   }
	
   fprintf(f,"   ");
	
   return 0;
}
H sumaH(H x, H y){
	H r;
 
 	r.a=x.a+y.a;
	r.b=x.b+y.b;
	r.c=x.c+y.c;
	r.d=x.d+y.d;

 return r;	
}

H restaH(H x, H y){
	H r;
	
	r.a=x.a-y.a;
	r.b=x.b-y.b;
 	r.c=x.c-y.c;
 	r.d=x.d-y.d;
 
 return r;	
}
H multH(H x, H y){
	H r;
 
 r.a=x.a*y.a-x.b*y.b-x.c*y.c-x.d*y.d;
 r.b=x.a*y.b+x.b*y.a+x.c*y.d-x.d*y.c;
 r.c=x.a*y.c-x.b*y.d+x.c*y.a+x.d*y.b;
 r.d=x.a*y.d+x.b*y.c-x.c*y.b+x.d*y.a;
 
 return r;
}

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
