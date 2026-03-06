#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct _nodo_{
    int info;
    struct _nodo_ *izq,*der;
}nodo;

typedef nodo *arbol;

int inserta(int info, arbol *parbol);
int busca(int info, arbol a);
int preorden(arbol a);
int inorden(arbol a);
int posorden(arbol a);
nodo* creaNodo(int info);

int main(int argc, char *argv[])
{
  int x,opc,c=1;
  arbol A=NULL;
  
  do{
        printf("Digite una opcion:\n 1)Insertar informacion\n2)Preorden\n3)Inorden\n4)posorder\n5)Salir\n");
        scanf("%d",&opc);
        switch(opc){
            case 1: printf("\nIngrese un valor entero: ");
                    scanf("%d",&x);
                    inserta(x,&A);
                    break;
            case 2: printf("\nRecorrido preorden\n");
                    preorden(A);
                    printf("\n");
                    break;
            case 3: printf("\nRecorrido inorden\n");
                    inorden(A);
                    printf("\n");
                    break;
            case 4: printf("\nRecorrido posorden\n");
                    posorden(A);
                    printf("\n");
                    break;
            case 5: c=0;
                    break;
            default: printf("\nOpcion incorrecta");
        }
    }while(c);
  
  
  printf("\nFin del programa\n");
    system("PAUSE");	
  return 0;

}

int inserta(int info, arbol *parbol)
{
    nodo* aux;
    arbol auxArbol;
    
    aux=creaNodo(info);
    if(aux==NULL) return -1;
    if(*parbol==NULL){
        *parbol=aux;
        return 0;
    }
    
    auxArbol=*parbol;
    if(auxArbol->info>info) inserta(info,&auxArbol->izq);
    else inserta(info,&auxArbol->der);
    return 0;
    
    
    
}
int busca(int info, arbol a)
{
    if(a==NULL) return -1;
    if(a->info==info) return 0;
    if(a->info>info) return busca(info,a->izq);
    return busca(info,a->der);
}
int preorden(arbol a)
{
    if(a==NULL) return 0;
    printf("%3d", a->info);
    preorden(a->izq);
    preorden(a->der);
    return 0;
}
int inorden(arbol a)
{
     if(a==NULL) return 0;
     inorden(a->izq);
    printf("%3d", a->info);
    inorden(a->der);
    return 0;
}
int posorden(arbol a)
{
    if(a==NULL) return 0;
    printf("%3d", a->info);
    posorden(a->izq);
    posorden(a->der);
    return 0;
}

nodo* creaNodo(int info)
{
    nodo* ret;
    ret=(nodo*)malloc(sizeof(nodo));
    if(ret!=NULL){
        ret->info=info;
        ret->izq=ret->der=NULL;
    }
    return ret;
}
