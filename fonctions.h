#ifndef FONCTIONS_H
#define FONCTIONS_H

unsigned char source_id_court[8], source_id_long[8], destination_id[8], ip[16], port[2],
sender_id[8], nonce[4], type[1], data[40];

/**********************************************/
extern void helloCourt(unsigned char* tableau);

/*********************************************/
extern void helloLong(unsigned char* tableau);

/*****************************************************/
extern void neighbor(unsigned char * tableau);

/****************************************************/
extern void dataTLV(unsigned char *tab, int taille);

/**************************************************/
extern void affiche(unsigned char tab[], int taille);

/**************************************************/
extern void afficher_message(unsigned char tab[], int taille);

/**************************************************/
extern void parserTLV(unsigned char tab[], int taille);
#endif

