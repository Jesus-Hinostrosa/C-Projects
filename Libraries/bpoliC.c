#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> 
#include<string.h> 

#include "bcomp.h"
#include "bpoliC.h"

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
    fprintf(f, "0\n\n");
    return 0;
  }
  if(p.g==0){
  	escC(f, p.c[0]);
    fprintf(f, "\n\n");
    return 0;
  }

	if(!esCeroC(p.c[0])){
		escC(f, p.c[0]);
		fprintf(f, "+");
	} 
	if(!esCeroC(p.c[1])){
  		if(igualC(p.c[1],unit)){
  			fprintf(f,"x");
  			if(p.g>1) fprintf(f, "+");
		  }else{
    		fprintf(f, "(");
			escC(f,p.c[1]);
			fprintf(f, ")");
    		fprintf(f,"x ");
    		if(p.g>1) fprintf(f, "+");
			} 
		}
		  
  	for(i=2; i<=p.g; i++){
	  	if (!esCeroC(p.c[i])){
    	if(igualC(p.c[i],unit)){
    		fprintf(f,"x^%d ", i);
    		if(i<p.g) fprintf(f, "+");
		} 
    	else{
    		fprintf(f, "(");
			escC(f,p.c[i]);
			fprintf(f, ")");
    		fprintf(f,"x^%d ", i);
    		if(i<p.g) fprintf(f, "+");
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
  C neg={r:-1.0,i:0.0};

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
  C ceroC={r:0.0,i:0.0};

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
  C ceroC={r:0.0,i:0.0};

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
	C r={r:0, i:0};
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
