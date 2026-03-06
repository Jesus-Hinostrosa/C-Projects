#include <stdio.h>   
#include <stdlib.h>   
#include <math.h>  
#include <string.h>  

#include "bGauss.h"
#include "bPoliG.h"


int main(int argc, char *argv[]) {
	FILE *ent, *sal;
	char *noment="poliG.txt", *nomsal="resultado.txt";
	Gx A, B, C, R={c:NULL, g:-1};
	int m, n, i;

  
  printf("Por leer el archivo %s.\n", noment);
  ent=fopen(noment,"rt");
  if(ent==NULL){
    int mi_error=errno; 
	printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	mi_error, strerror(mi_error));
    return -1;
  }
  printf("Por leer el polinomio A(x).\n");
   A=leeGx(ent);

  printf("Por leer el polinomio B(x).\n");
  B=leeGx(ent);
  
  /* Suma */
  printf("Por calcular A(x)+B(x).\n");
  C=sumaGx(A,B);
  
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
  escGx(sal, C);
  liberaGx(&C); 
  
  /* Resta */
  printf("Por calcular A(x)-B(x).\n");
  C=restGx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)-B(x)=");
  escGx(sal, C);
  liberaGx(&C);
  
  /* Producto */
  printf("Por calcular A(x)B(x).\n");
  C=multGx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)*B(x)=");
  escGx(sal, C);
  liberaGx(&C);
  
  /* Derivada */
  printf("Por calcular A'(x).\n");
  C=derivaGx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A'(x)=");
  escGx(sal, C);
  liberaGx(&C);
  liberaGx(&A); 
  liberaGx(&B); 
  
  fclose(sal);
  fclose(ent);
	return 0;
}
