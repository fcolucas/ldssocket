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
#define TRUE 1
#define FALSE 0

struct sockaddr_in remoto;

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t len = sizeof(remoto);
    int slen, rec, sair = FALSE;
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

    rec = recv(sockfd, resposta, TAM, 0);
    resposta[rec] = '\0';
    printf("Servidor: %s\n", resposta);
    printf("Ponha * para mandar uma mensagem. Escreva # para terminar a conexao\n");

    do{
        printf("Escreva sua mensagem: ");
        do{
            fgets(mensagem, TAM, stdin);
            mensagem[strlen(mensagem)-1] = '\0';
            send(sockfd, mensagem, strlen(mensagem), 0);
            if(*mensagem == '#'){
                send(sockfd, mensagem, strlen(mensagem), 0);
                *mensagem = '*';
                sair = TRUE;
            }
        }while(*mensagem != '*');

        do{
            rec = recv(sockfd, resposta, TAM, 0);
            resposta[rec] = '\0';
            printf("Servidor: %s\n", resposta);
            if(*resposta == '#'){
                *resposta = '*';
                sair = TRUE;
            }
        }while(*resposta != '*');
    }while(!sair);

    close(sockfd);
    printf("Cliente Encerrado! \n");
    return 0;
}


