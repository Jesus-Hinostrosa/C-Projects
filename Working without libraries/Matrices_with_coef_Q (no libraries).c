#include<stdio.h>
#include<stdlib.h>
#include<errno.h> 
#include<string.h> 

#include "bRac.h"
#include "bMatQ.h"

int main(int argc, char *argv[]) {
	
	FILE *ent, *sal;
  char *noment="matQ.txt", *nomsal="resultado.txt";
  MatQ A, B, C;
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
 A=leeMQ(ent);
  
  printf("Por leer matriz B.\n");
  B=leeMQ(ent);
  
  /* Suma */
  printf("Por calcular A+B.\n");
  if (A.m!=B.m || A.n!=B.n ){
    printf("No se puede efectuar la suma de matrices\n");
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=sumaMatQ(A,B);
  
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
  escMatQ(sal, C);
  LiberaMQ(&C);
  
  /* Resta */
  printf("Por calcular A-B.\n");
  if (A.m!=B.m || A.n!=B.n ){
    printf("No se puede efectuar la suma de matrices\n");
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=restaMatQ(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "La resta");
  escMatQ(sal, C);
  LiberaMQ(&C);
   
  /* Producto */
  printf("Por calcular AB.\n");
  if (A.n!=B.m){
    printf("No se puede efectuar la multiplicacion de matrices (%d!=%d)\n", A.n, B.m);
    printf("Por finalizar la ejecucion del programa.\n");
      fclose(ent);
    return -2;
  }
  C=multMatQ(A, B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "El producto");
  escMatQ(sal, C);
  LiberaMQ(&C);
  LiberaMQ(&A);
  LiberaMQ(&B);

  
  fclose(ent); 
  fclose(sal);

	return 0;
}
