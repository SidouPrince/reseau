#include <unistd.h>

int main(int argc, char const *argv[])
{	
	int s = socket(AF_INET6, SOCK_DGRAM, 0);
	if (s < 0 )
	{
		printf("s est negatif\n");
	}
	struct sockaddr_in6 server;//adresse d'une socket
	memset(&server, 0, sizeof(server));
	server.sin6_family = AF_INET6;
	server.sin6_port = htons(1717);
	int rc = bind(s, (struct sockaddr*) &server, sizeof(server));
	
	if(rc < 0){
	    printf("Erreur\n");
	    exit(1);
	}
    while(1){
	char req[4096], reply[4096];
	struct sockaddr_in6 client;
	int client_len = sizeof(client);
	rc = recvfrom(s, req, 4096, 0, (struct sockaddr*)&client, &client_len);
	if(rc < 0) {
	    perror("recvfrom");continue;
    }
    strcpy(reply , "Bonjour");
    /* analyser la requête, construire la réponse */
    rc = sendto(s, reply, 4096, 0, (struct sockaddr*)&client, client_len);
    }	
return 0;
}
