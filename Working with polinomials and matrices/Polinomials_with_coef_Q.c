#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> 
#include<string.h> 

#include "bRaq.h"
#include "bpoliQ.h"

int main(int argc, char *argv[]) {
	FILE *ent, *sal;
  char *noment="poliQ.txt", *nomsal="resultado.txt";
  Qx A, B, C, R={c:NULL, g:-1};
  int m, n, i;
  Q  r={p:0,q:1}, a={p:0,q:1}, b={p:0,q:1};
  
  printf("Por leer el archivo %s.\n", noment);
  ent=fopen(noment,"rt");
  if(ent==NULL){
    int mi_error=errno; 
	printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	mi_error, strerror(mi_error));
    return -1;
  }
  printf("Por leer el polinomio A(x).\n");
   A=leeQx(ent);

  printf("Por leer el polinomio B(x).\n");
  B=leeQx(ent);
  
  /* Suma */
  printf("Por calcular A(x)+B(x).\n");
  C=sumaQx(A,B);
  
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
  escQx(sal, C);
  liberaQx(&C);
  
  /* Resta */
  printf("Por calcular A(x)-B(x).\n");
  C=restQx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)-B(x)=");
  escQx(sal, C);
  liberaQx(&C);
  
  /* Producto */
  printf("Por calcular A(x)B(x).\n");
  C=multQx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)*B(x)=");
  escQx(sal, C);
  liberaQx(&C);
  
  /* Cociente y residuo */
  printf("Por calcular A(x)/B(x) y R(x).\n");
  C=divQx(A,B,&R);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)/B(x)=");
  escQx(sal, C);
  fprintf(sal, "Residuo=");
  escQx(sal, R);
  liberaQx(&C);
  liberaQx(&R);
  
  /* MCD */
  printf("Por calcular mcd(A(x),B(x)).\n");
  C=mcdQx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "mcd(A(x),B(x))=");
  escQx(sal, C);
  liberaQx(&C); 
  
  /* Derivada */
  printf("Por calcular A'(x).\n");
  C=derivaQx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A'(x)=");
  escQx(sal, C);
  liberaQx(&C);
  
  /* Integral indefinida*/
  printf("Por calcular la integral indefinida de A(x)\n");
  C=integraQx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "Integral indefinida de A(x)=");
  escQx(sal, C);
  liberaQx(&C);
  
  /* Evaluar */
  printf("Por evaluar A(x).\n");
  a=leeQ(ent);
  r=evaluaQx(A, a);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"A(");
  escQ(sal,a);
  fprintf(sal,") es:");
  escQ(sal,r);
  fprintf(sal,"\n");
  
  
  /* Integral definida */
  printf("Por calcular la integral definida de A(x).\n");
  a=leeQ(ent);
  b=leeQ(ent);
  r=integraDefQx(A,a,b);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"El polinomio A(x) integrado de ");
  escQ(sal,a);
  fprintf(sal," a ");
  escQ(sal,b);
  fprintf(sal," es: ");
  escQ(sal,r);
  fprintf(sal,"\n");
  liberaQx(&A);
  liberaQx(&B);
  
  fclose(sal);
  fclose(ent);
  system("PAUSE");
	return 0;
}
