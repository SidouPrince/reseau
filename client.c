#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include "fonctions.h"


#define ADRESSE "81.194.27.155"
#define ADRESSEE "192.168.43.47"


int main(int argc, char const *argv[]){
    int s = socket(PF_INET6, SOCK_DGRAM, 0);
    if ( s < 0 )
    {
    	printf("socket");
	exit(EXIT_FAILURE);
    }

/***********************************************************************/

    //declarer la structure sockadd_in6 pour stokcer les infos du serveur
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(1212);
    server.sin_addr.s_addr = inet_addr(ADRESSE);
    /***********************************************/
    
    unsigned char req[14];	
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
 //    // req[14] = 103;
 //    // req[15] = 125;
 //    // req[16] = 198;
 //    // req[17] = 35;
 //    // req[18] = 77;
 //    // req[19] = 39;
 //    // req[20] = 99;
 //    // req[21] = 181;
 //    // req[22] = 3; //magic
 //    // req[23] = 18; //version
 //    // req[24] = 0;//source_id
 //    // req[25] = 0; //source_id
 //    // req[26] = 0;
 //    // req[27] = 0;
 //    // req[28] = 0;
 //    // req[29] = 0;
 //    // req[30] = 0;
 //    // req[31] = 0;
 //    // req[32] = 0;
 //    // req[33] = 0;
 //    // req[34] = 255;
 //    // req[35] = 255;
 //    // req[36] = 192;
 //    // req[37] = 168;
 //    // req[38] = 43;
 //    // req[39] = 47;
 //    // req[40] = 0;
 //    // req[41] = 22;
    unsigned int taille_server = sizeof(server);
    int send = sendto(s, req, 14, 0, (struct sockaddr *)&server, taille_server);
    if (send < 0)
    {
    	printf("sendto \n");
	exit(EXIT_FAILURE);
    }
    printf("message envoyé !!\n");
    unsigned char reponse[1024];
    int recv = recvfrom(s, reponse, 1024, 0, (struct sockaddr*)&server, &taille_server);
    
    if ( recv < 0 )
    {
    	printf("recvfrom \n");
	exit(EXIT_FAILURE);
    }
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