/*
 * Profesor: Carlos Coronado
 * 
 * Curso de Programacion II
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> /*fnucion gettimeofday*/

signed long fiboRec(signed long n);
signed long fiboRecDinIni(signed long n);
signed long fiboRecDin(signed long fib[], signed long n);
signed long fiboIte(signed long n);

int main(int argc, char *argv[])
{
  signed int n, ret;
  struct timeval tvini, tvfin;
  long segundos;
  long microsegundos;
  signed long (*fibo[])(signed long) = {fiboRec, fiboRecDinIni, fiboIte};
  char *nombre[]={"fiboRec", "fiboRecDinIni", "fiboIte"};
  int i, tope=3;

  printf("digite n:");
  scanf("%ld", &n);
  for(i=0; i<tope; i++){
    gettimeofday(&tvini, NULL);
    printf("\nPor calcular el %d-esimo elemento: ", n);
    ret = fibo[i](n);
    printf("%ld \n", ret);
    gettimeofday(&tvfin, NULL);
    microsegundos=tvfin.tv_usec-tvini.tv_usec;
    segundos = tvfin.tv_sec-tvini.tv_sec;
    if (microsegundos<0){
      segundos--;
      microsegundos+=1000000;
    }

    printf("A la función %s le tomó %d.%06d segundos.\n", nombre[i], segundos, microsegundos);
  }
    system("PAUSE");
  printf("\nFin del programa.\n");

  return 0;
}


signed long fiboRec(signed long n)
{
  if (n<=1L) return n;
  return fiboRec(n-1)+fiboRec(n-2);
}

signed long fiboRecDinIni(signed long n)
{
  signed long *fib;
  signed long  i;
  
  if ((fib=(signed long*)malloc((n+1)*sizeof(signed long)))==NULL){
    printf("Espacio insuficiente en memoria para calcular el %d-esimo elemento en la sucesion de Fibonacci.\n", n);
    return -1;
  }
  for (i=0L; i<=n; i++) fib[i]=-1L;
  fib[0]=0L;
  if (n>0L) fib[1]=1L;

  return fiboRecDin(fib, n);
}

signed long fiboRecDin(signed long fib[], signed long n)
{
  if (fib[n]>=0L) return fib[n];
  fib[n] = fiboRecDin(fib, n-1)+fiboRecDin(fib, n-2);
  return fib[n];
}

signed long fiboIte(signed long n)
{
  signed int i, ret, ret_ant=1L, ret_ant_ant=0L;

  if (n<=1L) return n;
  for (i=2; i<=n; i++){
    ret=ret_ant+ret_ant_ant;
    ret_ant_ant=ret_ant;
    ret_ant=ret;
  }

  return ret;
}
