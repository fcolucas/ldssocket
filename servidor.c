/*Arquivo Servidor!*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 2000
#define TAM 256

struct sockaddr_in local;
struct sockaddr_in remoto;

int create_socket(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd != -1){
        printf("Socket criado!\n");
        return sockfd;
    }else{
        perror("socket ");
        return 0;
    }
}

void setting_socket(struct sockaddr_in *local, int family, int port){
    local->sin_family = family;
    local->sin_port = htons(port);
    memset(local->sin_zero, 0x0, 8);
}

int connect_socket(int sockfd, struct sockaddr_in local, struct sockaddr_in remoto){
    int on = bind(sockfd, (struct sockaddr *)&local, sizeof(local));
    if(on == -1){
        perror("bind ");
        return 0;
    }

    on = listen(sockfd, 1);
    if(on == -1){
        perror("listen ");
        return 0;
    }
    printf("Aguardando cliente...\n");

    socklen_t len = sizeof(remoto);;
    int client = accept(sockfd, (struct sockaddr *)&remoto, &len);
    if(client==-1){
        perror("accept ");
        exit(1);
    }
    return client;
	printf("Cliente conectado!\n\n");
}

int main()
{
    int client, rec, env;
    char mensagem[TAM], resposta[TAM];

    int sockfd = create_socket();

    setting_socket(&local, AF_INET, PORT);
/*
    local.sin_family = AF_INET;
    local.sin_port = htons(PORTA);
    local.sin_addr.s_addr = inet_addr("192.168.254.1");
    memset(local.sin_zero, 0x0, 8);
*/
    client = connect_socket(sockfd, local, remoto);

/*
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
*/

    do{
        rec = recv(client, resposta, 256, 0);
        resposta[rec] = '\0';
        printf("Cliente: %s\n", resposta);

        /*printf("Servidor: ");*/
        fgets(mensagem, 256, stdin);
        mensagem[strlen(mensagem)-1] = '\0';
        env = send(client, mensagem, strlen(mensagem), 0);

        /*if(resposta[0]=='*') rec = -1;
        if(mensagem[0]=='*') env = -1;*/
	}while(rec != -1 && env != -1);

	close(client);
    close(sockfd);
    printf("Servidor Encerrado! \n");
    return 0;
}
