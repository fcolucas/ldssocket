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
#define TAM 4096

struct sockaddr_in remoto;

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t len = sizeof(remoto);
    int slen;
    char buffer[TAM];
    char ip[32];
    strcpy(ip, "127.0.0.1");

 	printf("Sou o cliente!\n");

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

        while(1){
            if((slen = recv(sockfd, buffer, TAM, 0))>0){
                buffer[slen-1] = '\0';
                printf("Mensagem Recebida: %s\n", buffer);
            }
			memset(buffer, 0x0, TAM);
			fgets(buffer, TAM, stdin);
			send(sockfd, buffer, TAM, 0);
        }

    close(sockfd);
    printf("Cliente Encerrado! \n");
    return 0;
}
