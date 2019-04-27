#ifndef FONCTIONS_H
#define FONCTIONS_H
#include <stdbool.h>
#include <time.h>

/***************************Les variables des differents tlv***************************/
unsigned char source_id_court[8], source_id_long[8], destination_id[8], ip[16], port[2],
sender_id[8], nonce[4], type[1], data[40];
/****************************************************************************************/
/********************La structure Liste des voisin potentiels****************************/
typedef struct voisins_potentiels voisins_potentiels;
struct voisins_potentiels{
    unsigned char ip[16];
    unsigned char port[2];
    voisins_potentiels *suivant;
};

/********************La structure Liste des voisins****************************/
typedef struct voisins voisins;
struct voisins{
    unsigned char ip[16];
    unsigned char port[2];
    unsigned char source_id[8];
    time_t dateTLV;
    time_t dateLong;
    voisins *suivant;
};

/***************************Voisins Potentiels**********************************/
extern voisins_potentiels* allouer(unsigned char* ip, unsigned char *port);
extern voisins_potentiels* ajoutVP(voisins_potentiels* liste, unsigned char* ip, unsigned char *port);
extern void afficherListe(voisins_potentiels* liste);
extern bool recherche(voisins_potentiels* liste, unsigned char* ip);
extern short size(voisins_potentiels* liste);

/******************************************************************************************/
extern void helloCourt(unsigned char* tableau);
extern void helloLong(unsigned char* tableau);
extern void neighbor(unsigned char * tableau);
extern void dataTLV(unsigned char *tab, int taille);
extern void affiche(unsigned char tab[], int taille);
extern void afficher_message(unsigned char tab[], int taille);
extern void parserTLV(unsigned char tab[], int taille);

/**************************************Voisins Hello**************************************/
extern voisins* allouerVoisins(unsigned char* ip, unsigned char *port, unsigned char *source_id, int type);
// extern voisins* ajoutVoisins(voisins* liste, unsigned char* ip, unsigned char *port, unsigned char *source_id);
// extern void afficherListe(voisins* liste);
// extern bool recherche(voisins* liste, unsigned char* ip);
/******************************************************************************************/

#endif

