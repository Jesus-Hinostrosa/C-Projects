#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> 
#include<string.h> 

typedef struct Q{
  int p, q;        
}Q;

typedef struct Qx{
  int g;
  Q *c;
}Qx;

//funciones Q//
Q leeQ(FILE *f);
int escQ(FILE *f, Q a); 
int mcd(int a, int b);
int esCeroQ(Q a); 
int igualQ(Q a, Q b);  
Q simplificaQ(Q a);    
Q creaQ(int num, int den);
Q sumaQ(Q a, Q b);
Q restaQ(Q a, Q b);
Q prodQ(Q a, Q b);
Q powQ(Q a, int g);
Q divQ(Q a, Q b);

//funciones Qx//
Qx leeQx(FILE *f);
int escQx(FILE *f, Qx p);
Qx sumaQx(Qx a, Qx b);
Qx restQx(Qx a, Qx b);
Qx multQx(Qx a, Qx b);
Qx multMonoQx(Qx a, Q c, int e);
Qx divQx(Qx a, Qx b, Qx *r);
Qx mcdQx(Qx a, Qx b);
Qx derivaQx(Qx a);
Qx integraQx(Qx a);
Q evaluaQx(Qx a, Q d);
Q integraDefQx(Qx p, Q a, Q b);
int esCeroQx(Qx a);
Qx copiaQx(Qx a);
Qx copiaMenosQx(Qx a);
int  liberaQx(Qx *a);

int main(int argc, char *argv[]) {
	FILE *ent, *sal;
  char *noment="poliQ.txt", *nomsal="resultado.txt";
  Qx A, B, C, R={c:NULL, g:-1};
  int m, n, i;
  Q  r={p:0,q:1}, a={p:0,q:1}, b={p:0,q:1};
  
  printf("Por leer el archivo %s.\n", noment);
  ent=fopen(noment,"rt");
  if(ent==NULL){
    int mi_error=errno; 
	printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	mi_error, strerror(mi_error));
    return -1;
  }
  printf("Por leer el polinomio A(x).\n");
   A=leeQx(ent);

  printf("Por leer el polinomio B(x).\n");
  B=leeQx(ent);
  
  /* Suma */
  printf("Por calcular A(x)+B(x).\n");
  C=sumaQx(A,B);
  
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
  escQx(sal, C);
  liberaQx(&C);
  
  /* Resta */
  printf("Por calcular A(x)-B(x).\n");
  C=restQx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)-B(x)=");
  escQx(sal, C);
  liberaQx(&C);
  
  /* Producto */
  printf("Por calcular A(x)B(x).\n");
  C=multQx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)*B(x)=");
  escQx(sal, C);
  liberaQx(&C);
  
  /* Cociente y residuo */
  printf("Por calcular A(x)/B(x) y R(x).\n");
  C=divQx(A,B,&R);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)/B(x)=");
  escQx(sal, C);
  fprintf(sal, "Residuo=");
  escQx(sal, R);
  liberaQx(&C);
  liberaQx(&R);
  
  /* MCD */
  printf("Por calcular mcd(A(x),B(x)).\n");
  C=mcdQx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "mcd(A(x),B(x))=");
  escQx(sal, C);
  liberaQx(&C); 
  
  /* Derivada */
  printf("Por calcular A'(x).\n");
  C=derivaQx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A'(x)=");
  escQx(sal, C);
  liberaQx(&C);
  
  /* Integral indefinida*/
  printf("Por calcular la integral indefinida de A(x)\n");
  C=integraQx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "Integral indefinida de A(x)=");
  escQx(sal, C);
  liberaQx(&C);
  
  /* Evaluar */
  printf("Por evaluar A(x).\n");
  a=leeQ(ent);
  r=evaluaQx(A, a);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"A(");
  escQ(sal,a);
  fprintf(sal,") es:");
  escQ(sal,r);
  fprintf(sal,"\n");
  
  
  /* Integral definida */
  printf("Por calcular la integral definida de A(x).\n");
  a=leeQ(ent);
  b=leeQ(ent);
  r=integraDefQx(A,a,b);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal,"El polinomio A(x) integrado de ");
  escQ(sal,a);
  fprintf(sal," a ");
  escQ(sal,b);
  fprintf(sal," es: ");
  escQ(sal,r);
  fprintf(sal,"\n");
  
  fclose(sal);
  fclose(ent);
  system("PAUSE");
	return 0;
}

//funciones Q//
Q leeQ(FILE *f){
	Q a;

   fscanf(f,"%d%d",&a.p,&a.q);
   a=simplificaQ(a);	
  
  return a;
}
int escQ(FILE *f, Q a){

  fprintf(f, "%+d", a.p);
  if (a.q!= 1) fprintf(f, "/%d", a.q);
  
  return 0;
} 
int mcd(int a, int b){
	int r;             

  if (a < 0) a=-a;
  if (b < 0) b=-b;
  if (b == 0) return a;

  while ((r=a%b) != 0){
    a = b;             
    b = r;             
  }                    

  return b;
}   
int esCeroQ(Q a){
	if(a.p==0) return 1;
	else return 0;
}

int igualQ(Q a, Q b){
	if(a.p==b.p	&& a.q==b.q) return 1;
	else return 0;
}
Q simplificaQ(Q a){
	int d;
  Q regreso;

  regreso = a;
  d = mcd (a.p, a.q);
  if (d>1){            
    regreso.p /= d;         
    regreso.q /= d;         
  }                    
  if (regreso.q < 0){       
    regreso.p *= -1;        
    regreso.q *= -1;        
  }

  return regreso;
}    
Q creaQ(int num, int den){
	Q r = {num, den};

  r=simplificaQ(r);

  return r;
}
Q sumaQ(Q a, Q b){
	Q r={p:a.p*b.q + a.q*b.p, q:a.q*b.q};           
	
  return simplificaQ(r);
}
Q restaQ(Q a, Q b){
	Q r={p:a.p*b.q - a.q*b.p, q:a.q*b.q};           

  return simplificaQ(r);
}
Q prodQ(Q a, Q b){
	Q r={a.p*b.p, a.q*b.q};           

  return simplificaQ(r);
}
Q powQ(Q a, int g){
	Q ret={p:0,q:1};
  
  ret.p=pow(a.p,g);
  ret.q=pow(a.q,g);
  simplificaQ(ret);
  
  return ret;
}
Q divQ(Q a, Q b){
	Q r={p:a.p*b.q, q:a.q*b.p};           
	
  return simplificaQ(r);
}

//funciones Qx//
Qx leeQx(FILE *f){
  Qx ret;
  int i;

  printf("Por leer el grado\n");
  fscanf(f,"%d", &(ret.g));

  if((ret.c=(Q*)malloc((ret.g+1)*sizeof(Q)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for (i=0; i<=ret.g; i++)
    ret.c[i]=leeQ(f);

  return ret;
}
int escQx(FILE *f, Qx p){
	int i;
	Q unit={p:1,q:1};
  
  if(p.g<0){
    fprintf(f, " 0\n\n");
    return 0;
  }
  
  if(p.g==0 && p.c[0].p!=0){
  	escQ(f, p.c[0]);
  	fprintf(f, "\n\n");
  	return 0;
  }
	if (!esCeroQ(p.c[0])) escQ(f, p.c[0]);
	if(!esCeroQ(p.c[1])){
  		if(igualQ(p.c[1],unit)) fprintf(f,"+x");
    	else{
    		escQ(f,p.c[1]);
    		fprintf(f,"x ");	
			} 
		}
		  
  	for(i=2; i<=p.g; i++){
	if (!esCeroQ(p.c[i])){
    	if(igualQ(p.c[i],unit)) fprintf(f,"+x^%d ", i);
    	else{
    		escQ(f,p.c[i]);
    		fprintf(f,"x^%d ", i);
		} 
	} 
  }
    
  fprintf(f,"\n\n");
  
  return 0;
}
Qx sumaQx(Qx a, Qx b){
  Qx ret;
  int i, min;

  if (a.g<0){
    return copiaQx(b);
  }
  if (b.g<0){
    return copiaQx(a);
  }
  if (a.g<b.g){
    min = a.g;
    ret.g = b.g;
  } else{
    min = b.g;
    ret.g = a.g;
  }
  if((ret.c=(Q*)malloc((ret.g+1)*sizeof(Q)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  for (i=0; i<=min; i++) ret.c[i]=sumaQ(a.c[i],b.c[i]);
  if (a.g==min){
    for (; i<=ret.g; i++) ret.c[i]=b.c[i];
  }
  if (b.g==min){
    for (; i<=ret.g; i++) ret.c[i]=a.c[i];
  }
  while(ret.g>=0 && esCeroQ(ret.c[ret.g])) ret.g--;
  if (ret.g<0){
    free(ret.c);
    ret.c = NULL;
  }
  return ret;
}
Qx restQx(Qx a, Qx b){
	Qx ret;
  int i, min;
  Q neg={p:-1,q:1};

  if (a.g<0){
    return copiaMenosQx(b);
  }
  if (b.g<0){
    return copiaQx(a);
  }
  if (a.g<b.g){
    min = a.g;
    ret.g = b.g;
  } else{
    min = b.g;
    ret.g = a.g;
  }
  if((ret.c=(Q*)malloc((ret.g+1)*sizeof(Q)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  for (i=0; i<=min; i++) ret.c[i]=restaQ(a.c[i],b.c[i]);
  if (a.g==min){
    for (; i<=ret.g; i++) ret.c[i]=prodQ(neg,b.c[i]);
  }
  if (b.g==min){
    for (; i<=ret.g; i++) ret.c[i]=a.c[i];
  }
  while(ret.g>=0 && esCeroQ(ret.c[ret.g])) ret.g--;
  if (ret.g<0){
    free(ret.c);
    ret.c = NULL;
  }
  return ret;
}
Qx multQx(Qx a, Qx b){
	int i, j;
  Qx ret;
  Q ceroQ={p:0,q:1};

  ret.g=a.g+b.g;
  if((ret.c=(Q*)malloc((ret.g+1)*sizeof(Q)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  for (i=0; i<=ret.g; i++) ret.c[i]=ceroQ;
  for (i=0; i<=a.g; i++)
    for(j=0; j<=b.g; j++)
      ret.c[i+j]=sumaQ(ret.c[i+j],prodQ(a.c[i],b.c[j]));

  return ret;
}
Qx multMonoQx(Qx a, Q c, int e){
	int i;
  Qx ret;
  Q ceroQ={p:0,q:1};

  ret.g=a.g+e;
  if((ret.c=(Q*)malloc((ret.g+1)*sizeof(Q)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for (i=0; i<=ret.g; i++) ret.c[i]=ceroQ;
  for (i=e; i<=ret.g; i++) ret.c[i]=prodQ(a.c[i-e],c);

  return ret;
}
Qx divQx(Qx a, Qx b, Qx *r){
	Qx q, aux, a_aux;
  double coef;
  int grad, i;
  Q ceroQ={p:0,q:1};
  
  a_aux= copiaQx(a);
  a=a_aux;

  if (a.g<b.g){
    q.g=-1;
    q.c=NULL;
    *r = copiaQx(a);

    return q;
  }

  q.g=a.g-b.g;
  if((q.c=(Q*)malloc((q.g+1)*sizeof(Q)))==NULL){
    printf("error al generar espacio.\n");
    q.g = -1;
    return q;
  }
  for (i=0; i<=q.g; i++) q.c[i]=ceroQ;

  do{
    grad=a.g-b.g;
    q.c[grad] =divQ( a.c[a.g],b.c[b.g]);
    aux = multMonoQx(b, q.c[grad], grad);
    a_aux = restQx(a, aux);
    liberaQx(&a);
    liberaQx(&aux);
    a = a_aux;
  liberaQx(r);
    *r=copiaQx(a);
  }while(!esCeroQx(*r) && (r->g>=b.g));
  
  return q;
}
Qx mcdQx(Qx a, Qx b){
	Qx aaux,baux,r={g:-1,c:NULL};
	int i;
	
	if(esCeroQx(b)){
		return a;
	}
	
	aaux=copiaQx(a);
	a=aaux;
	
	baux=copiaQx(b);
	b=baux;
	

	while(!esCeroQx(r)){
	   divQx(aaux,baux,&r);
	   aaux=copiaQx(baux);
	   liberaQx(&baux);
	   baux=copiaQx(r);
	   liberaQx(&r);
	   }
	   
	return baux;
}
Qx derivaQx(Qx a){
	Qx ret={g:a.g-1,c:NULL};
	int i;
	
	if((ret.c=(Q*)malloc((ret.g+1)*sizeof(Q)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
	
	for(i=0;i<=ret.g;i++){
		ret.c[i].p=(i+1)*a.c[i+1].p;
		ret.c[i].q=a.c[i+1].q;
	}
	
	return ret;
}
Qx integraQx(Qx a){
	Qx ret={g:a.g+1,c:NULL};
	int i;
	Q ceroQ={p:0,q:1};
	
	if((ret.c=(Q*)malloc((ret.g+1)*sizeof(Q)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
    }
    
    ret.c[0]=ceroQ;
    for(i=1;i<=ret.g;i++){
    	ret.c[i].p=a.c[i-1].p;
		ret.c[i].q=a.c[i-1].q*(i);
	}
	
	return ret;
}
Q evaluaQx(Qx a, Q d){
	Q r={p:0, q:1};
	int i;

	for(i=0;i<=a.g;i++) r=sumaQ(r, prodQ(a.c[i],powQ(d,i)));
	return r;
}
Q integraDefQx(Qx p, Q a, Q b){
	Qx P={g:p.g+1,c:NULL};
	Q Pb,Pa,r;
	
	P=integraQx(p);
	Pb=evaluaQx(P,b);
	Pa=evaluaQx(P,a);
	r=restaQ(Pb,Pa);	
	return r;
}
int esCeroQx(Qx a){
	return a.g <0;
}
Qx copiaQx(Qx a){
	Qx ret;
  int i;

  ret.g = a.g;
  if (ret.g<0){
    ret.c=NULL;
    return ret;
  }
  if((ret.c=(Q*)malloc((ret.g+1)*sizeof(Q)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for(i=0; i<=ret.g; i++){
  	ret.c[i].p=a.c[i].p;
  	ret.c[i].q=a.c[i].q;
  }

  return ret;
}
Qx copiaMenosQx(Qx a){
	Qx ret;
  int i;

  ret.g = a.g;
  if (ret.g<0){
    ret.c=NULL;
    return ret;
  }
  if((ret.c=(Q*)malloc((ret.g+1)*sizeof(Q)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for(i=0; i<=ret.g; i++){
  	ret.c[i].p=-a.c[i].p;
  	ret.c[i].q=-a.c[i].q;
  }

  return ret;
}
int  liberaQx(Qx *a){
	if(a->c!=NULL) free(a->c);
  a->g=-1;
  a->c=NULL;
  return 0;	
}
