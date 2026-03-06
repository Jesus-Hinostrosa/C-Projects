#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> 
#include<string.h> 

#include "bcomp.h"
#include "bpoliC.h"

int main(int argc, char *argv[]) {
	FILE *ent, *sal;
	char *noment="poliC.txt", *nomsal="resultado.txt";
	C a,b,r;
	Cx A,B,C,R={g:-1,c:NULL};
	
	printf("Por leer el archivo %s.\n", noment);
  ent=fopen(noment,"rt");
  if(ent==NULL){
    int mi_error=errno; 
	printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	mi_error, strerror(mi_error));
    return -1;
  }
  printf("Por leer el polinomio A(x).\n");
   A=leeCx(ent);

  printf("Por leer el polinomio B(x).\n");
  B=leeCx(ent);
  
  /* Suma */
  printf("Por calcular A(x)+B(x).\n");
  C=sumaCx(A,B); 
  
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
  escCx(sal, C);
  liberaCx(&C); 
  
  /* Resta */
  printf("Por calcular A(x)-B(x).\n");
  C=restCx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)-B(x)=");
  escCx(sal, C);
  liberaCx(&C);
  
  /* Producto */
  printf("Por calcular A(x)B(x).\n");
  C=multCx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)*B(x)=");
  escCx(sal, C);
  liberaCx(&C);
  
 /* Cociente y residuo*/
  printf("Por calcular A(x)/B(x) y R(x).\n");
  C=divCx(A,B,&R);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)/B(x)=");
  escCx(sal, C);
  fprintf(sal, "Residuo=");
  escCx(sal, R); 
  liberaCx(&C);
  liberaCx(&R); 
  
  /* Derivada */
  printf("Por calcular A'(x).\n");
  C=derivaCx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A'(x)=");
  escCx(sal, C);
  liberaCx(&C);
  
  /* Integral indefinida*/
  printf("Por calcular la integral indefinida de A(x)\n");
  C=integraCx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "Integral indefinida de A(x)=");
  escCx(sal, C);
  liberaCx(&C);
  
  /* Evaluar */
  printf("Por evaluar A(x).\n");
  a=leeC(ent);
  r=evaluaCx(A, a);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"A(");
  escC(sal,a);
  fprintf(sal,") es:");
  escC(sal,r);
  fprintf(sal,"\n");
  
  
  /* Integral definida */
  printf("Por calcular la integral definida de A(x).\n");
  a=leeC(ent);
  b=leeC(ent);
  r=integraDefCx(A,a,b);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"El polinomio A(x) integrado de ");
  escC(sal,a);
  fprintf(sal," a ");
  escC(sal,b);
  fprintf(sal," es: ");
  escC(sal,r);
  fprintf(sal,"\n");
  liberaCx(&A);
  liberaCx(&B);


	fclose(sal);
	fclose(ent);
	system("PAUSE");
	return 0;
}
