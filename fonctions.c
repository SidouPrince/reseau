
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"

unsigned char source_id_court[8], source_id_long[8], destination_id[8], ip[16], port[2],
sender_id[8], nonce[4], type[1], data[40];

voisins_potentiels* liste = NULL;

/******************Liste des voisins potentiels ***************/
voisins_potentiels* allouer(unsigned char *ip, unsigned char *port){
    voisins_potentiels* ptr = malloc(sizeof(voisins_potentiels));
    if ( ptr == NULL )
    {
	perror("malloc allocation");
    	return NULL;
    }
    memcpy(ptr -> ip, ip, 16);
    memcpy(ptr -> port, port, 2);
    ptr -> suivant = NULL;
    return ptr;
}

bool recherche(voisins_potentiels* liste, unsigned char* ip){
    voisins_potentiels* ptr = liste;
    while( ptr != NULL ){
	if ( strcmp((char*)ip, (char*)ptr->ip) == 0 )
	{
		return true;
	}
    ptr = ptr -> suivant;
    }
    return false;	
}

voisins_potentiels* ajoutVP(voisins_potentiels* liste, unsigned char *ip, unsigned char *port){
    voisins_potentiels* p = allouer(ip, port);
    if ( p == NULL ){
	perror("malloc allocation");
	return NULL;	
    }
    
    if ( liste == NULL )//la liste est vide
    {
	printf("ouups\n");
    	liste = p;
	return liste;
    }else{
	/*la liste n'est pas vide
	  avant d'inserer faut effectuer une recherche
	*/
	if ( !recherche(liste, ip) )
	{
	    printf("Nouvelle adresse \n");
	    p -> suivant = liste;
	    liste = p;
	    return liste;
	}else{    
	    //il existe déja
	    printf("adresse deja existante\n");
	    return liste;
	}
    }

}


void afficherListe(voisins_potentiels* liste){
    voisins_potentiels * ptr = liste;
    
    while( ptr != NULL ){
	unsigned char *tmp = ptr -> ip;
	affiche(tmp, 16);
	ptr = ptr -> suivant;
    }
}

short size(voisins_potentiels* liste){
    int cpt = 0;
    if ( liste == NULL ) return 0;
    voisins_potentiels* p = liste;
    while( p != NULL ){
	cpt++;
	p = p->suivant;
    }
    return cpt;
}
/*******************************************Voisins*******************************************************/
voisins* allouerVoisins(unsigned char *ip, unsigned char *port, unsigned char *source_id, int type){
    voisins* ptr = malloc(sizeof(voisins));
    if ( ptr == NULL )
    {
	perror("malloc allocation");
    	return NULL;
    }
    memcpy(ptr -> ip, ip, 16);
    memcpy(ptr -> port, port, 2);
    memcpy(ptr -> source_id, source_id, 8);
    time(&ptr->dateTLV);
    if ( type == 0 )
    {
    	//tlv court
	ptr->dateLong = 0;
    }else{
	time(&ptr -> dateLong);
    }

    ptr -> suivant = NULL;
    return ptr;
}
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
		     liste = ajoutVP(liste, ip, port);
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