#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h> 
#include<string.h> 

#include "bRaq.h"
#include "bpoliQ.h"

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
