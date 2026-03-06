#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> 
#include<string.h> 

typedef struct C{
   double r,i;
}C;

typedef struct Cx{
   int g;
   C *c;
}Cx;

//funciones C//
C leeC(FILE *f);
int escC(FILE *f, C a); 
int esCeroC(C a); 
int igualC(C a, C b);     
C creaC(int num, int den);
C sumaC(C a, C b);
C restaC(C a, C b);
C prodC(C a, C b);
C invC(C a);
C powC(C a, int g);
C divC(C a, C b);

//funciones Qx//
Cx leeCx(FILE *f);
int escCx(FILE *f, Cx p);
Cx sumaCx(Cx a, Cx b);
Cx restCx(Cx a, Cx b);
Cx multCx(Cx a, Cx b);
Cx multMonoCx(Cx a, C c, int e);
Cx divCx(Cx a, Cx b, Cx *res);
Cx mcdCx(Cx a, Cx b);
Cx derivaCx(Cx a);
Cx integraCx(Cx a);
C evaluaCx(Cx a, C d);
C integraDefCx(Cx p, C a, C b);
int esCeroCx(Cx a);
Cx copiaCx(Cx a);
Cx copiaMenosCx(Cx a);
int  liberaCx(Cx *a);

int main(int argc, char *argv[]) {
	FILE *ent, *sal;
  char *noment="poliC.txt", *nomsal="resultado.txt";
   C a,b,r;
  Cx A, B, C, R={c:NULL, g:-1};
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
   A=leeCx(ent);

  printf("Por leer el polinomio B(x).\n");
  B=leeCx(ent);
  
  /* Suma */
  printf("Por calcular A(x)+B(x).\n");
  C=sumaCx(A,B);
  
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
  escCx(sal, A);
  escCx(sal, B);
  escCx(sal, C);
  liberaCx(&C);
  
  /* Resta */
  printf("Por calcular A(x)-B(x).\n");
  C=restCx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)-B(x)=");
  escCx(sal, C);
  liberaCx(&C);
  
  /* Producto */
  printf("Por calcular A(x)B(x).\n");
  C=multCx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)*B(x)=");
  escCx(sal, C);
  liberaCx(&C);
  
  /* Cociente y residuo 
  printf("Por calcular A(x)/B(x) y R(x).\n");
  C=divCx(A,B,&R);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)/B(x)=");
  escCx(sal, C);
  fprintf(sal, "Residuo=");
  escQx(sal, R); 
  liberaCx(&C);
  liberaCx(&R); */
  
  /* MCD 
  printf("Por calcular mcd(A(x),B(x)).\n");
  C=mcdQx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "mcd(A(x),B(x))=");
  escQx(sal, C);
  liberaQx(&C); */
  
  /* Derivada */
  printf("Por calcular A'(x).\n");
  C=derivaCx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A'(x)=");
  escCx(sal, C);
  liberaCx(&C);
  
  /* Integral indefinida*/
  printf("Por calcular la integral indefinida de A(x)\n");
  C=integraCx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "Integral indefinida de A(x)=");
  escCx(sal, C);
  liberaCx(&C);
  
  /* Evaluar */
  printf("Por evaluar A(x).\n");
  a=leeC(ent);
  r=evaluaCx(A, a);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"A(");
  escC(sal,a);
  fprintf(sal,") es:");
  escC(sal,r);
  fprintf(sal,"\n");
  
  
  /* Integral definida */
  printf("Por calcular la integral definida de A(x).\n");
  a=leeC(ent);
  b=leeC(ent);
  r=integraDefCx(A,a,b);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"El polinomio A(x) integrado de ");
  escC(sal,a);
  fprintf(sal," a ");
  escC(sal,b);
  fprintf(sal," es: ");
  escC(sal,r);
  fprintf(sal,"\n");
  
  fclose(ent);
  system("PAUSE");
	return 0;
}

//funciones C//
C leeC(FILE *f){
	C a;

   fscanf(f,"%lg%lg",&a.r,&a.i);	
  
  return a;
}
int escC(FILE *f, C a){
	if(a.r==0.0 &&a.i==0.0) fprintf(f,"0");
     else{
     	if(a.r==0.0);
     	else fprintf(f,"%+lg",a.r);
     	if (a.i==0.0);
     	else{
     		if(a.i==1.0) fprintf(f,"+i");
     		else{
     			if(a.i==-1.0) fprintf(f,"-i");
     		    else fprintf(f,"%+lgi",a.i);	
			 }
     		
		 }
	 }
	return 0;
} 
int esCeroC(C a){
	if(a.r==0.0 && a.i==0.0) return 1;
	else return 0;
} 
int igualC(C a, C b){
	if(a.r==b.r	&& a.i==b.i) return 1;
	else return 0;
}     
C creaC(int num, int den){
	C r = {num, den};

  return r;
}
C sumaC(C a, C b){
	C r={r:a.r+b.r, i:a.i+b.i};           
	
  return r;
}
C restaC(C a, C b){
	C r={r:a.r-b.r, i:a.i-b.i};           
	
  return r;
}
C prodC(C a, C b){
	C r={r:a.r*b.r-a.i*b.i, i:a.r*b.i+a.i*b.r};           
	
  return r;
}
C invC(C a){
	C c; 
	double n;
	
	n=sqrt(a.r*a.r+a.i*a.i);
	c.r=a.r/(n*n);
	c.i=-a.i/(n*n);
	
	return c;
	
}
C powC(C a, int g){
	C ret=a;
    int i;
    
    for(i=1;i<g;i++) ret=prodC(ret,a);
    return ret;
}
C divC(C a, C b){
	C c;
	
	b=invC(b);
	c=prodC(a,b);
	
	return c;
}

//funciones Qx//
Cx leeCx(FILE *f){
	Cx ret;
  int i;

  printf("Por leer el grado\n");
  fscanf(f,"%d", &(ret.g));

  if((ret.c=(C*)malloc((ret.g+1)*sizeof(C)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for (i=0; i<=ret.g; i++)
    ret.c[i]=leeC(f);

  return ret;
}
int escCx(FILE *f, Cx p){
	int i;
	C unit={r:1,i:0};
  
  if(p.g<0){
    fprintf(f, " 0\n\n");
    return 0;
  }
  if(p.g==0){
  	escC(f, p.c[0]);
    fprintf(f, "\n\n");
    return 0;
  }

	if (!esCeroC(p.c[0])){
		escC(f, p.c[0]);
		fprintf(f, "+");
	} 
	if(!esCeroC(p.c[1])){
  		if(igualC(p.c[1],unit)){
  			fprintf(f,"+x");
  			if(p.g!=1) fprintf(f, "+");
		  } 
    	else{
    		fprintf(f, "(");
			escC(f,p.c[1]);
			fprintf(f, ")");
    		fprintf(f,"x ");
    		if(p.g!=1) fprintf(f, "+");
			} 
		}
		  
  	for(i=2; i<=p.g; i++){
  	if(i=p.g){
  		if (!esCeroC(p.c[i])){
    	if(igualC(p.c[i],unit)){
    		fprintf(f,"+x^%d ", i);
		} 
    	else{
    		fprintf(f, "(");
			escC(f,p.c[i]);
			fprintf(f, ")");
    		fprintf(f,"x^%d ", i);
		} 
	} 
	  }else{
	  	if (!esCeroC(p.c[i])){
    	if(igualC(p.c[i],unit)){
    		fprintf(f,"+x^%d ", i);
    		fprintf(f, "+");
		} 
    	else{
    		fprintf(f, "(");
			escC(f,p.c[i]);
			fprintf(f, ")");
    		fprintf(f,"x^%d ", i);
    		fprintf(f, "+");
		} 
	} 
	  }
	
  }

  fprintf(f,"\n\n");
  
  return 0;
}
Cx sumaCx(Cx a, Cx b){
  Cx ret;
  int i, min;

  if (a.g<0){
    return copiaCx(b);
  }
  if (b.g<0){
    return copiaCx(a);
  }
  if (a.g<b.g){
    min = a.g;
    ret.g = b.g;
  } else{
    min = b.g;
    ret.g = a.g;
  }
  if((ret.c=(C*)malloc((ret.g+1)*sizeof(C)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  for (i=0; i<=min; i++) ret.c[i]=sumaC(a.c[i],b.c[i]);
  if (a.g==min){
    for (; i<=ret.g; i++) ret.c[i]=b.c[i];
  }
  if (b.g==min){
    for (; i<=ret.g; i++) ret.c[i]=a.c[i];
  }
  while(ret.g>=0 && esCeroC(ret.c[ret.g])) ret.g--;
  if (ret.g<0){
    free(ret.c);
    ret.c = NULL;
  }
  return ret;
}
Cx restCx(Cx a, Cx b){
	Cx ret;
  int i, min;
  C neg={r:1,i:0};

  if (a.g<0){
    return copiaMenosCx(b);
  }
  if (b.g<0){
    return copiaCx(a);
  }
  if (a.g<b.g){
    min = a.g;
    ret.g = b.g;
  } else{
    min = b.g;
    ret.g = a.g;
  }
  if((ret.c=(C*)malloc((ret.g+1)*sizeof(C)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  for (i=0; i<=min; i++) ret.c[i]=restaC(a.c[i],b.c[i]);
  if (a.g==min){
    for (; i<=ret.g; i++) ret.c[i]=prodC(neg,b.c[i]);
  }
  if (b.g==min){
    for (; i<=ret.g; i++) ret.c[i]=a.c[i];
  }
  while(ret.g>=0 && esCeroC(ret.c[ret.g])) ret.g--;
  if (ret.g<0){
    free(ret.c);
    ret.c = NULL;
  }
  return ret;
}
Cx multCx(Cx a, Cx b){
	int i, j;
  Cx ret;
  C ceroC={r:1,i:0};

  ret.g=a.g+b.g;
  if((ret.c=(C*)malloc((ret.g+1)*sizeof(C)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  for (i=0; i<=ret.g; i++) ret.c[i]=ceroC;
  for (i=0; i<=a.g; i++)
    for(j=0; j<=b.g; j++)
      ret.c[i+j]=sumaC(ret.c[i+j],prodC(a.c[i],b.c[j]));

  return ret;
}
Cx multMonoCx(Cx a, C c, int e){
	int i;
  Cx ret;
  C ceroC={r:1,i:0};

  ret.g=a.g+e;
  if((ret.c=(C*)malloc((ret.g+1)*sizeof(C)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for (i=0; i<=ret.g; i++) ret.c[i]=ceroC;
  for (i=e; i<=ret.g; i++) ret.c[i]=prodC(a.c[i-e],c);

  return ret;
}
Cx divCx(Cx a, Cx b, Cx *res){
	Cx ret,aux,aaux;
	int grad,i;
	
	aaux=copiaCx(a);
	a=aaux; 
	
	ret.g=a.g-b.g;
    if((ret.c=(C*)malloc((ret.g+1)*sizeof(C)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
    
  for (i=0; i<=ret.g; i++){
  	ret.c[i].r=0.0;
  	ret.c[i].i=0.0;
  } 

  do{
    grad=a.g-b.g;
    ret.c[grad] =divC(a.c[a.g],b.c[b.g]);
    aux=multMonoCx(b, ret.c[grad], grad);
    aaux=restCx(a,aux);
    liberaCx(&a);
    a=aaux;
    liberaCx(res);
    *res=copiaCx(a);
  }while(!esCeroCx(*res) && (res->g>=b.g));
	
   return ret;	
}

Cx mcdCx(Cx a, Cx b){
	Cx aaux,baux,r={g:-1,c:NULL};
	
	if(esCeroCx(b)){
		return a;
	}
	
	aaux=copiaCx(a);
	a=aaux;
	
	baux=copiaCx(b);
	b=baux;
	
	divCx(aaux,baux,&r);

	while(!esCeroCx(r)){
	   divCx(aaux,baux,&r);
	   aaux=copiaCx(baux);
	   liberaCx(&baux);
	   baux=copiaCx(r);
	   liberaCx(&r);}

	return baux;
}
Cx derivaCx(Cx a){
	Cx ret={g:a.g-1,c:NULL};
	int i;
	
	if((ret.c=(C*)malloc((ret.g+1)*sizeof(C)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
	
	for(i=0;i<=ret.g;i++){
	  ret.c[i].r=(i+1)*a.c[i+1].r;
	  ret.c[i].i=(i+1)*a.c[i+1].i;
	}
	
	return ret;
}
Cx integraCx(Cx a){
	Cx ret={g:a.g+1,c:NULL};
	int i;
	
	if((ret.c=(C*)malloc((ret.g+1)*sizeof(C)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
    
    ret.c[0].r=0.0;
    ret.c[0].i=0.0;
    for(i=1;i<=ret.g;i++){
     ret.c[i].r=a.c[i-1].r/i;
	 ret.c[i].i=a.c[i-1].i/i;	
	} 
	
	return ret;
}
C evaluaCx(Cx a, C d){
	C r={r:1, i:0};
	int i;

	for(i=0;i<=a.g;i++) r=sumaC(r, prodC(a.c[i],powC(d,i)));
	return r;
}
C integraDefCx(Cx p, C a, C b){
	Cx P={g:p.g+1,c:NULL};
	C Pb,Pa,r;
	
	P=integraCx(p);
	Pb=evaluaCx(P,b);
	Pa=evaluaCx(P,a);
	r=restaC(Pb,Pa);	
	return r;
}
int esCeroCx(Cx a){
	return a.g <0;
}
Cx copiaCx(Cx a){
	Cx ret;
  int i;

  ret.g = a.g;
  if (ret.g<0){
    ret.c=NULL;
    return ret;
  }
  if((ret.c=(C*)malloc((ret.g+1)*sizeof(C)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }

  for(i=0; i<=ret.g; i++){
  	ret.c[i].r=a.c[i].r;
  	ret.c[i].i=a.c[i].i;
  }

  return ret;
}
Cx copiaMenosCx(Cx a){
	Cx ret;
  int i;

  ret.g = a.g;
  if (ret.g<0){
    ret.c=NULL;
    return ret;
  }
  if((ret.c=(C*)malloc((ret.g+1)*sizeof(C)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for(i=0; i<=ret.g; i++){
  	ret.c[i].r=-a.c[i].r;
  	ret.c[i].i=-a.c[i].i;
  }

  return ret;
}
int  liberaCx(Cx *a){
	if(a->c!=NULL) free(a->c);
  a->g=-1;
  a->c=NULL;
  return 0;	
}
