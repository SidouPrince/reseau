#include <stdio.h> 
#include <arpa/inet.h> 
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <stdlib.h> //exit
#include <unistd.h> //close
#include <string.h>
#include <netdb.h>
#include <time.h>
#include "fonctions.h"

#define SERVER "81.194.27.155"


int main(int argc, char const *argv[]){
    int s = socket(PF_INET, SOCK_DGRAM, 0);
    if ( s < 0 )
    {
    	printf("socket");
	exit(EXIT_FAILURE);
    }

/***********************************************************************/

    //declarer la structure sockadd_in pour stokcer les infos du serveur
    struct sockaddr_in server;
    

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER);
    server.sin_port = htons(1212);
    /***********************************************/
    
    unsigned char req[4096];	
    //remplir le datagramme avec le tlv hello
    req[0] = 93; //magic
    req[1] = 2; //version
    req[2] = 0; //body_length
    req[3] = 10; //car le champ body_legnth est de 2 octets
    req[4] = 2; //type tlv hello
    req[5] = 8; //taille tlv hello
    req[6] = 178;//source_id
    req[7] = 154; //source_id
    req[8] = 123;
    req[9] = 10;
    req[10] = 1;
    req[11] = 1;
    req[12] = 1;
    req[13] = 1;
 
    socklen_t taille_server = sizeof(server);
    
    int send = sendto(s, req, 100, 0, (struct sockaddr *)&server, taille_server);
    if (send < 0)
    {
    	printf("sendto \n");
	exit(EXIT_FAILURE);
    }
    
    printf("message envoyé !!\n");

/*********************************************************************************************/
    unsigned char reponse[4096];
    struct sockaddr_in emetteur;
    socklen_t taille_emetteur = sizeof emetteur;
    //memset(&emetteur, 0, sizeof(emetteur));
    emetteur.sin_family = AF_INET;

    int recv = recvfrom(s, reponse, 4096, 0, (struct sockaddr *) &emetteur, &taille_emetteur);
    
    char ip[16];

    inet_ntop(AF_INET, &emetteur.sin_addr, ip, sizeof(ip));
    printf("%s\n",ip);//0.0.0.0

    if ( recv < 0 )
    {
    	printf("recvfrom \n");
	exit(EXIT_FAILURE);
    }
    /******************************************************************************************/


    printf("message recu !\n");
    int leng = reponse[3];
    printf("la longueur  %d\n", leng);
    for (int i = 4; i < leng+4; ++i)
    {
    	printf("%.2d : ", reponse[i] );
    }
    printf("\n");
    /*******************parserTLV****************************/
    parserTLV(&reponse[4], reponse[3]);

    close(s);
    return 0;
}