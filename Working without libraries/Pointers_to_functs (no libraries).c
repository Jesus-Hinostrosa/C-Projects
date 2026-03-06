#include <stdio.h>    /*funciones de entrada y salida est'andar*/
#include <stdlib.h>   /*funciones de la biblioteca est'andar*/   
#include <string.h>
#include <math.h>

#include "bQ.h"
#include "bR.h"
#include "bC.h"
#include "bZp.h"
#include "bH.h"
#include "bG.h"
#include "bCoef.h"


int main(int argc, char *argv[]) {
	FILE *ent, *sal;
  char *noment="coeficientes.txt", *nomsal="resultado.txt";
  void *fs[]={sumaQ, sumaR, sumaH, sumaG, sumaZp, sumaC};
  void *fr[]={restaQ, restaR, restaH, restaG, restaZp, restaC};
  void *fp[]={prodQ, prodR, prodH, prodG, prodZp, prodC};
  void *fd[]={divQ, divR, divH, divZp, divC};
  int tipo,p=0;
  Coeficiente a, b;
  
  printf("Por leer el archivo %s.\n", noment);
  ent=fopen(noment,"rt");
  if(ent==NULL){
    int mi_error=errno; 
	printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	mi_error, strerror(mi_error));
    return -1;
  }
  fscanf(ent, "%d", &tipo);
  if(tipo==ZP) fscanf(ent, "%d", &p);
  a=leeCoef(ent,tipo,p);
  b=leeCoef(ent,tipo,p);
  
  printf("\nPor escribir el resultado en el archivo %s\n", nomsal);
  sal=fopen(nomsal, "wt");
  if (sal==NULL){
    int mi_error=errno; 
    printf("Hubo un error en la escritura del archivo: %d <<%s>>\nPor finalizar la ejecucion del programa.\n", 
      mi_error, strerror(mi_error));

    fclose(ent);
    return -1;
	}
	
	fprintf(sal,"Sumas: \n");
    muestraB(sal, a, b, fs[tipo], tipo);
    fprintf(sal,"Restas: \n");
	muestraB(sal, a, b, fr[tipo], tipo);
  	fprintf(sal,"Productos: \n");
	muestraB(sal, a, b, fp[tipo], tipo);
	if(tipo==GAUSSIANOS) fprintf(sal,"\nNo es posible dividir");
  	else if(tipo==ZP || tipo==COMPLEJOS){
  		fprintf(sal,"Divisiones: \n");
		muestraB(sal, a, b, fd[tipo-1], tipo);	
		}else{
		fprintf(sal,"Divisiones: \n");
		muestraB(sal, a, b, fd[tipo], tipo);
	}
  
	fclose(sal);
	fclose(ent);
	printf("\nFin del programa\n");
	system("PAUSE");
	return 0;
}


