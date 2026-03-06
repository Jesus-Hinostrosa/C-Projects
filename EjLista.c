 #include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct _elemlista_{
    int val;
    struct _elemlista_ *sig;
}elemlista;

typedef elemlista *Lista;

int inserta(int val1, Lista *plista);
int busca(int val1, Lista lista);
int borra(int val1, Lista *plista);
int imprime(Lista lista);
elemlista* creaEL(int val1);




int main(int argc, char *argv[])
{
  int continuar, val;
  Lista l=NULL;
  
  printf("Ejemplo de lista simplemente ligada\n");
  do{
    printf("\nDigite un entero:");
    scanf("%d",&val);
    inserta(val,&l);
    printf("El contenido de la lista es:");
    imprime(l);
    printf("Digite 0 para terminar, distinto de cero para continuar:");
    scanf("%d",&continuar);
    }while(continuar);
    
  printf("Fin del programa");
  system("PAUSE");
  return 0;

}


int inserta(int val1, Lista *plista)
{
    elemlista *aux;
    Lista auxl;
    
    aux=creaEL(val1);
    if(aux==NULL) return -1;
    if(*plista==NULL){
        *plista=aux;
        return 0;
    }
    auxl=*plista;
    if(aux->val<=auxl->val){
        aux->sig=auxl;
        *plista=aux;
        return 0;
    }
    while(auxl->sig!=NULL){
        if(aux->val<=auxl->val){
            aux->sig=auxl->sig;
            auxl->sig=aux;
            return 0;
        }
        auxl=auxl->sig;
    }
    auxl->sig=aux;
    return 0;
}
int busca(int val1, Lista lista)
{
    while(lista!=NULL){
        if(val1==lista->val) return 1;
        lista=lista->sig;
    }
    return 0;
}
int borra(int val1, Lista *plista)
{
    return 0;
    
}
int imprime(Lista lista)
{
    if(lista==NULL){
        printf("Lista vacia \n");
        return 0;
    }
    
    while(lista!=NULL){
        printf("%3d ",lista->val);
        lista=lista->sig;
    }
}

elemlista* creaEL(int val1)
{
    elemlista* ret;
    
    ret=(elemlista*)malloc(sizeof(elemlista));
    if(ret!=NULL){
        ret->val=val1; /* No siempre es asi, en este caso porque es un simple entero*/
        ret->sig=NULL;    
    }    
    return ret;
}



