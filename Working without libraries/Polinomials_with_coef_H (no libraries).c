#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> 
#include<string.h> 

typedef struct H{
double r,i,j,k;	
}H;

typedef struct Hx{
int g;
H *c;	
}Hx;

#define EPSILON 1e-5

// funciones H //
H leeH(FILE *f);
int escH(FILE *f, H x); 
int esCeroH(H a); 
int igualH(H a, H b);     
H creaH(double rea, double im, double jim, double kim);
H sumaH(H a, H b);
H restaH(H a, H b);
H prodH(H x, H y);
H invH(H a);
H divH(H a, H b);

// funciones Hx //
Hx leeHx(FILE *f);
int escHx(FILE *f, Hx p);
Hx sumaHx(Hx a, Hx b);
Hx restHx(Hx a, Hx b);
Hx multHx(Hx a, Hx b);
Hx multMonoHx(Hx a, H c, int e);
Hx divHx(Hx a, Hx b, Hx *res);
Hx mcdHx(Hx a, Hx b);
Hx derivaHx(Hx a);
Hx integraHx(Hx a);
H evaluaHx(Hx a, H d);
H integraDefHx(Hx p, H a, H b);
int esCeroHx(Hx a);
Hx copiaHx(Hx a);
Hx copiaMenosHx(Hx a);
int  liberaHx(Hx *a);



int main(int argc, char *argv[]) {
	FILE *ent, *sal;
	char *noment="poliH.txt", *nomsal="resultado.txt";
	H a,b,r;
	Hx A,B,C,R={g:-1,c:NULL};
	
	printf("Por leer el archivo %s.\n", noment);
	ent=fopen(noment,"rt");
	if(ent==NULL){
    int mi_error=errno; 
	printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	mi_error, strerror(mi_error));
    return -1;
	}
	printf("Por leer el polinomio A(x).\n");
	A=leeHx(ent);

	printf("Por leer el polinomio B(x).\n");
	B=leeHx(ent);
  
   /* Suma */
  printf("Por calcular A(x)+B(x).\n");
  C=sumaHx(A,B); 
  
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
  escHx(sal, C);
  liberaHx(&C); 
  
  /* Resta */
  printf("Por calcular A(x)-B(x).\n");
  C=restHx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)-B(x)=");
  escHx(sal, C);
  liberaHx(&C);
  
  /* Producto */
  printf("Por calcular A(x)B(x).\n");
  C=multHx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)*B(x)=");
  escHx(sal, C);
  liberaHx(&C);
  
   /* Cociente y residuo */
  printf("Por calcular A(x)/B(x) y R(x).\n");
  C=divHx(A,B,&R);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)/B(x)=");
  escHx(sal, C);
  fprintf(sal, "Residuo=");
  escHx(sal, R); 
  liberaHx(&C);
  liberaHx(&R); 
  
  /* MCD 
  printf("Por calcular mcd(A(x),B(x)).\n");
  C=mcdHx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "mcd(A(x),B(x))=");
  escHx(sal, C);
  liberaHx(&C); */
  
   /* Derivada */
  printf("Por calcular A'(x).\n");
  C=derivaHx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A'(x)=");
  escHx(sal, C);
  liberaHx(&C);
  
  /* Integral indefinida*/
  printf("Por calcular la integral indefinida de A(x)\n");
  C=integraHx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "Integral indefinida de A(x)=");
  escHx(sal, C);
  liberaHx(&C);
  
  /* Evaluar */
  printf("Por evaluar A(x).\n");
  a=leeH(ent);
  r=evaluaHx(A, a);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"A(");
  escH(sal,a);
  fprintf(sal,") es:");
  escH(sal,r);
  fprintf(sal,"\n");
  
  
  /* Integral definida */
  printf("Por calcular la integral definida de A(x).\n");
  a=leeH(ent);
  b=leeH(ent);
  r=integraDefHx(A,a,b);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"El polinomio A(x) integrado de ");
  escH(sal,a);
  fprintf(sal," a ");
  escH(sal,b);
  fprintf(sal," es: ");
  escH(sal,r);
  fprintf(sal,"\n");
  
  
	liberaHx(&A); 
	liberaHx(&B);
	fclose(sal);
	fclose(ent);
	system("PAUSE");
	return 0;
}

// funciones H //
H leeH(FILE *f){
	H a;

   fscanf(f,"%lg%lg%lg%lg",&a.r,&a.i,&a.j,&a.k);	
  
  return a;
}
int escH(FILE *f, H x){
	if(esCeroH(x)){
		fprintf(f,"0");
	 	return 0;	
	}
	
	if(x.r==0.0);
	else fprintf(f,"%lg",x.r);
    if(x.i==0.0);
    else {
    if(x.i==1.0) fprintf(f,"+i");
    else{
    	if(x.i==-1.0) fprintf(f,"-i");
    	else fprintf(f,"%+lgi",x.i);
		}
	}
    if(x.j==0.0);
	else {
    	if(x.j==1.0) fprintf(f,"+j");
    	else{
    	    if(x.j==-1.0) fprintf(f,"-j");
    	    else fprintf(f,"%+lgj",x.j);
    	    }
	    }
    if(x.k==0.0);
    else{
    	if(x.k==1.0) fprintf(f,"+k");
    	else{
			if(x.k==-1.0) fprintf(f,"-k");
    	    else fprintf(f,"%+lgk",x.k);
			} 
	    }
	return 0;	 
} 
int esCeroH(H a){
	if(a.r==0.0 && a.i==0.0 && a.j==0.0 && a.k==0.0) return 1;
	else return 0;
} 
int igualH(H a, H b){
	if(a.r==b.r && a.i==b.i && a.j==b.j && a.k==b.k) return 1;
	else return 0;
}     
H creaH(double rea, double im, double jim, double kim){
	H ret={r:rea, i:im, j:jim, k: kim};
	return ret;
}
H sumaH(H a, H b){
	H ret={r:a.r+b.r, i:a.i+b.i, j:a.j+b.j, k:a.k+b.k}; 
	return ret;
}
H restaH(H a, H b){
	H ret={r:a.r-b.r, i:a.i-b.i, j:a.j-b.j, k:a.k-b.k}; 
	return ret;
}
H prodH(H x, H y){
	H ret={ x.r*y.r - x.i*y.i - x.j*y.j - x.k*y.k,
    		x.r*y.i + x.i*y.r + x.j*y.k - x.k*y.j,
    		x.r*y.j - x.i*y.k + x.j*y.r + x.k*y.i,
    		x.r*y.k + x.i*y.j - x.j*y.i + x.k*y.r};

  if (-EPSILON <= ret.r && ret.r <= EPSILON) ret.r = 0.0;
  if (-EPSILON <= ret.i && ret.i <= EPSILON) ret.i = 0.0;
  if (-EPSILON <= ret.j && ret.j <= EPSILON) ret.j = 0.0;
  if (-EPSILON <= ret.k && ret.k <= EPSILON) ret.k = 0.0;

  return ret;
}
H invH(H a){
	double norm2=a.r*a.r+a.i*a.i+a.j*a.j+a.k*a.k;
  H ret={a.r, -a.i, -a.j, -a.k};

  if (norm2==0.0) return a;
  ret.r/=norm2;
  ret.i/=norm2;
  ret.j/=norm2;
  ret.k/=norm2;

  if (-EPSILON <= ret.r && ret.r <= EPSILON) ret.r = 0.0;
  if (-EPSILON <= ret.i && ret.i <= EPSILON) ret.i = 0.0;
  if (-EPSILON <= ret.j && ret.j <= EPSILON) ret.j = 0.0;
  if (-EPSILON <= ret.k && ret.k <= EPSILON) ret.k = 0.0;

  return ret;
}

H divH(H a, H b){
	H r;
	
	return prodH(a, invH(b)); 
}

// funciones Hx //
Hx leeHx(FILE *f){
  Hx ret;
  int i;

  printf("Por leer el grado\n");
  fscanf(f,"%d", &(ret.g));

  if((ret.c=(H*)malloc((ret.g+1)*sizeof(H)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for (i=0; i<=ret.g; i++)
    ret.c[i]=leeH(f);

  return ret;
}
int escHx(FILE *f, Hx p){
	int i;
	H unit={r:1.0,i:0.0,j:0.0,k:0.0};
  
  if(p.g<0){
    fprintf(f, "0\n\n");
    return 0;
  }
  if(p.g==0){
  	escH(f, p.c[0]);
    fprintf(f, "\n\n");
    return 0;
  }

	if(!esCeroH(p.c[0])){
		escH(f, p.c[0]);
		fprintf(f, "+");
	} 
	if(!esCeroH(p.c[1])){
  		if(igualH(p.c[1],unit)){
  			fprintf(f,"x");
  			if(p.g>1) fprintf(f, "+");
		  }else{
    		fprintf(f, "(");
			escH(f,p.c[1]);
			fprintf(f, ")");
    		fprintf(f,"x ");
    		if(p.g>1) fprintf(f, "+");
			} 
		}
		  
  	for(i=2; i<=p.g; i++){
	  	if (!esCeroH(p.c[i])){
    	if(igualH(p.c[i],unit)){
    		fprintf(f,"x^%d ", i);
    		if(i<p.g) fprintf(f, "+");
		} 
    	else{
    		fprintf(f, "(");
			escH(f,p.c[i]);
			fprintf(f, ")");
    		fprintf(f,"x^%d ", i);
    		if(i<p.g) fprintf(f, "+");
			} 
		} 
	}

  fprintf(f,"\n\n");
  
  return 0;
}
Hx sumaHx(Hx a, Hx b){
	Hx ret;
  int i, min;

  if (a.g<0){
    return copiaHx(b);
  }
  if (b.g<0){
    return copiaHx(a);
  }
  if (a.g<b.g){
    min = a.g;
    ret.g = b.g;
  } else{
    min = b.g;
    ret.g = a.g;
  }
  
  if((ret.c=(H*)malloc((ret.g+1)*sizeof(H)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  
  for (i=0; i<=min; i++) ret.c[i]=sumaH(a.c[i],b.c[i]);
  if (a.g==min){
    for (; i<=ret.g; i++) ret.c[i]=b.c[i];
  }
  if (b.g==min){
    for (; i<=ret.g; i++) ret.c[i]=a.c[i];
  }
  
  while(ret.g>=0 && esCeroH(ret.c[ret.g])) ret.g--;
  if (ret.g<0){
    free(ret.c);
    ret.c = NULL;
  }
  return ret;	
}
Hx restHx(Hx a, Hx b){
	Hx ret;
  int i, min;

  if (a.g<0){
    return copiaMenosHx(b);
  }
  if (b.g<0){
    return copiaHx(a);
  }
  if (a.g<b.g){
    min = a.g;
    ret.g = b.g;
  } else{
    min = b.g;
    ret.g = a.g;
  }
  
  if((ret.c=(H*)malloc((ret.g+1)*sizeof(H)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  
  for (i=0; i<=min; i++) ret.c[i]=restaH(a.c[i],b.c[i]);
  if (a.g==min){
    for (; i<=ret.g; i++){
    	printf("a.g");
  	ret.c[i].r=-b.c[i].r;
  	ret.c[i].i=-b.c[i].i;
  	ret.c[i].j=-b.c[i].j;
  	ret.c[i].k=-b.c[i].k;
	  } 
	}else{
  	printf("b.g");
    for (; i<=ret.g; i++){
    	ret.c[i].r=a.c[i].r;
    	ret.c[i].i=a.c[i].i;
    	ret.c[i].j=a.c[i].j;
    	ret.c[i].k=a.c[i].k;
	}
  }
  
  while(ret.g>=0 && esCeroH(ret.c[ret.g])) ret.g--;
  if (ret.g<0){
    free(ret.c);
    ret.c = NULL;
  }
  return ret;
}
Hx multHx(Hx a, Hx b){
	Hx ret;
  int i,j;
  
  if (a.g<0 || b.g<0){
  	ret.g=-1;	
    return ret;
  }
  
   ret.g=a.g+b.g; 
   
   if((ret.c=(H*)malloc((ret.g+1)*sizeof(H)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
   }
    
    for(i=0;i<=ret.g;i++){
      ret.c[i].r=0.0;
	  ret.c[i].i=0.0;
	  ret.c[i].j=0.0;
	  ret.c[i].k=0.0;	
	} 
  
      for(i=0;i<=a.g;i++)
       for(j=0;j<=b.g; j++)	
    	ret.c[i+j]=sumaH(ret.c[i+j],prodH(a.c[i],b.c[j]));
	
    return ret;
}
Hx multMonoHx(Hx a, H b, int e){
	Hx ret;
	int i;
	
	ret.g=a.g+e;
	
	if((ret.c=(H*)malloc((ret.g+1)*sizeof(H)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }

    for(i=0;i<=ret.g;i++){
      ret.c[i].r=0.0;
	  ret.c[i].i=0.0;
	  ret.c[i].j=0.0;
	  ret.c[i].k=0.0;	
	} 
    for(i=e;i<=ret.g;i++) ret.c[i]=prodH(b,a.c[i-e]);
    
	return ret;  
}
Hx divHx(Hx a, Hx b, Hx *res){
	Hx ret,aux,aaux;
	int grad,i;
	
	aaux=copiaHx(a);
	a=aaux; 
	
	ret.g=a.g-b.g;
    if((ret.c=(H*)malloc((ret.g+1)*sizeof(H)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
    
  for (i=0; i<=ret.g; i++){
  	ret.c[i].r=0.0;
  	ret.c[i].i=0.0;
  	ret.c[i].j=0.0;
  	ret.c[i].k=0.0;
  } 

  do{
    grad=a.g-b.g;
    printf("%d\n",grad);
    ret.c[grad]=divH(a.c[a.g],b.c[b.g]);
    printf("%lg %lgi %lgj %lgk\n",ret.c[grad].r,ret.c[grad].i,ret.c[grad].j,ret.c[grad].k);
    aux=multMonoHx(b, ret.c[grad], grad);
    for(i=0;i<=aux.g;i++)
	printf("aux  (%lg %lgi %lgj %lgk)x^%d\n",aux.c[i].r,aux.c[i].i,aux.c[i].j,aux.c[i].k,i);
	printf("%d\n",aux.g);
    aaux=restHx(a,aux);
    for(i=0;i<=aux.g;i++)
    printf("aaux (%lg %lgi %lgj %lgk)x^%d\n",aaux.c[i].r,aaux.c[i].i,aaux.c[i].j,aaux.c[i].k,i);
	printf("%d\n",aaux.g);
    liberaHx(&a);
    liberaHx(&aux);
    a=aaux;
    liberaHx(res);
    *res=copiaHx(a);
    
  }while(!esCeroHx(*res) && (res->g>=b.g));
	
   return ret;
}
Hx mcdHx(Hx a, Hx b){
	Hx aaux,baux,r={g:-1,c:NULL};
	
	if(esCeroHx(b)){
		return a;
	}
	
	aaux=copiaHx(a);
	a=aaux;
	
	baux=copiaHx(b);
	b=baux;
	
	divHx(a,b,&r);

	while(!esCeroHx(r)){
	   divHx(a,b,&r);
	   liberaHx(&a);
	   a=copiaHx(b);
	   liberaHx(&b);
	   b=copiaHx(r);
	   liberaHx(&r);}
	return b;
}
Hx derivaHx(Hx a){
	Hx ret={g:a.g-1,c:NULL};
	int i;
	
	if((ret.c=(H*)malloc((ret.g+1)*sizeof(H)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
	
	for(i=0;i<=ret.g;i++){
	  ret.c[i].r=(i+1)*a.c[i+1].r;
	  ret.c[i].i=(i+1)*a.c[i+1].i;
	  ret.c[i].j=(i+1)*a.c[i+1].j;	
	  ret.c[i].k=(i+1)*a.c[i+1].k;			
	} 
	
	return ret;
}
Hx integraHx(Hx a){
	Hx ret={g:a.g+1,c:NULL};
	int i;
	
	if((ret.c=(H*)malloc((ret.g+1)*sizeof(H)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
    
    ret.c[0].r=0.0;
    ret.c[0].i=0.0;
    ret.c[0].j=0.0;
    ret.c[0].k=0.0;
    
    for(i=1;i<=ret.g;i++){
     ret.c[i].r=a.c[i-1].r/i;
	 ret.c[i].i=a.c[i-1].i/i;
	 ret.c[i].j=a.c[i-1].j/i;
	 ret.c[i].k=a.c[i-1].k/i;	
	} 
	
	return ret;
}
H evaluaHx(Hx a, H d){
	H r={r:0.0, i:0.0, j:0.0, k:0.0};
	int i;

	for(i=a.g;i>0;i--) r=prodH(sumaH(a.c[i],r),d);
	r=sumaH(r,a.c[0]);
	return r;
}
H integraDefHx(Hx p, H a, H b){
	Hx P={g:p.g+1,c:NULL};
	H Pb,Pa,r;
	
	P=integraHx(p);
	Pb=evaluaHx(P,b);
	Pa=evaluaHx(P,a);
	r=restaH(Pb,Pa);	
	return r;
}
int esCeroHx(Hx a){
	return a.g <0;
}
Hx copiaHx(Hx a){
	Hx ret;
  int i;

  ret.g = a.g;
  if (ret.g<0){
    ret.c=NULL;
    return ret;
  }
  if((ret.c=(H*)malloc((ret.g+1)*sizeof(H)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }

  for(i=0; i<=ret.g; i++){
  	ret.c[i].r=a.c[i].r;
  	ret.c[i].i=a.c[i].i;
  	ret.c[i].j=a.c[i].j;
  	ret.c[i].k=a.c[i].k;
  }

  return ret;
}
Hx copiaMenosHx(Hx a){
	Hx ret;
  int i;

  ret.g = a.g;
  if (ret.g<0){
    ret.c=NULL;
    return ret;
  }
  if((ret.c=(H*)malloc((ret.g+1)*sizeof(H)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for(i=0; i<=ret.g; i++){
  	ret.c[i].r=-a.c[i].r;
  	ret.c[i].i=-a.c[i].i;
  	ret.c[i].j=-a.c[i].j;
  	ret.c[i].k=-a.c[i].k;
  }

  return ret;
}
int  liberaHx(Hx *a){
	if(a->c!=NULL) free(a->c);
	a->g=-1;
	a->c=NULL;
	return 0;	
}

