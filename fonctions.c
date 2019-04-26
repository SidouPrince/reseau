
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"

unsigned char source_id_court[8], source_id_long[8], destination_id[8], ip[16], port[2],
sender_id[8], nonce[4], type[1], data[40];

/**********************************************/
void helloCourt(unsigned char* tableau){
    memcpy(source_id_court, &tableau[0], 8);
}

/*********************************************/
void helloLong(unsigned char* tableau){

    memcpy(source_id_long, &tableau[0], 8);
    memcpy(destination_id, &tableau[8], 8);
}
/*****************************************************/
void neighbor(unsigned char * tableau){
    memcpy(ip, &tableau[0], 16);
    memcpy(port, &tableau[16], 2);
}
/*****************************************************/
void dataTLV(unsigned char *tab, int taille){
    memcpy(sender_id, &tab[0], 8);
    memcpy(nonce, &tab[8], 4);
    memcpy(type, &tab[12], 1);
    memcpy(data, &tab[13], (taille-13));
}
/**************************************************/
void affiche(unsigned char tab[], int taille){
    for (int i = 0; i < taille ; ++i)
    {
    	printf("%.2d : ", tab[i]);
    }
    printf("\n");
}
/**************************************************/
void afficher_message(unsigned char tab[], int taille){
    for (int i = 0; i < taille ; ++i)
    {
    	printf("%c : ", tab[i]);
    }
    printf("\n");
}
/*****************************************************/
 void parserTLV(unsigned char tab[], int taille){
     int i = 0;
     while( i < taille ){
	 switch (tab[i]){ //exactement ou se trouve le début de tlv
	     case 1: 
		     printf("***********TLV PADN***************\n");
		     i = i + tab[i+1] + 2;
	     case 2: 
		    if ( tab[i+1] == 8 )
		    {
		    	printf("*********Hello Court**********\n");
			helloCourt(&tab[i+2]);
			affiche(source_id_court, 8);
			i = i + 10; //pour passer au tlv suivant
		    }else{
			printf("*********Hello Long************\n");
			helloLong(&tab[i+2]);
			affiche(source_id_long, 8);
			affiche(destination_id, 8);
			i = i + 18; //pour passer au tlv suivant
		    }
		    break;
             case 3: 
		     printf("**********TLV Neighbor***********\n");
		     neighbor(&tab[i+2]);
		     i = i + 20; //pour passer au tlv suivant
		     printf("L'adresse ip est : ");
		     affiche(ip, 16);
		     printf("Le port est : ");
		     affiche(port, 2);
		     break;
	    case 4: 
		    printf("******************TLV DATA****************");
		    dataTLV(&tab[i+2], tab[i+3]);
		    printf("L'adresse ip est : ");
		     affiche(sender_id, 8);
		     printf("Le Nonce est : ");
		     affiche(nonce, 4);
		     printf("Le type est : ");
		     affiche(type, 1);
		     printf("Le message est : ");
		     afficher_message(data, (tab[i+3]-13));
		     break;
		     break;

	 }
     }
}