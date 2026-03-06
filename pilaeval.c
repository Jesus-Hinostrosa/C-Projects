#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

typedef struct _elemPila_{
    double c;
    struct _elemPila_ *sig;
}elemPila;

typedef elemPila *pila;

typedef struct _operador_{
    char c;
    struct _operador_ *sig;
}operador;

typedef operador *pilaOp;

int pushOp(char s, pilaOp *ppila);   
operador* creaOp(char s);
int imprimeOp(pilaOp stack);
char popOp(pilaOp *stack);
char revisaOp(pilaOp stack);
int pushVal(double s, pila *ppila);   
elemPila* creaVal(double s);
int imprimeVal(pila stack);
double popVal(pila *stack);
double revisaVal(pila stack);
char revisaOp(pilaOp stack);
int evalua(char dato[], pila *val, pilaOp *operadores);
int precedencia(char a, char b);
double aplica(double a, double b, char o);
double askVal(char c);
double aplicaF(double a, char o);
//char[] convierteCadena(char[] s);

int main(int argc, char *argv[])
{
    char a[64];
    pilaOp misOp=NULL;
    pila misVal=NULL;
    double i;
    
    printf("Este programa evalua la evaluacion que ingrese en los valores enteros de [-5,5]\n");
    printf("Los caracteres con minusculas son constantes por asignar\n");
    printf("Los caracteres con mayusuculas son las funciones \n\tS = sen(x)\n\tC = cos(x)\n\tT = tan(x)\n\tH = arcsen(x)\n\tJ = arccos(x)\n\tK = arctan(x)\n\tL = ln(x)\n\tF = E(x)\n");     
    printf("o las constantes matematicas Pi = P y e = E\n\n");
    printf("Ingrese una cadena de caracteres que represente dicha expresion: ");
    scanf("%s",&a);
    evalua(a,&misVal,&misOp);
    
    printf("Press enter to continue ...");
    system("PAUSE");	
    return 0;
}


operador* creaOp(char s)
{
    operador* ret;
    
    ret=(operador*)malloc(sizeof(operador));
    if(ret!=NULL){
        ret->c=s;
        ret->sig=NULL;    
    }    
    return ret;
}

int pushOp(char s, pilaOp *ppila)
{
    operador *nuevo;
    pilaOp auxPila=NULL;
    
    nuevo=creaOp(s);
    if(nuevo==NULL) return -1;
    if(*ppila==NULL){
        *ppila=nuevo;
        return 0;
    }
   
    auxPila=*ppila;
    nuevo->sig=auxPila;
    *ppila=nuevo;
    return 0;
}


int imprimeOp(pilaOp stack)
{
    if(stack==NULL){
        printf("Pila vacia \n");
        return 0;
    }
    
    while(stack!=NULL){
        printf("%c ",stack->c);
        stack=stack->sig;
    }
    return 0;
}

char popOp(pilaOp *stack)
{
    char ret;
    pilaOp aux;
    
    ret=(*stack)->c;
    aux=*stack;
    *stack=(*stack)->sig;
    free(aux);
    return ret;
}

elemPila* creaVal(double s){
    elemPila* ret;
    
    ret=(elemPila*)malloc(sizeof(elemPila));
    if(ret!=NULL){
        ret->c=s;
        ret->sig=NULL;    
    }    
    return ret;
}    
int pushVal(double s, pila *ppila){
    elemPila *nuevo;
    pila auxPila=NULL;
    
    nuevo=creaVal(s);
    if(nuevo==NULL) return -1;
    if(*ppila==NULL){
        *ppila=nuevo;
        return 0;
    }
   
    auxPila=*ppila;
    nuevo->sig=auxPila;
    *ppila=nuevo;
    return 0;
}   

int imprimeVal(pila stack){
    if(stack==NULL){
        printf("Pila vacia \n");
        return 0;
    }
    
    while(stack!=NULL){
        printf("%lg ",stack->c);
        stack=stack->sig;
    }
    return 0;
}

double popVal(pila *stack){
    double ret;
    pila aux;
    
    ret=(*stack)->c;
    aux=*stack;
    *stack=(*stack)->sig;
    free(aux);
    return ret;
}

double revisaVal(pila stack){
    double ret;
    ret=stack->c;
    return ret;
}
char revisaOp(pilaOp stack){
    char ret;
    ret=stack->c;
    return ret;
}

double askVal(char c){
    double ret;
    if(c=='E') return M_E;
    if(c=='P') return M_PI;
    printf("Ingrese el valor de %c: ", c);
    scanf("%lg", &ret);
    return ret;
}
/*
char[] convierteCadena(char[] s){
    int i,tam;
    char ret[64];
    double v;
    
    tam=strlen(s);
    for(i=0;i<tam;i++){
        if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/' || s[i]=='%' || s[i]=='^' ||
           s[i]=='S' || s[i]=='C' || s[i]=='T' || s[i]=='H' || s[i]=='J' || s[i]=='K' || s[i]=='L' || s[i]=='F'||
           s[i]=='(' || s[i]==')' || s[i]=='E' || s[i]=='P') ret[i]=s[i];
        else{
            printf("Ingrese el valor de %c: ", s[i]);
            scanf("%lg", &v);
            ret[i]=ValToChar(v);
        } 
        
    }
    return ret;
}

char ValToChar(double val){
    char c;
    if(
} */

double aplica(double a, double b, char o)
{
    double ret;
    int ret1;
    if(o=='+') ret=a+b;
    if(o=='-') ret=a-b;
    if(o=='*') ret=a*b;
    if(o=='/'){
         if(b!=0.0)ret=a/b;
        else{
        printf("Resultado erroneo // No se puede dividir entre cero\n");
        return 0;
        }
    }
    if(o=='%') ret1=((int)a)%((int)b);
    if(o=='^') ret=pow(a,b);
    return ret;
}
double aplicaF(double a, char o)
{
    double ret;
    int ret1;
    if(o=='S') ret=sin(a);
    if(o=='C') ret=cos(a);
    if(o=='T') ret=tan(a);  
    if(o=='H') ret=asin(a);
    if(o=='J') ret=acos(a);
    if(o=='K') ret=atan(a);
    if(o=='L') ret=log(a);
    if(o=='F') ret=exp(a);
    return ret;
}

int precedencia(char a, char b)
{
    if(a==b || a=='+' && b=='-' || a=='-' && b=='+' ||
       a=='*' && b=='/' || a=='*' && b=='%' || 
       a=='/' && b=='*' || a=='/' && b=='%' ||
       a=='%' && b=='*' || a=='%' && b=='/' ||
       a=='S' && b=='C' || a=='S' && b=='T' ||
       a=='S' && b=='H' || a=='S' && b=='J' ||
       a=='S' && b=='K' || a=='S' && b=='L' ||
       a=='S' && b=='F' || a=='C' && b=='S' ||
       a=='C' && b=='T' || a=='C' && b=='H' ||
       a=='C' && b=='J' || a=='C' && b=='K' ||
       a=='C' && b=='L' || a=='C' && b=='F' ||
       a=='T' && b=='S' || a=='T' && b=='C' ||
       a=='T' && b=='H' || a=='T' && b=='J' ||
       a=='T' && b=='K' || a=='T' && b=='L' ||
       a=='T' && b=='F' || a=='H' && b=='S' ||
       a=='H' && b=='C' || a=='H' && b=='T' ||
       a=='H' && b=='J' || a=='H' && b=='K' ||
       a=='H' && b=='L' || a=='H' && b=='F' ||
       a=='J' && b=='S' || a=='J' && b=='C' ||
       a=='J' && b=='T' || a=='J' && b=='H' ||
       a=='J' && b=='K' || a=='J' && b=='L' ||
       a=='J' && b=='F' || a=='K' && b=='S' ||
       a=='K' && b=='C' || a=='K' && b=='T' ||
       a=='K' && b=='H' || a=='K' && b=='J' ||
       a=='K' && b=='L' || a=='K' && b=='F' ||
       a=='L' && b=='S' || a=='L' && b=='C' ||
       a=='L' && b=='T' || a=='L' && b=='H' ||
       a=='L' && b=='J' || a=='L' && b=='K' ||
       a=='L' && b=='F' || a=='F' && b=='S' ||
       a=='F' && b=='C' || a=='F' && b=='T' ||
       a=='F' && b=='H' || a=='F' && b=='J' ||
       a=='F' && b=='K' || a=='F' && b=='L' ) return 1;
    else if(a=='+' && b=='*' || a=='+' && b=='/' || a=='+' && b=='S' || a=='+' && b=='C' || a=='+' && b=='J' || a=='+' && b=='K' ||
            a=='+' && b=='%' || a=='+' && b=='^' || a=='+' && b=='T' || a=='+' && b=='H' || a=='+' && b=='L' || a=='+' && b=='F' ||
            a=='-' && b=='*' || a=='-' && b=='/' || a=='-' && b=='S' || a=='-' && b=='C' || a=='-' && b=='J' || a=='-' && b=='K' ||
            a=='-' && b=='%' || a=='-' && b=='^' || a=='-' && b=='T' || a=='-' && b=='H' || a=='-' && b=='L' || a=='-' && b=='F' ||
            a=='*' && b=='^' || a=='*' && b=='S' || a=='*' && b=='C' || a=='*' && b=='J' || a=='*' && b=='K' ||a=='*' && b=='T' || a=='*' && b=='H' || a=='*' && b=='L' || a=='*' && b=='F' ||
            a=='/' && b=='^' || a=='/' && b=='S' || a=='/' && b=='C' || a=='/' && b=='J' || a=='/' && b=='K' ||a=='/' && b=='T' || a=='/' && b=='H' || a=='/' && b=='L' || a=='/' && b=='F' ||
            a=='%' && b=='^' || a=='%' && b=='S' || a=='%' && b=='C' || a=='%' && b=='J' || a=='%' && b=='K' ||a=='%' && b=='T' || a=='%' && b=='H' || a=='%' && b=='L' || a=='%' && b=='F' ||
            a=='^' && b=='S' || a=='^' && b=='C' || a=='^' && b=='J' || a=='^' && b=='K' ||a=='^' && b=='T' || a=='^' && b=='H' || a=='^' && b=='L' || a=='^' && b=='F') return 1;
    else return 0;
}


int evalua(char dato[], pila *val, pilaOp *operadores)
{
    int tam,i;
    char c;
    double x,a,b,z,aux[64];
    
    tam=strlen(dato);
    for(i=0;i<tam;i++){
        if(dato[i]=='+' || dato[i]=='-' || dato[i]=='*' || dato[i]=='/' || dato[i]=='%' || dato[i]=='^' ||
           dato[i]=='S' || dato[i]=='C' || dato[i]=='T' || dato[i]=='H' || dato[i]=='J' || dato[i]=='K' || dato[i]=='L' || dato[i]=='F'||
           dato[i]=='(' || dato[i]==')' || dato[i]=='E' || dato[i]=='P' || dato[i]=='x') aux[i]=0.0;
        else aux[i]=askVal(dato[i]);
    }       
    
    for(x=-5.0;x<=5.0;x++){
    for(i=0;i<tam;i++){
        if(dato[i]=='+' || dato[i]=='-' || dato[i]=='*' || dato[i]=='/' || dato[i]=='^' || dato[i]=='%' ||
           dato[i]=='S' || dato[i]=='C' || dato[i]=='T' || dato[i]=='H' || dato[i]=='J' || dato[i]=='K' ||
           dato[i]=='L' || dato[i]=='F' ){
            while(*operadores!=NULL && precedencia(dato[i],(*operadores)->c)){
                if((*operadores)->c =='+' || (*operadores)->c =='-' || (*operadores)->c =='*' || (*operadores)->c =='/' || (*operadores)->c =='^' || (*operadores)->c =='%'){
                    c=popOp(operadores);
                    b=popVal(val);
                    a=popVal(val);
                    z=aplica(a,b,c);
                    pushVal(z,val);
                }else{
                    c=popOp(operadores);
                    b=popVal(val);
                    z=aplicaF(b,c);
                    pushVal(z,val);
                }
                
            }
            pushOp(dato[i],operadores);
        }else if(dato[i]==')'){
            c=revisaOp(*operadores);
            while(c!='('){
                c=popOp(operadores);
                b=popVal(val);
                a=popVal(val);
                z=aplica(a,b,c);
                pushVal(z,val);
                c=revisaOp(*operadores);
            }
            popOp(operadores);
        }else if(dato[i]=='(') pushOp(dato[i],operadores);
        else if(dato[i]=='x') pushVal(x,val);
        else{
            z=aux[i];
            pushVal(z,val);
        }
    }
    while(*operadores!=NULL){
        if((*operadores)->c =='+' || (*operadores)->c=='-' || (*operadores)->c=='*' ||
           (*operadores)->c =='/' || (*operadores)->c=='^' || (*operadores)->c=='%'){
                 c=popOp(operadores);
                 b=popVal(val);
                 a=popVal(val);
                 z=aplica(a,b,c);
                 pushVal(z,val);
            }else{
                c=popOp(operadores);
                b=popVal(val);
                z=aplicaF(b,c);
                pushVal(z,val);
            }
       
    }
    printf("La expresion evaluada en %lg es: %lg\n",x,z);
    }
    return 0;
} 
//a+S(b*x^c/d-e)-(f*g/h-i^j+k)-L(a+E)
