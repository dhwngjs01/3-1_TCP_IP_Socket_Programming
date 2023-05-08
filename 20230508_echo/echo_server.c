#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    // 1. socket()
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        error_handling("socket() error");
    }

    // 2. bind()
    memset(&serv_adr, 0, sizeof(serv_adr)); // 0으로 초기화
    serv_adr.sin_family = AF_INET; // IPv4
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); // IP 주소
    serv_adr.sin_port = htons(atoi(argv[1])); // 포트번호

    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    

    // 3. listen()
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");
    

    // 4. accept()
    clnt_adr_sz = sizeof(clnt_adr);

    for(i=0; i<5; i++){
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if(clnt_sock == -1){
            error_handling("accept() error");
        }else{
            printf("Connected client %d \n", i+1);
        }

        // 5. read(), write()
        while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0){
            write(clnt_sock, message, str_len);
            message[str_len] = 0;
            printf("%s \n", message);
        }

        close(clnt_sock);
    }

    // 6. close()
    close(serv_sock);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}