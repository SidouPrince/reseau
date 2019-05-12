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
#include "fonctions.c"

#define SERVER "81.194.27.155"
#define ME "192.168.43.47"

int main(int argc, char const *argv[]){
    //initialisation id
    generationID(my_id);


    



/***********************************************************************/
    int s = socket(PF_INET, SOCK_DGRAM, 0);
    if ( s < 0 )
    {
    	printf("socket");
	exit(EXIT_FAILURE);
    }


    pid_t pid = fork();
    if ( pid == 0 )//on est dans le fils
    {
	struct sockaddr_in potentiel;
	memset(&potentiel, 0, sizeof(potentiel));
	printf("je suis dans le fils\n");
	    if (listeVoisins == NULL)
	    {
	    	printf("listeVoisins est egale NULL\n");
	    }
	while(1){
	    sleep(10);
	    printf("le nombre de voisins symetrique est %d\n", recherche_symetrique());
	    if ( recherche_symetrique() >= 2 )
	    {
		while( liste != NULL ){
		     printf("je suis dasn le while\n");
		    inet_pton(AF_INET, (const char*)liste->ip, &potentiel.sin_addr);
		    uint16_t port = liste->port;
		    potentiel.sin_port = htons(port);
		    unsigned char r[4096];	
		    //remplir le datagramme avec le tlv hello
		    r[0] = 93; //magic
		    r[1] = 2; //version
		    r[2] = 0; //body_length
		    r[3] = r[3] + 10;
		    envoiHelloCourt(&r[4], my_id);
		    socklen_t taille_potentiel = sizeof(potentiel);

		    int send = sendto(s, r, 100, 0, (struct sockaddr *)&potentiel, taille_potentiel);
		    if (send < 0)
		    {
			printf("sendto \n");
			exit(EXIT_FAILURE);
		    }
    
		    printf("message envoyé hello court voisins potentiels !!\n");			
		}
	    }
	}
    }
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
    req[3] = req[3] + 10;
    envoiHelloCourt(&req[4], my_id);
 
    socklen_t taille_server = sizeof(server);
    
    int send = sendto(s, req, 100, 0, (struct sockaddr *)&server, taille_server);
    if (send < 0)
    {
    	printf("sendto \n");
	exit(EXIT_FAILURE);
    }
    
    

/*********************************************************************************************/
    unsigned char reponse[4096];
    struct sockaddr_in emetteur;
    socklen_t taille_emetteur = sizeof(emetteur);
    memset(&emetteur, 0, sizeof(emetteur));
    emetteur.sin_family = AF_INET;

    while(1){
	// int send = sendto(s, req, 100, 0, (struct sockaddr *)&server, taille_server);
	// printf("message envoyé !!\n");
 //    if (send < 0)
 //    {
 //    	printf("sendto \n");
	// exit(EXIT_FAILURE);
 //    }
    int recv = recvfrom(s, reponse, 4096, 0, (struct sockaddr *) &emetteur, &taille_emetteur);
    
    unsigned char src_ip[16];
    unsigned char src_port[2];

    inet_ntop(AF_INET, &emetteur.sin_addr, (char *) ip, sizeof(ip));

    printf("%s\n",ip);//0.0.0.0
    printf("%d\n", ntohs(emetteur.sin_port));

    if ( recv < 0 )
    {
    	printf("recvfrom \n");
	exit(EXIT_FAILURE);
    }

    /*******************parserTLV****************************/
    parserTLV(&reponse[4], reponse[3], src_ip, src_port);
}
    close(s);

    return 0;
}