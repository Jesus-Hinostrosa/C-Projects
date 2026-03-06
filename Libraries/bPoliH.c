#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> 
#include<string.h> 

#include "bH.h"
#include "bPoliH.h"

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
  	ret.c[i].r=-b.c[i].r;
  	ret.c[i].i=-b.c[i].i;
  	ret.c[i].j=-b.c[i].j;
  	ret.c[i].k=-b.c[i].k;
  } 
  }else{
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
    ret.c[grad]=divH(a.c[a.g],b.c[b.g]);
    aux=multMonoHx(b, ret.c[grad], grad);
    aaux=restHx(a,aux);
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

