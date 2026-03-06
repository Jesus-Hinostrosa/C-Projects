/*
 * Profesora: Veronica Bola~nos 
 * 
 * Curso de Programaci'on
 * 
 * no olvidar escribir en el rengl'on anterior al de return 0; la l'inea:
 *    system("PAUSE");
 * 
 */

#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>

enum pronombres {YO, TU, EL, NOSOTROS, USTEDES, ELLOS, TotalPronombres};
enum tiemposSimples {PRESENTE, PRETERITO, FUTURO, COPRETERITO, POSTPRETERITO, TotalTiemposSimples};
enum tiemposCompuestos {PretPer, Plus, FutPer, CondPerf, TotalTiemposCompuestos};
enum tiemposSubjuntivo {Pres, PretImp, Imp, PretPerf, PretPlus, TotalTiemposSub};                                                             

#define LONGMAX 128

typedef char enBasePronombres[TotalPronombres*TotalTiemposSimples][LONGMAX];
typedef char enBasePronombresC[TotalPronombres*TotalTiemposCompuestos][LONGMAX];
typedef char enBasePronombresS[TotalPronombres*TotalTiemposSub][LONGMAX];
//// Indicativo ////
char *ModoIndicativoSimple[]={"Presente", "Pretérito", "Futuro",
                             "Copretérito", "Postpretérito"}; 
char *ModoIndicativoCompuesto[]={"   Pretérito perfecto  ", "   Pluscuamperfecto  ",
							 "   Futuro perfecto  ", "   Condicional perfecto  "}; 
//// Subjuntivo ///		
char *ModoSubjuntivo[]={"Presente", "Pretérito imperfecto", "Impertativo", 
						"    Pretérito perfecto", "Pretérito Pluscuamperfecto"}; 
       
	   //// Verbos regulares ///	                      
enBasePronombres DesidenciaSimpleAR = {"o      ","as     ","a      ","amos   ","an     ","an     ",
									   "é      ","aste   ","ó      ","amos   ","aron   ","aron   ",
									   "aré    ","arás   ","ará    ","aremos ","arán   ","arán   ",
									   "aba    ","abas   ","aba    ","abamos ","aban   ","aban   ",
									   "aría   ","arías  ","aría   ","aríamos","arían  ","arían  "};
enBasePronombresC DesidenciaCompuestaAR = {"he", "has", "ha", "hemos", "han", "han",
										   "había", "habías", "había", "habíamos", "habían","habían",
										   "habré", "habrás", "habrá", "habremos", "habrán", "habrán",
										   "habría", "habrías", "habría", "habríamos", "habrían", "habrían"};									                                                                                
enBasePronombresS DesidenciaSubjuntivoAR ={"e      ","es     ","e      ","emos   ","en     ","en     ",
									       "ara    ","aras   ","ara    ","aramos ","aran   ","aran   ",
									       "       ","a      ","e      ","emos   ","en     ","en     ",
									       "haya","hayas","haya","hayamos","hayan","hayan",
									       "hubiera","hubieras","hubiera","hubiéramos","hubieran","hubieran"};

enBasePronombres DesidenciaSimpleER = {"o      ","es     ","e      ","emos   ","en     ","en     ",
									   "í      ","iste   ","ió     ","imos   ","ieron  ","ieron  ",
									   "eré    ","erás   ","erá    ","eremos ","erán   ","erán   ",
									   "ía     ","ías    ","ía     ","íamos  ","ían    ","ían    ",
									   "ería   ","erías  ","ería   ","eríamos","erían  ","erían  "};
enBasePronombresC DesidenciaCompuestaER = {"he", "has", "ha", "hemos", "han", "han", 
										   "había", "habías", "había", "habíamos", "habían","habían",
										   "habré", "habrás", "habrá", "habremos", "habrán", "habrán",
										   "habría", "habrías", "habría", "habríamos", "habrían", "habrían"};									                                                                                
enBasePronombresS DesidenciaSubjuntivoER ={"a      ","as     ","a      ","amos   ","an     ","an     ",
									       "iera   ","ieras  ","iera   ","iéramos ","ieran ","ieran  ",
									       "       ","e      ","a      ","amos   ","an     ","an     ",
									       "haya","hayas","haya","hayamos","hayan","hayan",
									       "hubiera","hubieras","hubiera","hubiéramos","hubieran","hubieran"};

enBasePronombres DesidenciaSimpleIR = {"o      ","es     ","e      ","imos   ","en     ","en     ",
									   "í      ","iste   ","ió     ","imos   ","ieron  ","ieron  ",
									   "iré    ","irás   ","irá    ","iremos ","irán   ","irán   ",
									   "ía     ","ías    ","ía     ","íabamos ","ían    ","ían    ",
									   "iera   ","ieras  ","iera   ","iéramos ","ieran ","ieran  "};
enBasePronombresC DesidenciaCompuestaIR = {"he", "has", "ha", "hemos", "han", "han",
										   "había", "habías", "había", "habíamos", "habían","habían",
										   "habré", "habrás", "habrá", "habremos", "habrán", "habrán",
										   "habría", "habrías", "habría", "habríamos", "habrían", "habrían"};									                                                                                
enBasePronombresS DesidenciaSubjuntivoIR ={"a      ","as     ","a      ","amos   ","an     ","an     ",
									       "iera   ","ieras  ","iera   ","ieramos","ieran  ","ieran  ",
									       "       ","e      ","a      ","amos   ","an     ","an     ",
									       "haya","hayas","haya","hayamos","hayan","hayan",
									       "hubiera","hubieras","hubiera","hubiéramos","hubieran","hubieran"};
			
			
			//// Verbos irregulares ///	
//// Caber ///
enBasePronombres DesidenciaSimpleCaber = {"quepo     ","es      ","e       ","emos    ","en      ","en      ",
									   "upe     ","upiste  ","upo     ","upimos  ","upieron ","upieron ",
									   "ré      ","rás     ","rá      ","remos   ","rán     ","rán     ",
									   "ía      ","ías     ","ia      ","íamos   ","ían     ","ían     ",
									   "ría     ","rías    ","ría     ","ríamos  ","rían    ","rían    "};
enBasePronombresC DesidenciaCompuestaCaber = {"he", "has", "ha", "hemos", "han", "han",
										   "había", "habías", "había", "habíamos", "habían","habían",
										   "habré", "habrás", "habrá", "habremos", "habrán", "habrán",
										   "habría", "habrías", "habría", "habríamos", "habrían", "habrían"};									                                                                                
enBasePronombresS DesidenciaSubjuntivoCaber ={"quepa   ","quepas  ","quepa   ","quepamos","quepan  ","quepan  ",
									       "upiera  ","upieras ","upiera  ","upieramos","upieran ","upieran ",
									       "        ","e       ","quepa   ","quepamos","quepan  ","quepan  ",
									       "haya","hayas","haya ","hayamos","hayan","hayan",
									       "hubiera","hubieras","hubiera","hubiéramos","hubieran","hubieran"};


//// Saber ///
enBasePronombres DesidenciaSimpleSaber = {"é       ","es      ","e       ","emos    ","en      ","en      ",
									      "upe     ","upiste  ","upo     ","upimos  ","upieron ","upieron ",
									      "ré      ","rás     ","rá      ","remos   ","rán     ","rán     ",
									      "ía      ","ías     ","ía      ","íamos   ","ían     ","ían     ",
									      "ría     ","rías    ","ría     ","ríamos  ","rían    ","rían    "};
enBasePronombresC DesidenciaCompuestaSaber = {"he", "has", "ha", "hemos", "han", "han",
										      "había", "habías", "había", "habíamos", "habían","habían",
										      "habré", "habrás", "habrá", "habremos", "habrán", "habrán",
										      "habría", "habrías", "habría", "habríamos", "habrían", "habrían"};									                                                                                
enBasePronombresS DesidenciaSubjuntivoSaber ={"epa      ","epas     ","epa     ","epamos   ","epan     ","epan     ",
									          "upiera   ","upieras  ","upiera  ","upieramos","upieran  ","upieran  ",
						 			          "         ","e        ","epa     ","epamos   ","epan     ","epan     ",
									          "haya","hayas","haya","hayamos","hayan","hayan",
				 					          "hubiera","hubieras","hubiera","hubiéramos","hubieran","hubieran"};


//// Caer, traer, raer, roer ///
enBasePronombres DesidenciaSimpleCaer = {"igo    ","es     ","e      ","emos   ","en     ","en     ",
									     "í      ","íste   ","yó     ","ímos   ","yeron  ","yeron  ",
									     "eré    ","erás   ","erá    ","eremos ","erán   ","erán   ",
									     "ía     ","ías    ","ía     ","íamos  ","ían    ","ían    ",
									     "ería   ","erías  ","ería   ","eríamos","erían  ","erían  "};
enBasePronombresC DesidenciaCompuestaCaer = {"he", "has", "ha", "hemos", "han", "han",
										     "había", "habías", "había", "habíamos", "habían","habían",
										     "habré", "habrás", "habrá", "habremos", "habrán", "habrán",
										     "habría", "habrías", "habría", "habríamos", "habrían", "habrían"};									                                                                                
enBasePronombresS DesidenciaSubjuntivoCaer ={"iga    ","igas   ","iga    ","igamos ","igan   ","igan   ",
									         "yera   ","yeras  ","yera   ","yeramos","yeran  ","yeran  ",
									         "       ","e      ","iga    ","igamos ","igan   ","igan   ",
									         "haya","hayas","haya","hayamos","hayan","hayan",
									         "hubiera","hubieras","hubiera","hubiéramos","hubieran","hubieran"};


//// Leer ///
enBasePronombres DesidenciaSimpleLeer = {"o      ","as     ","a      ","amos   ","an     ","an     ",
									   "é      ","aste   ","ó      ","amos   ","aron   ","aron   ",
									   "aré    ","arás   ","ará    ","aremos ","arán   ","arán   ",
									   "aba    ","abas   ","aba    ","abamos ","aban   ","aban   ",
									   "aría   ","arías  ","aría   ","aríamos","arían  ","arían  "};
enBasePronombresC DesidenciaCompuestaLeer = {"he", "has", "ha", "hemos", "han", "han",
										   "había", "habías", "había", "habíamos", "habían","habían",
										   "habré", "habrás", "habrá", "habremos", "habrán", "habrán",
										   "habría", "habrías", "habría", "habríamos", "habrían", "habrían"};									                                                                                
enBasePronombresS DesidenciaSubjuntivoLeer ={"e      ","es     ","e      ","emos   ","en     ","en     ",
									       "ara    ","aras   ","ara    ","aramos ","aran   ","aran   ",
									       "       ","a      ","e      ","emos   ","en     ","en     ",
									       "haya","hayas","haya","hayamos","hayan","hayan",
									       "hubiera","hubieras","hubiera","hubiéramos","hubieran","hubieran"};

				
									       
enBasePronombres Pronombres = {"yo", "tú", "él", "nosotros", "ustedes", "ellos"};                                                                             

int conjugacionRegularAR(FILE *archivo, char raizVerboAR[]);
int conjugacionRegularER(FILE *archivo, char raizVerboER[]); 
int conjugacionRegularIR(FILE *archivo, char raizVerboIR[]); 
int conjugacionCaber(FILE *archivo, char raizCaber[]);  
int conjugacionSaber(FILE *archivo, char raizSaber[]);  
int conjugacionCaer(FILE *archivo, char raizCaer[]);  /* 4 */ 
int conjugacionLeer(FILE *archivo, char raizLeer[]);                                                                            

int main(int argc, char *argv[])
{                               
  FILE *miArchivo;              
  char buffer[128], a,b,c,d;             
  int lbuffer;                  

  miArchivo = fopen("misVerbos.txt", "w");

  if (miArchivo == NULL){
    fprintf(stderr, "No se pudo abrir el archivo \"misVerbos.txt\"\n");
    return 0;                                                          
  }                                                                    
  printf("Escriba un verbo regular terminado en ar (ADVERTENCIA: No atender "
         "a esta instrucci'on ocasionar'a un resultado inesperado :-) ):");  

  scanf("%s", buffer);
  lbuffer = strlen(buffer);

  d=buffer[lbuffer-5];
  c=buffer[lbuffer-4];
  b=buffer[lbuffer-3];
  a=buffer[lbuffer-2];                                      
  buffer[lbuffer-2]= '\0';

  printf("Por conjugar verbo\n");
  
  if(a=='a') conjugacionRegularAR(miArchivo, buffer);
  if(a=='e'){
  	printf("\n\n\n\n\n%d \n\n\n\n\n",lbuffer);
  	if(lbuffer==5){
  		if(d=='c' && c=='a' && b=='b') conjugacionCaber(miArchivo, buffer);
		if(d=='s' && c=='a' && b=='b') conjugacionSaber(miArchivo, buffer);
		if(d=='t' && c=='r' && b=='a'){
			printf("\n\n\n\n una frase mas larga \n\n\n\n");
			conjugacionCaer(miArchivo, buffer);
		} 
	}else{
  		if(lbuffer==4){
		  if(c=='c' && b=='a') conjugacionCaer(miArchivo, buffer);
		  if(c=='r' && b=='o') conjugacionCaer(miArchivo, buffer);
		  if(c=='r' && b=='a') conjugacionCaer(miArchivo, buffer);
		  }
  		else{
  			printf("\n\n\n\n\n sjfkglgl \n\n\n\n\n");
  			conjugacionRegularER(miArchivo, buffer);
		  } 
		} 
	}
	  
  if(a=='i') conjugacionRegularIR(miArchivo, buffer);
  printf("Verbo Conjugado\n");                    

  fclose(miArchivo);

  printf("FIN\n");

  return 0;
}          

int conjugacionRegularAR(FILE *archivo, char raizVerboAR[])                                                                           
{                                                                               
  int  lpronombre=8, ldesidencia=4,tiempo, lverbo, persona, centrado, titulo;           
  char formato[1024];                                                           
  
  lverbo = strlen(raizVerboAR)+2;

  for(tiempo=0;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoIndicativoSimple[tiempo])/2; /* 4 */
	    centrado = (lverbo+lpronombre+ldesidencia+1)/2; /* 8 */
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoIndicativoSimple[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<5*TotalPronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona], 
    		        raizVerboAR, DesidenciaSimpleAR[tiempo]); 
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=3;tiempo++)
   {
  		titulo = strlen(ModoIndicativoCompuesto[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, "  ", ModoIndicativoCompuesto[tiempo],"  ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<4*TotalPronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %8s %sado  ", Pronombres[persona], 
    		         DesidenciaCompuestaAR[tiempo], raizVerboAR); 
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=2;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+3)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona;tiempo<3*TotalPronombres;tiempo+=6){
   		if(tiempo==12){
   			fprintf(archivo, "%8s %s  ", Pronombres[persona],
			   			 DesidenciaSubjuntivoAR[tiempo]);
		   }
	  		else{
	  			fprintf(archivo, "%8s %s%s  ", Pronombres[persona], 
    		          raizVerboAR, DesidenciaSubjuntivoAR[tiempo]);
		   }
	   } 
   	                                                           
	fprintf(archivo, "\n");
   } 
   
   	fprintf(archivo, "\n");
   	for(tiempo=3;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona+18;tiempo<5*TotalPronombres;tiempo+=6){
	  		fprintf(archivo, "%8s %7s %sado  ", Pronombres[persona], 
    		          DesidenciaSubjuntivoAR[tiempo], raizVerboAR);
	   } 
   	                                                           
	fprintf(archivo, "\n");
   }    
  return 0;  
}            

int conjugacionRegularER(FILE *archivo, char raizVerboER[])                                                                           
{                                                                               
  int  lpronombre=8, ldesidencia=4,tiempo, lverbo, persona, centrado, titulo;           
  char formato[1024];                                                           
  
  lverbo = strlen(raizVerboER)+2;

  for(tiempo=0;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoIndicativoSimple[tiempo])/2; /* 4 */
	    centrado = (lverbo+lpronombre+ldesidencia+1)/2; /* 8 */
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoIndicativoSimple[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<5*TotalPronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona], 
    		        raizVerboER, DesidenciaSimpleER[tiempo]); 
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=3;tiempo++)
   {
  		titulo = strlen(ModoIndicativoCompuesto[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, "  ", ModoIndicativoCompuesto[tiempo],"  ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<4*TotalPronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %8s %sado  ", Pronombres[persona], 
    		         DesidenciaCompuestaER[tiempo], raizVerboER); 
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=2;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+3)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona;tiempo<3*TotalPronombres;tiempo+=6){
   		if(tiempo==12){
   			fprintf(archivo, "%8s %s  ", Pronombres[persona],
			   			 DesidenciaSubjuntivoER[tiempo]);
		   }
	  		else{
	  			fprintf(archivo, "%8s %s%s  ", Pronombres[persona], 
    		          raizVerboER, DesidenciaSubjuntivoER[tiempo]);
		   }
	   } 
   	                                                           
	fprintf(archivo, "\n");
   } 
   
   	fprintf(archivo, "\n");
   	for(tiempo=3;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona+18;tiempo<5*TotalPronombres;tiempo+=6){
	  		fprintf(archivo, "%8s %7s %sado  ", Pronombres[persona], 
    		          DesidenciaSubjuntivoER[tiempo], raizVerboER);
	   } 
   	                                                           
	fprintf(archivo, "\n");
   }    
  return 0;  
}            

int conjugacionRegularIR(FILE *archivo, char raizVerboIR[])                                                                           
{                                                                               
  int  lpronombre=8, ldesidencia=4,tiempo, lverbo, persona, centrado, titulo;           
  char formato[1024];                                                           
  
  lverbo = strlen(raizVerboIR)+2;

  for(tiempo=0;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoIndicativoSimple[tiempo])/2; /* 4 */
	    centrado = (lverbo+lpronombre+ldesidencia+1)/2; /* 8 */
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoIndicativoSimple[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<5*TotalPronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona], 
    		        raizVerboIR, DesidenciaSimpleIR[tiempo]); 
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=3;tiempo++)
   {
  		titulo = strlen(ModoIndicativoCompuesto[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, "  ", ModoIndicativoCompuesto[tiempo],"  ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<4*TotalPronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %8s %sado  ", Pronombres[persona], 
    		         DesidenciaCompuestaIR[tiempo], raizVerboIR); 
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=2;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+3)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona;tiempo<3*TotalPronombres;tiempo+=6){
   		if(tiempo==12){
   			fprintf(archivo, "%8s %s  ", Pronombres[persona],
			   			 DesidenciaSubjuntivoIR[tiempo]);
		   }
	  		else{
	  			fprintf(archivo, "%8s %s%s  ", Pronombres[persona], 
    		          raizVerboIR, DesidenciaSubjuntivoIR[tiempo]);
		   }
	   } 
   	                                                           
	fprintf(archivo, "\n");
   } 
   
   	fprintf(archivo, "\n");
   	for(tiempo=3;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona+18;tiempo<5*TotalPronombres;tiempo+=6){
	  		fprintf(archivo, "%8s %7s %sado  ", Pronombres[persona], 
    		          DesidenciaSubjuntivoIR[tiempo], raizVerboIR);
	   } 
   	                                                           
	fprintf(archivo, "\n");
   }    
  return 0;  
}            

int conjugacionCaber(FILE *archivo, char raizCaber[]){
	                                                                               
  int  lpronombre=8, ldesidencia=4,tiempo, lverbo, persona, centrado, titulo;           
  char formato[1024];                                                           
  
  lverbo = strlen(raizCaber)+2;

  for(tiempo=0;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoIndicativoSimple[tiempo])/2; /* 4 */
	    centrado = (lverbo+lpronombre+ldesidencia+1)/2; /* 8 */
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoIndicativoSimple[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<5*TotalPronombres;tiempo+=6) 
	  		if(tiempo==0 || 6<=tiempo && tiempo<=11){
			  if(tiempo==0) fprintf(archivo, "%8s %s", Pronombres[persona], DesidenciaSimpleCaber[tiempo]);
				if(6<=tiempo && tiempo<=11)
	  		    fprintf(archivo, "%8s c%s  ", Pronombres[persona], DesidenciaSubjuntivoCaber[tiempo]); 
			  }	
    		else fprintf(archivo, "%8s %s%s", Pronombres[persona], 
    		        raizCaber, DesidenciaSimpleCaber[tiempo]);         
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=3;tiempo++)
   {
  		titulo = strlen(ModoIndicativoCompuesto[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, "  ", ModoIndicativoCompuesto[tiempo],"  ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<4*TotalPronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %8s %sido  ", Pronombres[persona], 
    		         DesidenciaCompuestaCaber[tiempo], raizCaber); 
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=2;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+3)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona;tiempo<3*TotalPronombres;tiempo+=6){
   			if(0<=tiempo && tiempo<=5 || 14<=tiempo && tiempo<=17 || tiempo==12)
   				fprintf(archivo, "%8s %s  ", Pronombres[persona], DesidenciaSubjuntivoCaber[tiempo]);
	  		if(6<=tiempo && tiempo<=11)
	  			fprintf(archivo, "%8s c%s  ", Pronombres[persona], DesidenciaSubjuntivoCaber[tiempo]);
    		if(tiempo==13)
				fprintf(archivo, "%8s %s%s  ", Pronombres[persona], 
    		          raizCaber, DesidenciaSubjuntivoCaber[tiempo]);          
	   } 
   	                                                           
	fprintf(archivo, "\n");
   } 
   
   	fprintf(archivo, "\n");
   	for(tiempo=3;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona+18;tiempo<5*TotalPronombres;tiempo+=6){
	  		fprintf(archivo, "%8s %7s %sado  ", Pronombres[persona], 
    		          DesidenciaSubjuntivoIR[tiempo], raizCaber);
	   } 
   	                                                           
	fprintf(archivo, "\n");
   }    
  return 0; 
}  

int conjugacionSaber(FILE *archivo, char raizSaber[]){
	                                                                               
  int  lpronombre=8, ldesidencia=4,tiempo, lverbo, persona, centrado, titulo;           
  char formato[1024];                                                           
  
  lverbo = strlen(raizSaber)+2;

  for(tiempo=0;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoIndicativoSimple[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+1)/2;
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoIndicativoSimple[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<5*TotalPronombres;tiempo+=6) 
	  		if(tiempo==0 || 6<=tiempo && tiempo<=11)
	  			fprintf(archivo, "%8s s%s", Pronombres[persona], DesidenciaSimpleSaber[tiempo]); 
			else fprintf(archivo, "%8s %s%s", Pronombres[persona], 
    		        raizSaber, DesidenciaSimpleSaber[tiempo]); 
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=3;tiempo++)
   {
  		titulo = strlen(ModoIndicativoCompuesto[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, "  ", ModoIndicativoCompuesto[tiempo],"  ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<4*TotalPronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %8s %sido  ", Pronombres[persona], 
    		         DesidenciaCompuestaSaber[tiempo], raizSaber); 
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=2;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+3)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona;tiempo<3*TotalPronombres;tiempo+=6){
   		if(tiempo==13){
   			fprintf(archivo, "%8s %s%s  ", Pronombres[persona], 
    		          raizSaber, DesidenciaSubjuntivoSaber[tiempo]);
		   }
	  		else{
	  			fprintf(archivo, "%8s s%s", Pronombres[persona], DesidenciaSubjuntivoSaber[tiempo]);       
		   }
	   } 
   	                                                           
	fprintf(archivo, "\n");
   } 
   
   	fprintf(archivo, "\n");
   	for(tiempo=3;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona+18;tiempo<5*TotalPronombres;tiempo+=6){
	  		fprintf(archivo, "%8s %7s sabido  ", Pronombres[persona], 
    		          DesidenciaSubjuntivoSaber[tiempo]);
	   } 
   	                                                           
	fprintf(archivo, "\n");
   }    
  return 0; 
}  

int conjugacionCaer(FILE *archivo, char raizCaer[]){
  int  lpronombre=8, ldesidencia=4,tiempo, lverbo, persona, centrado, titulo;           
  char formato[1024];                                                           
  
  lverbo = strlen(raizCaer)+2;

  for(tiempo=0;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoIndicativoSimple[tiempo])/2; /* 4 */
	    centrado = (lverbo+lpronombre+ldesidencia+1)/2; /* 8 */
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoIndicativoSimple[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<5*TotalPronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona], 
    		        raizCaer, DesidenciaSimpleCaer[tiempo]); 
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=3;tiempo++)
   {
  		titulo = strlen(ModoIndicativoCompuesto[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, "  ", ModoIndicativoCompuesto[tiempo],"  ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<4*TotalPronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %8s %sído  ", Pronombres[persona], 
    		         DesidenciaCompuestaCaer[tiempo], raizCaer); 
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=2;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+3)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona;tiempo<3*TotalPronombres;tiempo+=6){
   		if(tiempo==12){
   			fprintf(archivo, "%8s %s  ", Pronombres[persona],
			   			 DesidenciaSubjuntivoCaer[tiempo]);
		   }
	  		else{
	  			fprintf(archivo, "%8s %s%s  ", Pronombres[persona], 
    		          raizCaer, DesidenciaSubjuntivoCaer[tiempo]);
		   }
	   } 
   	                                                           
	fprintf(archivo, "\n");
   } 
   
   	fprintf(archivo, "\n");
   	for(tiempo=3;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona+18;tiempo<5*TotalPronombres;tiempo+=6){
	  		fprintf(archivo, "%8s %7s %sído  ", Pronombres[persona], 
    		          DesidenciaSubjuntivoCaer[tiempo], raizCaer);
	   } 
   	                                                           
	fprintf(archivo, "\n");
   }    
  return 0;
} 
/*  
int conjugacionLeer(FILE *archivo, char raizLeer[]){
	                                                                               
  int  lpronombre=8, ldesidencia=4,tiempo, lverbo, persona, centrado, titulo;           
  char formato[1024];                                                           
  
  lverbo = strlen(raizLeer)+2;

  for(tiempo=0;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoIndicativoSimple[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+1)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoIndicativoSimple[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<5*TotalPronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona], 
    		        raizLeer, DesidenciaSimpleIR[tiempo]); 
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=3;tiempo++)
   {
  		titulo = strlen(ModoIndicativoCompuesto[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, "  ", ModoIndicativoCompuesto[tiempo],"  ");	
	    
   }
	  fprintf(archivo,"\n\n ");
  for (persona=0; persona<TotalPronombres; persona++)
   {
		for(tiempo=persona;tiempo<4*TotalPronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %8s %sado  ", Pronombres[persona], 
    		         DesidenciaCompuestaIR[tiempo], raizLeer); 
        fprintf(archivo, "\n");
   }                                                           
	fprintf(archivo, "\n");
	
	for(tiempo=0;tiempo<=2;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+3)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona;tiempo<3*TotalPronombres;tiempo+=6){
   		if(tiempo==12){
   			fprintf(archivo, "%8s %s  ", Pronombres[persona],
			   			 DesidenciaSubjuntivoIR[tiempo]);
		   }
	  		else{
	  			fprintf(archivo, "%8s %s%s  ", Pronombres[persona], 
    		          raizLeer, DesidenciaSubjuntivoIR[tiempo]);
		   }
	   } 
   	                                                           
	fprintf(archivo, "\n");
   } 
   
   	fprintf(archivo, "\n");
   	for(tiempo=3;tiempo<=4;tiempo++)
   {
  		titulo = strlen(ModoSubjuntivo[tiempo])/2; 
	    centrado = (lverbo+lpronombre+ldesidencia+5)/2; 
	    if (centrado<=titulo) centrado=0;
  			else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", ModoSubjuntivo[tiempo]," ");	
	    
   }
	  fprintf(archivo,"\n\n ");
	  
  for (persona=0; persona<TotalPronombres; persona++){
   	for(tiempo=persona+18;tiempo<5*TotalPronombres;tiempo+=6){
	  		fprintf(archivo, "%8s %7s %sado  ", Pronombres[persona], 
    		          DesidenciaSubjuntivoIR[tiempo], raizLeer);
	   } 
   	                                                           
	fprintf(archivo, "\n");
   }    
  return 0; 
}         
*/
