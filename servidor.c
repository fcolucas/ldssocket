/*Arquivo Servidor!*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORTA 2000
#define TAM 256

struct sockaddr_in local;
struct sockaddr_in remoto;

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t len = sizeof(remoto);
    int client, rec, env;
    char mensagem[TAM], resposta[TAM];

    if(sockfd == -1){
        perror("socket ");
        exit(1);
    }else{
        printf("Socket criado!\n");
    }

    local.sin_family = AF_INET;
    local.sin_port = htons(PORTA);
    /*local.sin_addr.s_addr = inet_addr("192.168.254.1");*/
    memset(local.sin_zero, 0x0, 8);

    if (bind(sockfd, (struct sockaddr *)&local, sizeof(local))==-1){
        perror("bind ");
        exit(1);
    }

    if(listen(sockfd, 1)==-1){
		perror("listen ");
		exit(1);
	}

	printf("Aguardando cliente...\n");

    client = accept(sockfd, (struct sockaddr *)&remoto, &len);
    if(client==-1){
        perror("accept ");
        exit(1);
    }
	printf("Cliente conectado!\n\n");

    do{
        rec = recv(client, resposta, 256, 0);
        resposta[rec] = '\0';
        printf("Cliente: %s\n", resposta);

        //printf("Servidor: ");
        fgets(mensagem, 256, stdin);
        mensagem[strlen(mensagem)-1] = '\0';
        env = send(client, mensagem, strlen(mensagem), 0);

        //if(resposta[0]=='*') rec = -1;
        //if(mensagem[0]=='*') env = -1;
	}while(rec != -1 && env != -1);

	close(client);
    close(sockfd);
    printf("Servidor Encerrado! \n");
    return 0;
}

