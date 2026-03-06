#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "bpoliR.h"

int main(int argc, char *argv[]) {
	FILE *ent, *sal;
  char *noment="poliR.txt", *nomsal="resultado.txt";
  Rx A, B, C, R={c:NULL, g:-1};
  int m, n;
  double  r=0.0, a=0.0, b=0.0;
  
  printf("Por leer el archivo %s.\n", noment);
  ent=fopen(noment,"rt");
  if(ent==NULL){
    int mi_error=errno; 
	printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	mi_error, strerror(mi_error));
    return -1;
  }
  printf("Por leer el polinomio A(x).\n");
   A=leeP(ent);

  printf("Por leer el polinomio B(x).\n");
  B=leeP(ent);
  /* Suma */
  printf("Por calcular A(x)+B(x).\n");
  C=suma(A,B);
  
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  sal=fopen(nomsal, "wt");
  if (sal==NULL){
    int mi_error=errno; 
    printf("Hubo un error en la escritura del archivo: %d <<%s>>\nPor finalizar la ejecucion del programa.\n", 
      mi_error, strerror(mi_error));

    fclose(ent);
    return -1;
  }
  fprintf(sal, "A(x)+B(x)=");
  escP(sal, C);
  liberaP(&C);
  
  /* Resta */
  printf("Por calcular A(x)-B(x).\n");
  C=rest(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)-B(x)=");
  escP(sal, C);
  liberaP(&C);
  
  /* Producto */
  printf("Por calcular A(x)B(x).\n");
  C=mult(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)*B(x)=");
  escP(sal, C);
  liberaP(&C);
    
 /* Cociente y residuo */
  printf("Por calcular A(x)/B(x) y R(x).\n");
  C=divR(A,B,&R);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)/B(x)=");
  escP(sal, C);
  fprintf(sal, "Residuo=");
  escP(sal, R);
  liberaP(&C);
  liberaP(&R);
  
  /* MCD */
  printf("Por calcular mcd(A(x),B(x)).\n");
  C=mcdR(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "mcd(A(x),B(x))=");
  escP(sal, C);
  liberaP(&C);
  
  /* Derivada */
  printf("Por calcular A'(x).\n");
  C=derivaR(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A'(x)=");
  escP(sal, C);
  liberaP(&C);
  
  /* Integral indefinida*/
  printf("Por calcular la integral indefinida de A(x)\n");
  C=integraR(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "Integral indefinida de A(x)=");
  escP(sal, C);
  liberaP(&C);
  
  /* Evaluar */
  printf("Por evaluar A(x).\n");
  a=leeR(ent);
  r=evaluaR(A, a);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"A(%lg) es: %lg\n",a,r);
  
  /* Integral definida*/
  printf("Por calcular la integral definida de A(x).\n");
  a=leeR(ent);
  b=leeR(ent);
  r=integraDefR(A,a,b);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"El polinomio A(x) integrado de %lg a %lg es: %lg\n",a,b,r);
  liberaP(&A);
  liberaP(&B);
  
  fclose(sal);
  fclose(ent);
  system("PAUSE"); 
	return 0;
}
