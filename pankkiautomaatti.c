/*
  20.12.2017
  Ensimmäinen hieman isompi harjoitustyo:
  Pankkiautomaatti-simulaattori
  Saila Kivela
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LOPETUS 4
 
void lueRoskat(void);
int laskeSetelit(int otto);
 
int main (void) {

    int vertailu,
	    otto,
		talletus,
		tulos;
		
	long toiminto;
	
	char toiminto2[256];
    char *ptr;
	char tilinumero[256];
	char pinkoodi[256];
    char oikeaPin[256];
	
	FILE * tili;
		
	double saldo;
	
    do{		   
        do{
	        printf("Anna tilinumero: ");
	        fgets( tilinumero, 256, stdin );
	
	        if( tilinumero[ strlen(tilinumero) -1] == '\n')
                tilinumero[ strlen(tilinumero) -1] = '\0';
            else
                lueRoskat();
	
	        strcat(tilinumero, ".tili");
	
	        if( ( tili = fopen( tilinumero, "r" ))!=NULL){
        
		        printf("Anna pinkoodi: "); 
                fgets( pinkoodi, 256, stdin );
		
	        } else {
                printf("Tilia ei loydy. \n");
	        }
        } while ( ( tili = fopen( tilinumero, "r" ))==NULL);
        		     
	    if( pinkoodi[ strlen(pinkoodi) -1] == '\n') {
            pinkoodi[ strlen(pinkoodi) -1] = '\0';
        
	    } else {
            lueRoskat();
        }    
            fgets( oikeaPin, 256, tili );
		
	    do {
		    if( oikeaPin[ strlen(oikeaPin) -1] == '\n')
                oikeaPin[ strlen(oikeaPin) -1] = '\0';
                
            if( oikeaPin[ strlen(oikeaPin) -1] == '\r')
                oikeaPin[ strlen(oikeaPin) -1] = '\0';
        
		    if( (vertailu = strcmp( pinkoodi, oikeaPin ))  == 0 ){
                fscanf( tili, "%lf", &saldo);
			
                do {
                    printf("\nValitse toiminto:\n 1   otto\n 2   talletus\n 3   saldo\n 4   lopetus\n");
            
			        fgets( toiminto2, 256, stdin );
			    
				    if( toiminto2[ strlen(toiminto2) -1] == '\n'){
                        toiminto2[ strlen(toiminto2) -1] = '\0';
			        } else {
                        lueRoskat();
			        }
			
			        toiminto = strtol(toiminto2, &ptr, 10);
			
		            switch (toiminto) { 
		                case 1 :
			                printf("Anna nostettava summa: ");
			                scanf("%d", &otto);
			   
			                if (saldo >= otto) {
			        
					            tulos = laskeSetelit (otto);
					    
						        if (tulos ==0 && otto >= 0){
					                saldo = saldo - otto;
			                        otto = 0;
		                            printf("\nTilin saldo on %.2f euroa.\n\n\n", saldo);
					            } else {
								    printf("Otto epaonnistui.\n");
							    }	
						        lueRoskat();
						        break;
			        
					        } else if(saldo < otto){
					            printf("Tililla ei ole tarpeeksi rahaa.\nOtto epaonnistui. \n");
							    lueRoskat();
				            } else {
                                printf("Otto epaonnistui.\n");
							    lueRoskat();
                            }							
			                break;
			
			            case 2 :
			                printf("Anna talletettava summa: ");
			                scanf("%d", &talletus);
				        
						    if (talletus >= 0){
				                saldo = saldo + talletus;
				                talletus = 0;
				                printf("Tilin saldo on nyt %.2f euroa.\n\n\n", saldo);
								
						    } else {
								printf("Talletus epaonnistui.\n");
							}
							lueRoskat();
			                break;
			
			            case 3 :			   
			                printf("\nTilin saldo on %.2f euroa.\n\n\n", saldo);
			                break;
			
			            case 4 :
						    if( ( tili = fopen( tilinumero, "w" ))!=NULL){
							    fprintf(tili, "%s\n%.2f\n", oikeaPin, saldo);
							
						        fclose (tili);
						    } else {
						        printf("Saldon tallennus epaonnistui.");
						    }
						
						    printf("\nKiitos kaynnista!\nTervetuloa uudestaan!\n\n");
						    exit(1);
			                break;
				    
					
				        default:
					        printf("\n Virhe valinnassa.\n Valitse uudestaan. \n\n");
	                        break;
                 	
    
                    }  
			    } while (toiminto != LOPETUS);	
		
	        } else {
               printf("Pin-koodi vaarin, kokeile uudestaan! \n\n");
            }
			
      	} while( !vertailu );

    } while (1);
    
	return 0;
}
 
 /*
 Funktio lueRoskat poistaa vaarat/turhat merkit syotteesta, jotta eivat jaa pyorimaan myohempiin vaiheisiin.
 */
 
void lueRoskat(void){
   
    while(fgetc(stdin) != '\n');
   
}

/*
Funktio laskeSetelit laskee ja kertoo montako 50-euron ja montako 20-euron setelia annetaan. Tulos kertoo myos, jos nosto ei onnistu.
Funktio saa parametrina ottosumman ja palauttaa arvona 1 tai 0, riippuen onnistuiko nosto.
1=nosto ei onnistu --> saldo ei muutu
0=nosto onnistuu --> saldo pienenee noston verran (mainissa).
*/
int laskeSetelit(int otto) {

    int setelit20,
        laskuri = 0,
		tulos;
	
	if (otto < 20 && otto > 0){
		printf("Pienin nostettava summa on 20 euroa.\n");
		tulos = 1;
		
	} else if (otto > 1000){
		printf("Suurin nostettava summa on 1000 euroa.\n");
		tulos = 1;
		
	} else if (otto >= 20 && otto <= 1000){
		
		if (otto % 10 != 0){
			printf("Ottosumman on oltava jaollinen 10:lla.\n");
			tulos = 1;
			
		} if (otto % 10 == 0){
			
			if (otto == 30){
				printf("Et voi nostaa 30 euroa. Kokeile jotain muuta summaa.\n");
				tulos = 1;
				
			} else {
				
				if (otto % 50 == 0){
					
					while (otto > 0){
						otto = otto - 50;
						laskuri++;
						tulos = 0;
					}	
							
			    } else if ((otto-20) % 50 == 0){
					otto = otto-20;
					setelit20 = 1;
					
					while (otto > 0){
						otto = otto - 50;
						laskuri++;
						tulos = 0;
					}
							
			    } else if ((otto-40) % 50 == 0){
					otto = otto-40;
					setelit20 = 2;
					
					while (otto > 0){
						otto = otto - 50;
						laskuri++;
						tulos = 0;
					}
							
			    } else if ((otto-60) % 50 == 0){
					otto = otto-60;
					setelit20 = 3;
					
					while (otto > 0){
						otto = otto - 50;
						laskuri++;
						tulos = 0;
					}							
							
			    } else if ((otto-80) % 50 == 0){
					otto = otto-80;
					setelit20 = 4;
					
					while (otto > 0){
						otto = otto - 50;
						laskuri++;
						tulos = 0;
					}							
			    }
				
			    printf("\nSaat %d * 50 euroa ja %d * 20 euroa.\n\n", laskuri, setelit20);										
		    }
	    }
	}
    return (tulos);
 }
