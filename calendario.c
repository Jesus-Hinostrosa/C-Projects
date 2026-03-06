#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int mes, dia, ndias, ndiames,anio,bis,diasem;
    
    printf("Digite dia, mes y anio:");
    scanf("%d%d%d", &dia, &mes, &anio); 
    
    printf("\nDigite el dia de la semana que fue primero de enero considerando 1=lunes, ..., 6=sabado\n");
    scanf("%d", &diasem);
    
    if((anio%4)!=0) bis=0;
    else if(anio%400==0) bis=1;
    else if(anio%100==0) bis=0;
    else bis=1;
    
    if(dia<=0 || 31<dia){
        printf("\n Fecha incorrecta. Por salir del programa");
        return 0;
    }
    if(dia==31 && (mes==2 || mes==4 || mes==6 || mes==9 || mes==11)){
        printf("\n Fecha incorrecta. Por salir del programa");
        return 0;
    }
    
    if((dia==30 && mes==2) || (dia==29 && mes==2 && bis==0) ){
        printf("\n Fecha incorrecta. Por salir del programa");
        return 0;
    }
    
    
    switch(mes-1){
        case 0: ndiames=0;break;
        case 1: ndiames=31;break;
        case 2: ndiames=31+28+bis;break; 
        case 3: ndiames=31+28+31+bis;break;
        case 4: ndiames=31+28+31+30+bis;break;
        case 5: ndiames=31+28+31+30+31+bis;break;
        case 6: ndiames=31+28+31+30+31+30+bis;break;
        case 7: ndiames=31+28+31+30+31+30+31+bis;break;
        case 8: ndiames=31+28+31+30+31+30+31+31+bis;break;
        case 9: ndiames=31+28+31+30+31+30+31+31+30+bis;break;
        case 10: ndiames=31+28+31+30+31+30+31+31+30+31+bis;break;
        case 11: ndiames=31+28+31+30+31+30+31+31+30+31+30+bis;break;
        }   
       ndias=ndiames+dia-1;
        
    
    printf("Los dias que hay del primero de enero a la fecha introducida son %d\n", ndias);
   
    printf("El dia de la semana de la fecha introducida es %d \n", (diasem+ndias)%7);
   
    printf("Fin del programa\n");
   system("PAUSE");
   
  	
  return 0;

}
