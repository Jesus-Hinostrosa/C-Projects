#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> 
#include<string.h> 

#include "bH.h"
#include "bPoliH.h"

int main(int argc, char *argv[]) {
	FILE *ent, *sal;
	char *noment="poliH.txt", *nomsal="resultado.txt";
	H a,b,r;
	Hx A,B,C,R={g:-1,c:NULL};
	
	printf("Por leer el archivo %s.\n", noment);
	ent=fopen(noment,"rt");
	if(ent==NULL){
    int mi_error=errno; 
	printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	mi_error, strerror(mi_error));
    return -1;
	}
	printf("Por leer el polinomio A(x).\n");
	A=leeHx(ent);

	printf("Por leer el polinomio B(x).\n");
	B=leeHx(ent);
  
   /* Suma */
  printf("Por calcular A(x)+B(x).\n");
  C=sumaHx(A,B); 
  
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
  escHx(sal, C);
  liberaHx(&C); 
  
  /* Resta */
  printf("Por calcular A(x)-B(x).\n");
  C=restHx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)-B(x)=");
  escHx(sal, C);
  liberaHx(&C);
  
  /* Producto */
  printf("Por calcular A(x)B(x).\n");
  C=multHx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)*B(x)=");
  escHx(sal, C);
  liberaHx(&C);
  
   /* Cociente y residuo*/
  printf("Por calcular A(x)/B(x) y R(x).\n");
  C=divHx(A,B,&R);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)/B(x)=");
  escHx(sal, C);
  fprintf(sal, "Residuo=");
  escHx(sal, R); 
  liberaHx(&C);
  liberaHx(&R); 
  
  /* MCD */
  printf("Por calcular mcd(A(x),B(x)).\n");
  C=mcdHx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "mcd(A(x),B(x))=");
  escHx(sal, C);
  liberaHx(&C); 
  
   /* Derivada */
  printf("Por calcular A'(x).\n");
  C=derivaHx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A'(x)=");
  escHx(sal, C);
  liberaHx(&C);
  
  /* Integral indefinida*/
  printf("Por calcular la integral indefinida de A(x)\n");
  C=integraHx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "Integral indefinida de A(x)=");
  escHx(sal, C);
  liberaHx(&C);
  
  /* Evaluar */
  printf("Por evaluar A(x).\n");
  a=leeH(ent);
  r=evaluaHx(A, a);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"A(");
  escH(sal,a);
  fprintf(sal,") es:");
  escH(sal,r);
  fprintf(sal,"\n");
  
  
  /* Integral definida */
  printf("Por calcular la integral definida de A(x).\n");
  a=leeH(ent);
  b=leeH(ent);
  r=integraDefHx(A,a,b);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"El polinomio A(x) integrado de ");
  escH(sal,a);
  fprintf(sal," a ");
  escH(sal,b);
  fprintf(sal," es: ");
  escH(sal,r);
  fprintf(sal,"\n");
  
  
	liberaHx(&A); 
	liberaHx(&B);
	fclose(sal);
	fclose(ent);
	system("PAUSE");
	return 0;
}
