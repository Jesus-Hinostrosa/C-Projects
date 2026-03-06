#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> 
#include<string.h> 

#include "bZp.h"
#include "bPoliZp.h"

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


