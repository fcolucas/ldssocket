//Arquivo Servidor!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORTA 2000
#define TAM 4096

struct sockaddr_in local;
struct sockaddr_in remoto;

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t len = sizeof(remoto);
    int slen, client;
    char buffer[TAM];

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

    if (bind(sockfd, (struct sockaddr *)&local, sizeof(local)) <0){
        perror("bind ");
        exit(1);
    }

    listen(sockfd, 1);

    client = accept(sockfd, (struct sockaddr *)&remoto, &len);
    if(client < 0){
        perror("accept ");
        exit(1);
    }

    strcpy(buffer, "Welcome!\n\0");

    if(send(client, buffer, TAM, 0)){
        printf("Aguardando resposta do cliente...\n");
        while(1){
            memset(buffer, 0x0, TAM);
            if((slen = recv(client, buffer, TAM, 0))>0){
                buffer[slen-1] = '\0';
                printf("Mensagem Recebida: %s\n", buffer);
                memset(buffer, 0x0, TAM);
                fgets(buffer, TAM, stdin);
                send(client, buffer, TAM, 0);
            }else{
                close(client);
                break;
            }
        }
    }

    close(sockfd);
    printf("Servidor Encerrado! \n");
    return 0;
}
