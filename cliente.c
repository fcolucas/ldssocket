//Arquivo Cliente!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORTA 2000
#define TAM 300

struct sockaddr_in remoto;

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t len = sizeof(remoto);
    int slen, rec, env;
    char mensagem[TAM], resposta[TAM];
    char ip[32];
    strcpy(ip, "127.0.0.1");

    if(sockfd == -1){
        perror("socket ");
        exit(1);
    }else{
        printf("Socket criado!\n");
    }

    remoto.sin_family = AF_INET;
    remoto.sin_port = htons(PORTA);
	inet_pton(AF_INET, ip, &remoto.sin_addr);
    memset(remoto.sin_zero, 0x0, 8);

    if(connect(sockfd, (struct sockaddr *)&remoto, len) < 0){
        perror("connect ");
        exit(1);
    }

    printf("Conectado!\n\n");

    do{
        //printf("Cliente: ");
        fgets(mensagem, 256, stdin);
        mensagem[strlen(mensagem)-1] = '\0';
        env = send(sockfd, mensagem, strlen(mensagem), 0);

        //if(resposta[0]=='*') rec = -1;
        //if(mensagem[0]=='*') env = -1;

        rec = recv(sockfd, resposta, 256, 0);
        resposta[rec] = '\0';
        printf("Servidor: %s\n", resposta);
    }while(rec != -1 && env != -1);

    close(sockfd);
    printf("Cliente Encerrado! \n");
    return 0;
}

