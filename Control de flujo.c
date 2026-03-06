#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int a,b,c,d, max, min, min1, max2, tmp;
    
    printf("Prgrama para ordenar cuatro numeros");
    printf("\nDigite cuatro numeros: ");
    scanf("%d%d%d%d",&a,&b,&c,&d);
    printf("Los numeros son: %d, %d, %d, %d\n",a,b,c,d);
    
    
    
     if(a>b){
            tmp=a;
            a=b;
            b=tmp;
    }   
     if(c>d){
            tmp=c;
            c=d;
            d=tmp;
    if(b<=c){
        min=a;
        min1=b;
        max2=c;
        max=d;
    }else if(c<=a){
        min=c;
        if(b<=d){
            min1=a;
            max2=b;
            max=d;
        }else{
            max=b;
            if(d<a){
                min1=d;
                max2=a;
                }else{
                    min1=a;
                    max2=d;
                }
            
            }
        
    }else{
        min=a;
        min1=c;
        if(b<=d){
        max2=b;
        max=d;
        }else{
            max2=d;
            min1=a;
        }
        
    }
} 
    
  	
  printf("Los numeros ordenados son: %d, %d, %d, %d\n",min,min1,max2,max);
   printf("Fin del programa\n");
   system("PAUSE");
   
  	
  return 0;

}
