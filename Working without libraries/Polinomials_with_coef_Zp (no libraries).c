#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> 
#include<string.h> 

typedef struct zp{
   int p,n;
}Zp;

typedef struct zpx{
  int g;
  Zp *c;
}Zpx;

// funciones Zp //
Zp leeZp(FILE *f, int p);
int escZp(FILE *f, Zp a);
int simpZp(Zp d);
Zp creaZp(int n, int p);
Zp sumaZp(Zp a, Zp b);
Zp restaZp(Zp a, Zp b);
Zp prodZp(Zp a, Zp b);
Zp powZp(Zp a, int g);
Zp invZp(Zp d);
Zp divZp(Zp a, Zp b);

//funciones Zpx//
Zpx leeZpx(FILE *f, int p);
int escZpx(FILE *f, Zpx p);
Zpx sumaZpx(Zpx a, Zpx b);
Zpx restZpx(Zpx a, Zpx b);
Zpx multZpx(Zpx a, Zpx b);
Zpx multMonoZpx(Zpx a, Zp b, int e);
Zpx divZpx(Zpx a, Zpx b, Zpx *res);
Zpx mcdZpx(Zpx a, Zpx b);
Zpx derivaZpx(Zpx a);
Zpx integraZpx(Zpx a);
Zp evaluaZpx(Zpx a, Zp d);
Zp integraDefZpx(Zpx p, Zp a, Zp b);
int esCeroZpx(Zpx a);
Zpx copiaZpx(Zpx a);
Zpx copiaMenosZpx(Zpx a);
int liberaZpx(Zpx *a);


int main(int argc, char *argv[]) {
	FILE *ent, *sal;
	char *noment="poliZp.txt", *nomsal="resultado.txt";
	Zpx A,B,C,R={g:-1,c:NULL};
	Zp a,b,r;
	int p;
	
	printf("Por leer el archivo %s.\n", noment);
	ent=fopen(noment,"rt");
	if(ent==NULL){
	int mi_error=errno; 
	printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	mi_error, strerror(mi_error));
    return -1;
	}
	printf("Por leer el primo \n");
	fscanf(ent,"%d",&p);
	printf("Por leer el polinomio A(x).\n");
	A=leeZpx(ent,p);

	printf("Por leer el polinomio B(x).\n");
	B=leeZpx(ent,p);
  
  /* Suma */
  printf("Por calcular A(x)+B(x).\n");
  C=sumaZpx(A,B);
  
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
  escZpx(sal, C);
  liberaZpx(&C);
  
  /* Resta */
  printf("Por calcular A(x)-B(x).\n");
  C=restZpx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)-B(x)=");
  escZpx(sal, C);
  liberaZpx(&C);
  
  /* Producto */
  printf("Por calcular A(x)B(x).\n");
  C=multZpx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)*B(x)=");
  escZpx(sal, C);
  liberaZpx(&C);
  
  /* Cociente y residuo */
  printf("Por calcular A(x)/B(x) y R(x).\n");
  C=divZpx(A,B,&R);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)/B(x)=");
  escZpx(sal, C);
  fprintf(sal, "Residuo=");
  escZpx(sal, R);
  liberaZpx(&C);
  liberaZpx(&R);
  
  /* MCD */
  printf("Por calcular mcd(A(x),B(x)).\n");
  C=mcdZpx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "mcd(A(x),B(x))=");
  escZpx(sal, C);
  liberaZpx(&C); 
  
  /* Derivada */
  printf("Por calcular A'(x).\n");
  C=derivaZpx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A'(x)=");
  escZpx(sal, C);
  liberaZpx(&C);
  
  /* Integral indefinida*/
  printf("Por calcular la integral indefinida de A(x)\n");
  C=integraZpx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "Integral indefinida de A(x)=");
  escZpx(sal, C);
  liberaZpx(&C);
  
   /* Evaluar */
  printf("Por evaluar A(x).\n");
  a=leeZp(ent,p);
  r=evaluaZpx(A, a);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"A(");
  escZp(sal,a);
  fprintf(sal,") es:");
  escZp(sal,r);
  fprintf(sal,"\n");
  
  /* Integral definida */
  printf("Por calcular la integral definida de A(x).\n");
  a=leeZp(ent,p);
  b=leeZp(ent,p);
  r=integraDefZpx(A,a,b);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"El polinomio A(x) integrado de ");
  escZp(sal,a);
  fprintf(sal," a ");
  escZp(sal,b);
  fprintf(sal," es: ");
  escZp(sal,r);
  fprintf(sal,"\n");
  
	
	fclose(sal);
	fclose(ent);
	return 0;
}

Zp leeZp(FILE *f, int p){
  Zp a;
  a.p=p;
  
  fscanf(f,"%d",&a.n);
  a.n=simpZp(a);
  return a;
}

int escZp(FILE *f, Zp a){
  fprintf(f,"%d",a.n);
  return 0;
}

int simpZp(Zp d){
	
 d.n=((d.n%d.p)+d.p)%d.p;
 return d.n;	
}

Zp creaZp(int n, int p){
	Zp a;
	a.p=p;
	a.n=n;
	simpZp(a);
	
	return a;
}

Zp sumaZp(Zp a, Zp b){
	
  Zp r;
  r.p=a.p;
  r.n=a.n+b.n;
  r.n=simpZp(r);
  return r;	
}

Zp restaZp(Zp a, Zp b){
	
  Zp r;
  r.p=a.p;
  r.n=a.n-b.n;
  r.n=simpZp(r);
  return r;	
}

Zp prodZp(Zp a, Zp b){
	
  Zp r;
  r.p=a.p;
  r.n=a.n*b.n;
  r.n=simpZp(r);
  return r;	
}

Zp powZp(Zp a, int g){
	
  Zp ret={p:a.p};
  ret.n=pow(a.n,g);
  ret.n=simpZp(ret);
  return ret;
}

Zp invZp(Zp d){
	
   int r,q,s,s0,s_1,a,b,p;	
    a=d.n;
    b=d.p;	
    s0=0;
    s_1=1;
    while((r=a%b)!=0){
      q = a/b;
      a=b;
      b=r;
      s=s0;
      s0=s_1-q*s0;
      s_1=s;
    }
	d.n=s0;
    d.n=simpZp(d);
	s0=((s0%p)+p)%p;
    
    return d;
}

Zp divZp(Zp a, Zp b){
  Zp r;
  b=invZp(b);
  r=prodZp(a,b);
  return r;		
}

//funciones Zpx//
Zpx leeZpx(FILE *f, int p){
	Zpx ret;
  	int i;

  	printf("Por leer el grado\n");
  	fscanf(f,"%d", &(ret.g));

  if((ret.c=(Zp*)malloc((ret.g+1)*sizeof(Zp)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for (i=0; i<=ret.g; i++)
    ret.c[i]=leeZp(f,p);
    
    while(ret.g>=0 && ret.c[ret.g].n==0) ret.g--;
    if (ret.g<0){
    free(ret.c);
    ret.c = NULL;
  }

  return ret;
}
int escZpx(FILE *f, Zpx p){
	int i;
  
  if(p.g<0){
    fprintf(f, " 0\n\n");
    return 0;
  }
  if(p.g==0 && p.c[0].n!=0){
  	escZp(f, p.c[0]);
  	fprintf(f, "\n\n");
  	return 0;
  }

	if (p.c[0].n!=0) fprintf(f,"%+d ", p.c[0].n);
	if(p.c[1].n!=0){
  		if(p.c[1].n==1) fprintf(f,"+x");
    	else fprintf(f,"%+d x ", p.c[1].n);	
		}
		  
  	for(i=2; i<=p.g; i++){
	if (p.c[i].n!=0){
    	if(p.c[i].n==1) fprintf(f,"+x^%d ", i);
    	else fprintf(f,"%+d x^%d ", p.c[i].n, i);
	} 
  }
    
  fprintf(f,"\n\n");
  
  return 0;
}
Zpx sumaZpx(Zpx a, Zpx b){
	Zpx ret;
  int i, min;

  if (a.g<0){
    return copiaZpx(b);
  }
  if (b.g<0){
    return copiaZpx(a);
  }
  if (a.g<b.g){
    min = a.g;
    ret.g = b.g;
  }else{
    min = b.g;
    ret.g = a.g;
  }
  
  if((ret.c=(Zp*)malloc((ret.g+1)*sizeof(Zp)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  
  for (i=0; i<=min; i++) ret.c[i]=sumaZp(a.c[i],b.c[i]);
  if (a.g==min){
    for (; i<=ret.g; i++) ret.c[i]=b.c[i];
  }
  if (b.g==min){
    for (; i<=ret.g; i++) ret.c[i]=a.c[i];
  }
  
  while(ret.g>=0 && ret.c[ret.g].n==0) ret.g--;
  if (ret.g<0){
    free(ret.c);
    ret.c = NULL;
  }
  return ret;
}
Zpx restZpx(Zpx a, Zpx b){
	Zpx ret;
  int i, min;

  if (a.g<0){
    return copiaMenosZpx(b);
  }
  if (b.g<0){
    return copiaZpx(a);
  }
  if (a.g<b.g){
    min = a.g;
    ret.g = b.g;
  } else{
    min = b.g;
    ret.g = a.g;
  }
  
  if((ret.c=(Zp*)malloc((ret.g+1)*sizeof(Zp)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  
  for (i=0; i<=min; i++) ret.c[i]=restaZp(a.c[i],b.c[i]);
  if (a.g==min){
    for (; i<=ret.g; i++) ret.c[i]=creaZp(-b.c[i].n,b.c[i].p);
  }
  if (b.g==min){
    for (; i<=ret.g; i++) ret.c[i]=a.c[i];
  }
  
  while(ret.g>=0 && ret.c[ret.g].n==0) ret.g--;
  if (ret.g<0){
    free(ret.c);
    ret.c = NULL;
  }
  return ret;
}
Zpx multZpx(Zpx a, Zpx b){
	 Zpx ret;
  int i,j;
  
  if (a.g<0 || b.g<0){
  	ret.g=-1;	
    return ret;
  }
  
   ret.g=a.g+b.g; 
   
   if((ret.c=(Zp*)malloc((ret.g+1)*sizeof(Zp)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
   }
    
    for(i=0;i<=ret.g;i++) ret.c[i]=creaZp(0,a.c[i].p);
  
      for(i=0;i<=a.g;i++)
       for(j=0;j<=b.g; j++){
       	ret.c[i+j]=sumaZp(ret.c[i+j],prodZp(a.c[i],b.c[j]));
	   }
	for(i=0;i<=ret.g;i++) ret.c[i].n=simpZp(ret.c[i]);	
	
    return ret;
}
Zpx multMonoZpx(Zpx a, Zp b, int e){
	Zpx ret;
	int i;
	
	ret.g=a.g+e;
	
	if((ret.c=(Zp*)malloc((ret.g+1)*sizeof(Zp)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }

    for(i=0;i<=ret.g;i++) ret.c[i]=creaZp(0,a.c[i].p);
    for(i=e;i<=ret.g;i++) ret.c[i]=prodZp(a.c[i-e],b);
    
	return ret;  
}
Zpx divZpx(Zpx a, Zpx b, Zpx *res){
	Zpx ret,aux,aaux;
	int grad,i;
	
	aaux=copiaZpx(a);
	a=aaux; 
	
	ret.g=a.g-b.g;
    if((ret.c=(Zp*)malloc((ret.g+1)*sizeof(Zp)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
    
  for (i=0; i<=ret.g; i++) ret.c[i]=creaZp(0,a.c[i].p);

  do{
    grad=a.g-b.g;
    ret.c[grad] = divZp(a.c[a.g],b.c[b.g]);
    aux=multMonoZpx(b,ret.c[grad], grad);
    aaux=restZpx(a,aux);
    liberaZpx(&a);
    a=aaux;
    liberaZpx(res);
    *res=copiaZpx(a);
  }while(!esCeroZpx(*res) && (res->g>=b.g));
	
   return ret;	
}
Zpx mcdZpx(Zpx a, Zpx b){
	Zpx aaux,baux,r={g:-1,c:NULL};
	
	if(esCeroZpx(b)){
		return a;
	}
	
	aaux=copiaZpx(a);
	a=aaux;
	
	baux=copiaZpx(b);
	b=baux;
	
	divZpx(aaux,baux,&r);

	while(!esCeroZpx(r)){
	   divZpx(aaux,baux,&r);
	   aaux=copiaZpx(baux);
	   liberaZpx(&baux);
	   baux=copiaZpx(r);
	   liberaZpx(&r);}

	return baux;
}
Zpx derivaZpx(Zpx a){
	Zpx ret={g:a.g-1,c:NULL};
	int i;
	
	if((ret.c=(Zp*)malloc((ret.g+1)*sizeof(Zp)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
	
	for(i=0;i<=ret.g;i++){
		ret.c[i].p=a.c[i].p;
		ret.c[i].n=(i+1)*a.c[i+1].n;
		ret.c[i].n=simpZp(ret.c[i]);
	}
	
	return ret;
}


Zpx integraZpx(Zpx a){
	Zpx ret={g:a.g+1,c:NULL};
	int i,p;
	Zp izp;
	
	if((ret.c=(Zp*)malloc((ret.g+1)*sizeof(Zp)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
    
    p=a.c[0].p;
	    
    ret.c[0]=creaZp(0,a.c[0].n);
    if(ret.g<p-1){
    	for(i=1;i<=ret.g;i++){
    	ret.c[i].p=a.c[i-1].p;
    	izp=creaZp(i,a.c[i-1].p);
		ret.c[i]=divZp(a.c[i-1], izp);
		}
	}else{
		for(i=1;i<=ret.g;i++){
			if(i==p){
				ret.c[i].p=a.c[i-1].p;
				ret.c[i].n=0;
				
			}else{
				ret.c[i].p=a.c[i-1].p;
    			izp=creaZp(i,a.c[i-1].p);
				ret.c[i]=divZp(a.c[i-1], izp);
			}
		}
	}
	
	return ret;
}
Zp evaluaZpx(Zpx a, Zp d){
	Zp r={n:0, p:d.p};
	int i;

	for(i=0;i<=a.g;i++) r=sumaZp(r, prodZp(a.c[i],powZp(d,i)));
	r.n=simpZp(r);
	return r;
}
Zp integraDefZpx(Zpx p, Zp a, Zp b){
	Zpx P={g:p.g+1,c:NULL};
	Zp Pb,Pa,r;
	
	P=integraZpx(p);
	Pb=evaluaZpx(P,b);
	Pa=evaluaZpx(P,a);
	r=restaZp(Pb,Pa);	
	return r;
} 

int esCeroZpx(Zpx a){
	return a.g<0;
}
Zpx copiaZpx(Zpx a){
	Zpx ret={g:a.g,c:NULL};
  int i;
  
  if (ret.g<0){
    ret.c=NULL;
    return ret;
  }
  
  if((ret.c=(Zp*)malloc((ret.g+1)*sizeof(Zp)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
  
  for(i=0;i<=ret.g;i++) ret.c[i]=a.c[i];
  
  return ret;
}
Zpx copiaMenosZpx(Zpx a){
	Zpx ret={g:a.g,c:NULL};
  int i;
  
  if((ret.c=(Zp*)malloc((ret.g+1)*sizeof(Zp)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
  
  for(i=0;i<=ret.g;i++) ret.c[i]=creaZp(-a.c[i].n,a.c[i].p);
  
  return ret;
}
int liberaZpx(Zpx *a){
	if(a->c!=NULL) free(a->c);
  a->g=-1;
  a->c=NULL;
  return 0;	
}
