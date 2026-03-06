#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 

typedef struct _Direccion_{
	char calle[64], col[64], del[64], city[32];
	int exterior, interior;
}direc;

typedef struct _entradaDirectorio_{
  char nombre[32], apellidoPaterno[32], apellidoMaterno[32];
  unsigned short lada;                                      
  unsigned int telFijo, telCel;
  unsigned int dia, mes, year;            
  char anotacion[64];
  char genero[32];
  double altura;
  direc vivienda;                                      
}EntradaDirectorio;                                         

int agregaEntradaAlFinal(FILE *directorio, EntradaDirectorio info);
int obtenEntrada(FILE *directorio, EntradaDirectorio *info);
int mostrarContactos(FILE *directorio);
int editarContacto(FILE *directorio, int a, int b);
int editarCampoContacto(FILE *directorio, int a, int b);
int borrarContacto(FILE *directorio, int a, int b);
int MostrarUno(FILE *directorio, int a, int b);
int MostrarAll(FILE *directorio, EntradaDirectorio entrada);
EntradaDirectorio leerEntrada(void);       

int main(int argc, char *argv[])
{                               
  FILE *archivoBinario;         
  int i,j,a,b,k, ret;                        
  EntradaDirectorio entrada;    

  printf("Ejemplo de archivos binarios. Uso de un directorio ...\n");

  archivoBinario = fopen("directorio.bin", "ab+");

  if (archivoBinario == NULL){
    int errAuxiliar;          
    errAuxiliar = errno;      
    fprintf(stderr, "No se pudo abrir el archivo \"directorio.bin\" (%d:%s)\n", 
errAuxiliar, strerror(errAuxiliar));                                            
    return 0;                                                                   
  }   
  
  do{
  	printf("Para realizar una de las siguientes operaciones, digite el numero correspondiente:");
	printf("\n1)Agregar un contacto");
	printf("\n2)Modificar un contacto");
	printf("\n3)Modificar un campo de un contacto");
	printf("\n4)Mostrar todos los contactos");
	printf("\n5)Mostrar un contacto");
	printf("\n6)Borrar un elemento del archivo");
	printf("\n7)Borrar todo el archivo\n");
	scanf("%d",&i);
	switch(i){
		case 1: entrada=leerEntrada();
				agregaEntradaAlFinal(archivoBinario, entrada);
				break;
		case 2: a=mostrarContactos(archivoBinario);
				if(a!=0){
					printf("\nElija el contacto que desean modificar:");
					scanf("%d",&b);
					editarContacto(archivoBinario,a,b);	
				}
				break;
		case 3: a=mostrarContactos(archivoBinario);
				if(a!=0){
				printf("\nElija el contacto que desean modificar:");
				scanf("%d",&b);
				editarCampoContacto(archivoBinario,a,b);
				}
				break;
		case 4: ret=MostrarAll(archivoBinario,entrada);            
				break;
		case 5: a=mostrarContactos(archivoBinario);
				if(a!=0){
				printf("\nElija el contacto que desean mostrar:");
				scanf("%d",&b);
				MostrarUno(archivoBinario, a, b);
				}
				break;
		case 6: a=mostrarContactos(archivoBinario);
				if(a!=0){
					printf("\nElija el contacto que desea eliminar:");
					scanf("%d",&b);
					borrarContacto(archivoBinario,a,b);	
				}
				break;
		case 7:	fclose(archivoBinario);
				archivoBinario = fopen("directorio.bin", "wb+");

 				 if (archivoBinario == NULL){
   				 int errAuxiliar;          
  				  errAuxiliar = errno;      
   				 fprintf(stderr, "No se pudo abrir el archivo \"directorio.bin\" (%d:%s)\n", 
				errAuxiliar, strerror(errAuxiliar));                                            
   				 return 0;                                                                   
  				} 
				break;
	}
	printf("\nPara salir digite 0; en caso contrario 1\n");
  	scanf("%d", &j);
  }while(j);
                                                                           
  fclose(archivoBinario);

  printf("FIN\n");

  return 0;
}

int agregaEntradaAlFinal(FILE *directorio, EntradaDirectorio info)
{
  long pos;
  int ret;

  pos = ftell(directorio);
  ret = fseek(directorio, 0L, SEEK_END);

  if (ret < 0){
    printf("Error al ir al final del archivo\n");
    return -1;
  }

  ret=fwrite(&info, 1, sizeof(info), directorio);

  if (ret<sizeof(info)){
    printf("Error al escribir la informacion en el directorio\n");
    return -2;
  }

  ret = fseek(directorio, pos, SEEK_SET);

  return 0;
}

int obtenEntrada(FILE *directorio, EntradaDirectorio *info)
{
  int ret;

  ret = fread(info, 1, sizeof(EntradaDirectorio), directorio);
  if (ret<sizeof(info)){
    int unError = errno;
    if (ret == 0) return -2;
    printf("\nError al leer informacion en el directorio (%d, %d, %s)\n",
           ret, unError, strerror(unError));
    return -1;
  }

  return 0;
}

int mostrarContactos(FILE *directorio){
  long pos;
  int ret, i;
  EntradaDirectorio ent;

  pos = ftell(directorio);
  ret = fseek(directorio, 0L, SEEK_SET);

  if (ret < 0){
    printf("Error al ir al inicio del archivo\n");
    return -1;
  }
  
  for (i=0; !feof(directorio); i++){
    if (obtenEntrada(directorio, &ent)<0) break;
    printf("\n\n\t%d)nombre: %s %s %s", i+1,                   
           ent.nombre, ent.apellidoPaterno, ent.apellidoMaterno);                      
  }                                                                          
  if (i==0) printf("\nDirectorio vacio.");                                                       

 printf("\n");
 ret = fseek(directorio, pos, SEEK_SET);
 return i; 
}

/* a= cantidad de contactos *y b= contacto a editar */
int editarContacto(FILE *directorio, int a, int b){ 
	int ret, i;
	EntradaDirectorio *entrada;
	
	ret = fseek(directorio, 0L, SEEK_SET);
	entrada=(EntradaDirectorio*)malloc(sizeof(EntradaDirectorio)*a);
	
	for(i=0; !feof(directorio); i++)
		if (obtenEntrada(directorio, &entrada[i])<0) break;
	
	printf("Por editar el elemento %d del directorio:\n", b);
  printf("Nombre(s): "); scanf("%*c%[^\n]%*c", entrada[b-1].nombre);   
  printf("Apellido paterno: "); scanf("%[^\n]%*c", entrada[b-1].apellidoPaterno);
  printf("Apellido materno: "); scanf("%[^\n]%*c", entrada[b-1].apellidoMaterno);
  printf("Lada: "); scanf("%u", &(entrada[b-1].lada));                    
  printf("Tel fijo: "); scanf("%u", &(entrada[b-1].telFijo));             
  printf("Cel: "); scanf("%u", &(entrada[b-1].telCel));  
  printf("Fecha de nacimiento (dia/ mes(numero) /año): "); scanf("%u%u%u",&(entrada[b-1].dia),&(entrada[b-1].mes),&(entrada[b-1].year));
  printf("Estado civil:");  scanf("%*c%[^\n]%*c", entrada[b-1].anotacion);
  printf("Genero: "); scanf("%[^\n]%*c",&(entrada[b-1].genero));   
  printf("Altura: "); scanf("%lg",&(entrada[b-1].altura));
  printf("Calle: "); scanf("%*c%[^\n]%*c", &(entrada[b-1].vivienda.calle));
  printf("Numero exterior: "); scanf("%d", &(entrada[b-1].vivienda.exterior));
  printf("Numero interior: "); scanf("%d", &(entrada[b-1].vivienda.interior));
  printf("Colonia: "); scanf("*c%[^\n]%*c", &(entrada[b-1].vivienda.col));
  printf("Delegacion: "); scanf("%[^\n]%*c", &(entrada[b-1].vivienda.del));
  printf("Ciudad: "); scanf("%[^\n]%*c", &(entrada[b-1].vivienda.city));
  
  fclose(directorio);
  
  directorio = fopen("directorio.bin", "wb+");

  if (directorio == NULL){
    int errAuxiliar;          
    errAuxiliar = errno;      
    fprintf(stderr, "No se pudo abrir el archivo \"directorio.bin\" (%d:%s)\n", 
errAuxiliar, strerror(errAuxiliar));                                            
    return 0;                                                                   
  }
  
  for(i=0;i<a;i++)
  	agregaEntradaAlFinal(directorio, entrada[i]); 
  	
  ret = fseek(directorio, 0L, SEEK_SET);
  return 0;		
}

int editarCampoContacto(FILE *directorio, int a, int b){
		int ret, i,j;
	EntradaDirectorio *entrada;
	
	ret = fseek(directorio, 0L, SEEK_SET);
	entrada=(EntradaDirectorio*)malloc(sizeof(EntradaDirectorio)*a);
	
	for(i=0; !feof(directorio); i++)
    if (obtenEntrada(directorio, &entrada[i])<0) break;
	
	printf("\nIngrese el numero de campo que desea editar:\n");
	printf("1)Nombre(s)\n2)Apellido paterno\n3)Apellido materno\n4)LADA\n5)Telefono fijo\n6)Telefono celular\n");
	printf("7)Fecha de nacimiento\n8)Estado civil\n9)Genero\n10)Altura\n11)Calle\n12)Numero exterior\n");
	printf("13)Numero interior\n14)Colonia\n15)Delegacion\n16)Ciudad\n");
	scanf("%d",&j);
	printf("Por editar el campo  %d de elemento %d del directorio:\n",j, b);
	if(j==1){
		printf("Nombre(s): "); 
		scanf("%*c%[^\n]%*c", entrada[b-1].nombre);
	}
	if(j==2){
		printf("Apellido paterno: "); 
		scanf("%*c%[^\n]%*c", entrada[b-1].apellidoPaterno);
	}
	if(j==3){
		printf("Apellido materno: "); 
		scanf("%*c%[^\n]%*c", entrada[b-1].apellidoMaterno);
	}
	if(j==4){
		printf("Lada: "); 
		scanf("%u", &(entrada[b-1].lada)); 
	}
	if(j==5){
		printf("Tel fijo: "); 
		scanf("%u", &(entrada[b-1].telFijo)); 
	}
	if(j==6){
		printf("Cel: "); 
		scanf("%u", &(entrada[b-1].telCel));
	}
	if(j==7){
		printf("Fecha de nacimiento  (dia/ mes(numero) /año): "); 
		scanf("%u%u%u",&(entrada[b-1].dia),&(entrada[b-1].mes),&(entrada[b-1].year));
	}
	if(j==8){
		printf("Estado civil: "); 
		scanf("%*c%[^\n]%*c", entrada[b-1].anotacion);
	}
	if(j==9){
		printf("Genero: "); 
		scanf("%*c%[^\n]%*c",&(entrada[b-1].genero)); 
	}if(j==10){
		printf("Altura: "); 
		scanf("%lg",&(entrada[b-1].altura));
	}if(j==11){
  		printf("Calle: "); 
		scanf("%*c%[^\n]%*c", &(entrada[b-1].vivienda.calle));
	}if(j==12){
		printf("Numero exterior: "); 
		scanf("%d", &(entrada[b-1].vivienda.exterior));
	}if(j==13){
   		printf("Numero interior: "); 
		scanf("%d", &(entrada[b-1].vivienda.interior));
	}if(j==14){
		printf("Colonia: "); 
		scanf("%*c%[^\n]%*c", &(entrada[b-1].vivienda.col));
	}if(j==15){
		printf("Delegacion: "); 
		scanf("%*c%[^\n]%*c", &(entrada[b-1].vivienda.del));
	}if(j==16){
		printf("Ciudad: "); 
		scanf("%*c%[^\n]%*c", &(entrada[b-1].vivienda.city));
	}
  
  fclose(directorio);
  
  directorio = fopen("directorio.bin", "wb+");

  if (directorio == NULL){
    int errAuxiliar;          
    errAuxiliar = errno;      
    fprintf(stderr, "No se pudo abrir el archivo \"directorio.bin\" (%d:%s)\n", 
errAuxiliar, strerror(errAuxiliar));                                            
    return 0;                                                                   
  }
  
  for(i=0;i<a;i++)
  	agregaEntradaAlFinal(directorio, entrada[i]); 
  	
  ret = fseek(directorio, 0L, SEEK_SET);
  return 0;		
	
}
EntradaDirectorio leerEntrada(void){
  EntradaDirectorio entrada;	
  printf("Por agregar un elemento al directorio:\n");
  printf("Nombre(s): "); scanf("%*c%[^\n]%*c", entrada.nombre);   
  printf("Apellido paterno: "); scanf("%[^\n]%*c", entrada.apellidoPaterno);
  printf("Apellido materno: "); scanf("%[^\n]%*c", entrada.apellidoMaterno);
  printf("Lada: "); scanf("%u", &(entrada.lada));                    
  printf("Tel fijo: "); scanf("%u", &(entrada.telFijo));             
  printf("Cel: "); scanf("%u", &(entrada.telCel)); 
  printf("Fecha de nacimiento (dia/ mes(numero) /año): "); scanf("%u%u%u",&(entrada.dia),&(entrada.mes),&(entrada.year));
  printf("Estado civil:");  scanf("%*c%[^\n]%*c", entrada.anotacion);
  printf("Genero: "); scanf("%[^\n]%*c",&(entrada.genero)); 
  printf("Altura: "); scanf("%lg",&(entrada.altura)); 
  printf("Datos sobre vivienda\n");
  printf("Calle: "); scanf("%*c%[^\n]%*c", &(entrada.vivienda.calle));
  printf("Numero exterior: "); scanf("%d", &(entrada.vivienda.exterior));
  printf("Numero interior: "); scanf("%d", &(entrada.vivienda.interior));
  printf("Colonia: "); scanf("%*c%[^\n]%*c", &(entrada.vivienda.col));
  printf("Delegacion: "); scanf("%[^\n]%*c", &(entrada.vivienda.del));
  printf("Ciudad: "); scanf("%[^\n]%*c", &(entrada.vivienda.city));
  
  return entrada;
}

int MostrarAll(FILE *directorio, EntradaDirectorio entrada){
	int k, ret;
	
	ret=fseek(directorio, 0L, SEEK_SET); 
	for (k=0; !feof(directorio); k++){
   		if (obtenEntrada(directorio, &entrada)<0) break;
   		printf("\n\n\tNombre(s): %s %s %s",                    
    	entrada.nombre, entrada.apellidoPaterno, entrada.apellidoMaterno);
   		printf("\n\tTelefono fijo: ");                                           
   		if (entrada.telFijo!=0) printf("(%u) %u", entrada.lada, entrada.telFijo);
  		else printf("sin numero telefonico");                                    
   		printf("\n\tTelefono celular: ");                                        
    	if (entrada.telCel!=0) printf("(%u) %u", entrada.lada, entrada.telCel);  
   		else printf("sin numero de telefonia celular");
	    printf("\n\tFecha de nacimiento: %u/%u/%u", entrada.dia, entrada.mes, entrada.year); 
		printf("\n\tEstado civil: %s", entrada.anotacion); 
		printf("\n\tGenero: %s", entrada.genero);
		printf("\n\tAltura: %lg", entrada.altura);   
		printf("\n\tDatos de vivienda:"); 
		printf("\n\tCalle: %s", entrada.vivienda.calle); 
		printf("\n\tNumero exterior: %d", entrada.vivienda.exterior);   
		printf("\n\tNumero interior: %d", entrada.vivienda.interior); 
		printf("\n\tColonia: %s", entrada.vivienda.col); 
		printf("\n\tDelegacion: %s", entrada.vivienda.del);
		printf("\n\tCiudad: %s", entrada.vivienda.city);                 
  	}                                                                          
  	if (k==0) printf("\nDirectorio vacio.\n");                                 
 	else printf("\n\n\t%d entradas en el directorio.\n", k);  
 				
 	return 0;
}
/* a= cantidad de contactos *y b= contacto a borrar */
int borrarContacto(FILE *directorio, int a, int b){
	int i,ret;
	EntradaDirectorio *entrada;
	
	ret = fseek(directorio, 0L, SEEK_SET);
	entrada=(EntradaDirectorio*)malloc(sizeof(EntradaDirectorio)*(a));
	
	for(i=0;!feof(directorio);i++)
		if(obtenEntrada(directorio, &entrada[i])<0) break;
		
	fclose(directorio);
	
	directorio=fopen("directorio.bin", "wb+");

  	if (directorio == NULL){
   		 int errAuxiliar;          
    	errAuxiliar = errno;      
    	fprintf(stderr, "No se pudo abrir el archivo \"directorio.bin\" (%d:%s)\n", 
		errAuxiliar, strerror(errAuxiliar));                                            
    return 0;                                                                   
  	}
  	
  	for(i=0;i<a;i++){
  		if(i!=b-1) agregaEntradaAlFinal(directorio, entrada[i]); 
	  }
	  
	return 0;
}
/* a= cantidad de contactos *y b= contacto para mostrar */
int MostrarUno(FILE *directorio, int a, int b){
		int k, ret;
		EntradaDirectorio *entrada;
	
	ret=fseek(directorio, 0L, SEEK_SET); 
	entrada=(EntradaDirectorio*)malloc(sizeof(EntradaDirectorio)*(a));
	
	
	for (k=0; !feof(directorio); k++){
   		if (obtenEntrada(directorio, &entrada[k])<0) break;
   		}
   		printf("\n\n\tNombre(s): %s %s %s",                    
    	entrada[b-1].nombre, entrada[b-1].apellidoPaterno, entrada[b-1].apellidoMaterno);
   		printf("\n\tTelefono fijo: ");                                           
   		if (entrada[b-1].telFijo!=0) printf("(%u) %u", entrada[b-1].lada, entrada[b-1].telFijo);
  		else printf("sin numero telefonico");                                    
   		printf("\n\tTelefono celular: ");                                        
    	if (entrada[b-1].telCel!=0) printf("(%u) %u", entrada[b-1].lada, entrada[b-1].telCel);  
   		else printf("sin numero de telefonia celular");
	    printf("\n\tFecha de nacimiento: %u/%u/%u", entrada[b-1].dia, entrada[b-1].mes, entrada[b-1].year); 
		printf("\n\tEstado civil: %s", entrada[b-1].anotacion); 
		printf("\n\tGenero: %s", entrada[b-1].genero);
		printf("\n\tAltura: %lg", entrada[b-1].altura);   
		printf("\n\tDatos de vivienda:"); 
		printf("\n\tCalle: %s", entrada[b-1].vivienda.calle); 
		printf("\n\tNumero exterior: %d", entrada[b-1].vivienda.exterior);   
		printf("\n\tNumero interior: %d", entrada[b-1].vivienda.interior); 
		printf("\n\tColonia: %s", entrada[b-1].vivienda.col); 
		printf("\n\tDelegacion: %s", entrada[b-1].vivienda.del);
		printf("\n\tCiudad: %s", entrada[b-1].vivienda.city);                                                                                          
  	if (k==0) printf("\nDirectorio vacio.\n");   
 				
 	return 0;
}
