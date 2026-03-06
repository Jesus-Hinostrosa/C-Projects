#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> 
#include<string.h> 

#include "bZp.h"
#include "bPoliZp.h"

int main(int argc, char *argv[]) {
	FILE *ent, *sal;
	char *noment="poliZp.txt", *nomsal="resultado.txt";
	Zpx A,B,C,R={g:-1,c:NULL};
	Zp a,b,r;
	int p;
	
	printf("Por leer el archivo %s.\n", noment);
	ent=fopen(noment,"rt");
	if(ent==NULL){
	int mi_error=errno; 
	printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	mi_error, strerror(mi_error));
    return -1;
	}
	printf("Por leer el primo \n");
	fscanf(ent,"%d",&p);
	printf("Por leer el polinomio A(x).\n");
	A=leeZpx(ent,p);

	printf("Por leer el polinomio B(x).\n");
	B=leeZpx(ent,p);
  
  /* Suma */
  printf("Por calcular A(x)+B(x).\n");
  C=sumaZpx(A,B);
  
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
  escZpx(sal, C);
  liberaZpx(&C);
  
  /* Resta */
  printf("Por calcular A(x)-B(x).\n");
  C=restZpx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)-B(x)=");
  escZpx(sal, C);
  liberaZpx(&C);
  
  /* Producto */
  printf("Por calcular A(x)B(x).\n");
  C=multZpx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)*B(x)=");
  escZpx(sal, C);
  liberaZpx(&C);
  
  /* Cociente y residuo */
  printf("Por calcular A(x)/B(x) y R(x).\n");
  C=divZpx(A,B,&R);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)/B(x)=");
  escZpx(sal, C);
  fprintf(sal, "Residuo=");
  escZpx(sal, R);
  liberaZpx(&C);
  liberaZpx(&R);
  
  /* MCD */
  printf("Por calcular mcd(A(x),B(x)).\n");
  C=mcdZpx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "mcd(A(x),B(x))=");
  escZpx(sal, C);
  liberaZpx(&C); 
  
  /* Derivada */
  printf("Por calcular A'(x).\n");
  C=derivaZpx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A'(x)=");
  escZpx(sal, C);
  liberaZpx(&C);
  
  /* Integral indefinida*/
  printf("Por calcular la integral indefinida de A(x)\n");
  C=integraZpx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "Integral indefinida de A(x)=");
  escZpx(sal, C);
  liberaZpx(&C);
  
   /* Evaluar */
  printf("Por evaluar A(x).\n");
  a=leeZp(ent,p);
  r=evaluaZpx(A, a);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"A(");
  escZp(sal,a);
  fprintf(sal,") es:");
  escZp(sal,r);
  fprintf(sal,"\n");
  
  /* Integral definida */
  printf("Por calcular la integral definida de A(x).\n");
  a=leeZp(ent,p);
  b=leeZp(ent,p);
  r=integraDefZpx(A,a,b);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"El polinomio A(x) integrado de ");
  escZp(sal,a);
  fprintf(sal," a ");
  escZp(sal,b);
  fprintf(sal," es: ");
  escZp(sal,r);
  fprintf(sal,"\n");
  liberaZpx(&B);
  liberaZpx(&A);
	
	fclose(sal);
	fclose(ent);
	return 0;
}
