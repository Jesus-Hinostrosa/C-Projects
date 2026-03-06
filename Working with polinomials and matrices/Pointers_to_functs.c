#include <stdio.h>    /*funciones de entrada y salida est'andar*/
#include <stdlib.h>   /*funciones de la biblioteca est'andar*/   
#include <string.h>
#include <math.h>

enum tipoCoeficiente {RACIONALES, REALES, CUATERNIONES, GAUSSIANOS, ZP, COMPLEJOS, TOTAL};

typedef struct _racionales_{
  int p, q;
}Q;

typedef struct _complejos_{
  double r, i;
}C;

typedef struct _ZP_{
   int p,n;
}Zp;

typedef struct _Cuaterniones_{
double r,i,j,k;	
}H;

typedef struct _Gaussianos_{
int  r,i; 
}G;  

typedef union _coeficiente_{
  Q unRacional;
  double unReal;
  C unComplejo;
  Zp unZp;
  H unCuate;
  G unGauss;
  
}Coeficiente;

#define EPSILON 1e-15

// Funciones con Zp //
Zp leeZp(FILE *f, int p);
int escZp(FILE *f, Zp a);
int simpZp(Zp d);
Zp creaZp(int n, int p);
Zp sumaZp(Zp a, Zp b);
Zp restaZp(Zp a, Zp b);
Zp prodZp(Zp a, Zp b);
Zp invZp(Zp d);
Zp divZp(Zp a, Zp b);

// Funciones con racionales //
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
Q divQ(Q a, Q b);

// Funciones con reales //
double sumaR(double a, double b);
double restaR(double a, double b);
double prodR(double a, double b);
double divR(double a, double b);

// Funciones con complejos //
C leeC(FILE *f);
int escC(FILE *f, C a); 
int esCeroC(C a); 
int igualC(C a, C b);     
C creaC(int num, int den);
C sumaC(C a, C b);
C restaC(C a, C b);
C prodC(C a, C b);
C invC(C a);
C divC(C a, C b);

// Funciones con cuaterniones //
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

// Funciones con gaussianos //
G leeG(FILE *f);
int escG(FILE *f, G a); 
int esCeroG(G a); 
int igualG(G a, G b);     
G creaG(int r, int i);
G sumaG(G a, G b);
G restaG(G a, G b);
G prodG(G a, G b);

// Funciones con coeficientes //
int muestraA(FILE *f, void *a, void *b, void *suma, enum tipoCoeficiente tipo);
int muestraB(FILE *f, Coeficiente a, Coeficiente b, void *suma, enum tipoCoeficiente tipo);
Coeficiente leeCoef(FILE *f, enum tipoCoeficiente tipo, int p);

int main(int argc, char *argv[]){
 	FILE *ent, *sal;
  char *noment="coeficientes.txt", *nomsal="resultado.txt";
  void *fs[]={sumaQ, sumaR, sumaH, sumaG, sumaZp, sumaC};
  void *fr[]={restaQ, restaR, restaH, restaG, restaZp, restaC};
  void *fp[]={prodQ, prodR, prodH, prodG, prodZp, prodC};
  void *fd[]={divQ, divR, divH, divZp, divC};
  int tipo,p=0;
  Coeficiente a, b;
  
  
  printf("Por leer el archivo %s.\n", noment);
  ent=fopen(noment,"rt");
  if(ent==NULL){
    int mi_error=errno; 
	printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
	mi_error, strerror(mi_error));
    return -1;
  }
  
  fscanf(ent, "%d", &tipo);
 if(tipo==ZP) fscanf(ent, "%d", &p);
  a=leeCoef(ent,tipo,p);
  b=leeCoef(ent,tipo,p);
  
  printf("\nPor escribir el resultado en el archivo %s\n", nomsal);
  sal=fopen(nomsal, "wt");
  if (sal==NULL){
    int mi_error=errno; 
    printf("Hubo un error en la escritura del archivo: %d <<%s>>\nPor finalizar la ejecucion del programa.\n", 
      mi_error, strerror(mi_error));

    fclose(ent);
    return -1;
  }
  
  fprintf(sal,"Sumas: \n");
    muestraB(sal, a, b, fs[tipo], tipo);
  fprintf(sal,"Restas: \n");
	muestraB(sal, a, b, fr[tipo], tipo);
  fprintf(sal,"Productos: \n");
	muestraB(sal, a, b, fp[tipo], tipo);
	
  if(tipo==GAUSSIANOS) fprintf(sal,"\nNo es posible dividir");
  else{
  	fprintf(sal,"Divisiones: \n");
	muestraB(sal, a, b, fd[tipo], tipo);	
	}

  fclose(ent);
  fclose(sal);
  printf("\nFin del programa\n");
  system("PAUSE");
	return 0;
}

// Funciones con Zp //
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

// Funciones con racionales //
Q leeQ(FILE *f){
	Q a;

   fscanf(f,"%d %d",&a.p,&a.q);
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

Q divQ(Q a, Q b){
	Q r={p:a.p*b.q, q:a.q*b.p};           
	
  return simplificaQ(r);
}

// Funciones con reales //
double sumaR(double a, double b){
  return a+b;
}
double restaR(double a, double b){
	return a-b;
}
double prodR(double a, double b){
	return a*b; 
}
double divR(double a, double b){
	return a/b;
}

// Funciones con complejos //
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
	
	n=a.r*a.r+a.i*a.i;
	c.r=a.r/n;
	c.i=-a.i/n;
	
	return c;
}
C divC(C a, C b){
	C c;
	
	b=invC(b);
	c=prodC(a,b);
	
	return c;
}

// Funciones con cuaterniones //
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

// Funciones con gaussianos //
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

// Funciones de coeficiente //

int muestraA(FILE *f, void *a, void *b, void *suma, enum tipoCoeficiente tipo)
{
  Q (*fRacional)(Q, Q);
  double (*fReal)(double, double);
  C (*fCompleja)(C, C);
  Zp (*fModulo)(Zp, Zp);
  H (*fCuaternion)(H, H);
  G (*fGaussiana)(G, G);
  
  Q racionalA, racionalB,retQ;
  double realA, realB;
  C complejoA, complejoB, retC;
  Zp zpA, zpB, retZp;
  H cuaternionA, cuaternionB, retH;
  G gaussA, gaussB, retG;

  if (tipo==RACIONALES){
    racionalA = *(Q *)a;
    racionalB = *(Q *)b;
    fRacional = suma;
    retQ = fRacional(racionalA, racionalB);
    fprintf(f,"F(");
    escQ(f,racionalA);
    fprintf(f,",");
    escQ(f,racionalB);
    fprintf(f,")=");
    escQ(f,retQ);
    fprintf(f,"\n");
  } else if (tipo==REALES){
    realA = *(double*)a;
    realB = *(double *)b;
    fReal = suma;
    fprintf(f,"F(%g, %g) = %g\n", realA, realB, fReal(realA, realB));
  } else if (tipo==COMPLEJOS){
    complejoA = *(C *)a;
    complejoB = *(C *)b;
    fCompleja = suma;
    retC = fCompleja(complejoA, complejoB);
    fprintf(f,"F(");
    escC(f,complejoA);
    fprintf(f,",");
    escC(f,complejoB);
    fprintf(f,")=");
    escC(f,retC);
    fprintf(f,"\n");
  } else if (tipo==ZP){
    zpA = *(Zp*)a;
    zpB = *(Zp*)b;
    fModulo = suma;
    retZp=fModulo(zpA,zpB);
    fprintf(f,"F(");
    escZp(f,zpA);
    fprintf(f,",");
    escZp(f,zpB);
    fprintf(f,")=");
    escZp(f,retZp);
    fprintf(f,"\n");
  } else if(tipo==CUATERNIONES){
  	cuaternionA = *(H*)a; 
  	cuaternionB = *(H*)b;
  	fCuaternion=suma;
	retH=fCuaternion(cuaternionA,cuaternionB);
	fprintf(f,"F(");
    escH(f,cuaternionA);
    fprintf(f,",");
    escH(f,cuaternionB);
    fprintf(f,")=");
    escH(f,retH);
    fprintf(f,"\n");
  }else if(tipo==GAUSSIANOS){
  	gaussA = *(G*)a;
  	gaussB = *(G*)b;
  	fGaussiana=suma;
  	retG=fGaussiana(gaussA,gaussB);
  	fprintf(f,"F(");
    escG(f,gaussA);
    fprintf(f,",");
    escG(f,gaussB);
    fprintf(f,")=");
    escG(f,retG);
    fprintf(f,"\n");
  }

  return 0;
}

int muestraB(FILE *f, Coeficiente a, Coeficiente  b, void *suma, enum tipoCoeficiente tipo)
{
  Q (*fRacional)(Q, Q);
  double (*fReal)(double, double);
  C (*fCompleja)(C, C);
  Zp (*fModulo)(Zp, Zp);
  H (*fCuaternion)(H, H);
  G (*fGaussiana)(G, G);
  Q racionalA, racionalB, retQ;
  C retC;
  Zp retZp;
  H retH;
  G retG;

  if (tipo==RACIONALES){
    fRacional = suma;
    retQ = fRacional(a.unRacional, b.unRacional);
    fprintf(f,"F(");
    escQ(f,a.unRacional);
    fprintf(f,",");
    escQ(f,b.unRacional);
    fprintf(f,")=");
    escQ(f,retQ);
    fprintf(f,"\n");
  } else if (tipo==REALES){
    fReal = suma;
    fprintf(f,"F(%g, %g) = %g\n", a.unReal, b.unReal, fReal(a.unReal, b.unReal));
  } else if (tipo==COMPLEJOS){
    fCompleja = suma;
    retC = fCompleja(a.unComplejo, b.unComplejo);
    fprintf(f,"F(");
    escC(f,a.unComplejo);
    fprintf(f,",");
    escC(f,b.unComplejo);
    fprintf(f,")=");
    escC(f,retC);
    fprintf(f,"\n");
  } else if (tipo==ZP){
    fModulo = suma;
    retZp=fModulo(a.unZp,b.unZp);
    fprintf(f,"F(");
    escZp(f,a.unZp);
    fprintf(f,",");
    escZp(f,b.unZp);
    fprintf(f,")=");
    escZp(f,retZp);
    fprintf(f,"\n");
  } else if(tipo==CUATERNIONES){
  	fCuaternion=suma;
	retH=fCuaternion(a.unCuate,b.unCuate);
	fprintf(f,"F(");
    escH(f,a.unCuate);
    fprintf(f,",");
    escH(f,b.unCuate);
    fprintf(f,")=");
    escH(f,retH);
    fprintf(f,"\n");
  }else if(tipo==GAUSSIANOS){
  	fGaussiana=suma;
  	retG=fGaussiana(a.unGauss, b.unGauss);
  	fprintf(f,"F(");
    escG(f,a.unGauss);
    fprintf(f,",");
    escG(f,b.unGauss);
    fprintf(f,")=");
    escG(f,retG);
    fprintf(f,"\n");
  }
  
   
  return 0;
}
Coeficiente leeCoef(FILE *f, enum tipoCoeficiente tipo, int p){
	Coeficiente ret;
  
    if (tipo==RACIONALES){
        ret.unRacional=leeQ(f);
  } else if (tipo==REALES){
		fscanf(f,"%lf",&ret.unReal);
  } else if (tipo==CUATERNIONES){
        ret.unCuate=leeH(f);
  } else if (tipo==GAUSSIANOS){
  	    ret.unGauss=leeG(f);
  } else if (tipo==ZP){
        ret.unZp=leeZp(f,p);
  } else if (tipo==COMPLEJOS){
        ret.unComplejo=leeC(f);
  }
  
  return ret;
}

