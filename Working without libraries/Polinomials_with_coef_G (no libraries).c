#include <stdio.h>   
#include <stdlib.h>   
#include <math.h>  
#include <string.h>  

typedef struct _Gaussianos_{
int  r,i; 
}G;  
typedef struct Gx{
   int g;
   G *c;
}Gx;

// funciones de G //
G leeG(FILE *f);
int escG(FILE *f, G a); 
int esCeroG(G a); 
int igualG(G a, G b);     
G creaG(int r, int i);
G sumaG(G a, G b);
G restaG(G a, G b);
G prodG(G a, G b);

// funciones de poliG //
Gx leeGx(FILE *f);
int escGx(FILE *f, Gx p);
Gx sumaGx(Gx a, Gx b);
Gx restGx(Gx a, Gx b);
Gx multGx(Gx a, Gx b);
Gx derivaGx(Gx a);
int esCeroGx(Gx a);
Gx copiaGx(Gx a);
Gx copiaMenosGx(Gx a);
int  liberaGx(Gx *a);

int main(int argc, char *argv[]) {
	FILE *ent, *sal;
	char *noment="poliG.txt", *nomsal="resultado.txt";
	Gx A, B, C, R={c:NULL, g:-1};
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
   A=leeGx(ent);

  printf("Por leer el polinomio B(x).\n");
  B=leeGx(ent);
  
  /* Suma */
  printf("Por calcular A(x)+B(x).\n");
  C=sumaGx(A,B);
  
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
  escGx(sal, C);
  liberaGx(&C); 
  
  /* Resta */
  printf("Por calcular A(x)-B(x).\n");
  C=restGx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)-B(x)=");
  escGx(sal, C);
  liberaGx(&C);
  
  /* Producto */
  printf("Por calcular A(x)B(x).\n");
  C=multGx(A,B);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A(x)*B(x)=");
  escGx(sal, C);
  liberaGx(&C);
  
  /* Derivada */
  printf("Por calcular A'(x).\n");
  C=derivaGx(A);
  printf("Por escribir el resultado en el archivo %s\n", nomsal);
  fprintf(sal, "A'(x)=");
  escGx(sal, C);
  liberaGx(&C);
  
  fclose(sal);
  fclose(ent);
	return 0;
}

// funciones de G //
G leeG(FILE *f){
	G a;

   fscanf(f,"%d%d",&a.r,&a.i);	
  
  return a;
}
int escG(FILE *f, G a){
	if(a.r==0 &&a.i==0) fprintf(f,"0");
     else{
     	if(a.r==0);
     	else fprintf(f,"%+d",a.r);
     	if (a.i==0);
     	else{
     		if(a.i==1) fprintf(f,"+i");
     		else{
     			if(a.i==-1) fprintf(f,"-i");
     		    else fprintf(f,"%+di",a.i);	
			 }
     		
		 }
	 }
	return 0;
} 
int esCeroG(G a){
	if(a.r==0 && a.i==0) return 1;
	else return 0;
} 
int igualG(G a, G b){
	if(a.r==b.r	&& a.i==b.i) return 1;
	else return 0;
}     
G creaG(int rea, int ima){
	G r = {r:rea, i:ima};

  return r;
}
G sumaG(G a, G b){
	G r={r:a.r+b.r, i:a.i+b.i};           
	
  return r;
}
G restaG(G a, G b){
	G r={r:a.r-b.r, i:a.i-b.i};           
	
  return r;
}
G prodG(G a, G b){
	G r={r:a.r*b.r-a.i*b.i, i:a.r*b.i+a.i*b.r};           
	
  return r;
}

// funciones de poliG //
Gx leeGx(FILE *f){
	Gx ret;
  int i;

  printf("Por leer el grado\n");
  fscanf(f,"%d", &(ret.g));

  if((ret.c=(G*)malloc((ret.g+1)*sizeof(G)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }

  for (i=0; i<=ret.g; i++)
    ret.c[i]=leeG(f);

  return ret;
}
int escGx(FILE *f, Gx p){
		int i;
	G unit={r:1,i:0};
  
  if(p.g<0){
    fprintf(f, "0\n\n");
    return 0;
  }
  if(p.g==0){
  	escG(f, p.c[0]);
    fprintf(f, "\n\n");
    return 0;
  }

	if(!esCeroG(p.c[0])){
		escG(f, p.c[0]);
		fprintf(f, "+");
	} 
	if(!esCeroG(p.c[1])){
  		if(igualG(p.c[1],unit)){
  			fprintf(f,"x");
  			if(p.g>1) fprintf(f, "+");
		  }else{
    		fprintf(f, "(");
			escG(f,p.c[1]);
			fprintf(f, ")");
    		fprintf(f,"x ");
    		if(p.g>1) fprintf(f, "+");
			} 
		}
		  
  	for(i=2; i<=p.g; i++){
	  	if (!esCeroG(p.c[i])){
    	if(igualG(p.c[i],unit)){
    		fprintf(f,"x^%d ", i);
    		if(i<p.g) fprintf(f, "+");
		} 
    	else{
    		fprintf(f, "(");
			escG(f,p.c[i]);
			fprintf(f, ")");
    		fprintf(f,"x^%d ", i);
    		if(i<p.g) fprintf(f, "+");
			} 
		} 
	}

  fprintf(f,"\n\n");
  
  return 0;
}
Gx sumaGx(Gx a, Gx b){
	Gx ret;
  int i, min;

  if (a.g<0){
    return copiaGx(b);
  }
  if (b.g<0){
    return copiaGx(a);
  }
  if (a.g<b.g){
    min = a.g;
    ret.g = b.g;
  } else{
    min = b.g;
    ret.g = a.g;
  }
  if((ret.c=(G*)malloc((ret.g+1)*sizeof(G)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  for (i=0; i<=min; i++) ret.c[i]=sumaG(a.c[i],b.c[i]);
  if (a.g==min){
    for (; i<=ret.g; i++) ret.c[i]=b.c[i];
  }
  if (b.g==min){
    for (; i<=ret.g; i++) ret.c[i]=a.c[i];
  }
  while(ret.g>=0 && esCeroG(ret.c[ret.g])) ret.g--;
  if (ret.g<0){
    free(ret.c);
    ret.c = NULL;
  }
  return ret;
}
Gx restGx(Gx a, Gx b){
	Gx ret;
  int i, min;
  G neg={r:-1,i:0};

  if (a.g<0){
    return copiaMenosGx(b);
  }
  if (b.g<0){
    return copiaGx(a);
  }
  if (a.g<b.g){
    min = a.g;
    ret.g = b.g;
  } else{
    min = b.g;
    ret.g = a.g;
  }
  if((ret.c=(G*)malloc((ret.g+1)*sizeof(G)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  for (i=0; i<=min; i++) ret.c[i]=restaG(a.c[i],b.c[i]);
  if (a.g==min){
    for (; i<=ret.g; i++) ret.c[i]=prodG(neg,b.c[i]);
  }
  if (b.g==min){
    for (; i<=ret.g; i++) ret.c[i]=a.c[i];
  }
  while(ret.g>=0 && esCeroG(ret.c[ret.g])) ret.g--;
  if (ret.g<0){
    free(ret.c);
    ret.c = NULL;
  }
  return ret;
}
Gx multGx(Gx a, Gx b){
	int i, j;
  Gx ret;
  G ceroG={r:0,i:0}; 

  ret.g=a.g+b.g;
  if((ret.c=(G*)malloc((ret.g+1)*sizeof(G)))==NULL){
    printf("error al generar espacio.\n");
    ret.g = -1;
    return ret;
  }
  for (i=0; i<=ret.g; i++) ret.c[i]=ceroG;
  for (i=0; i<=a.g; i++)
    for(j=0; j<=b.g; j++)
      ret.c[i+j]=sumaG(ret.c[i+j],prodG(a.c[i],b.c[j]));

  return ret;
}
Gx derivaGx(Gx a){
	Gx ret={g:a.g-1,c:NULL};
	int i;
	
	if((ret.c=(G*)malloc((ret.g+1)*sizeof(G)))==NULL){
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
int esCeroGx(Gx a){
	return a.g <0;
}
Gx copiaGx(Gx a){
	Gx ret;
  int i;

  ret.g = a.g;
  if (ret.g<0){
    ret.c=NULL;
    return ret;
  }
  if((ret.c=(G*)malloc((ret.g+1)*sizeof(G)))==NULL){
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
Gx copiaMenosGx(Gx a){
	Gx ret;
  int i;

  ret.g = a.g;
  if (ret.g<0){
    ret.c=NULL;
    return ret;
  }
  if((ret.c=(G*)malloc((ret.g+1)*sizeof(G)))==NULL){
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
int  liberaGx(Gx *a){
	if(a->c!=NULL) free(a->c);
  a->g=-1;
  a->c=NULL;
  return 0;	
}

