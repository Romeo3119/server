#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8080

int main()
{
    int cfd; //与服务端进行通信的描述符
    struct sockaddr_in serv_addr;
    socklen_t serv_addr_len;
   cfd = socket(AF_INET, SOCK_STREAM, 0);
    //不推荐手动绑定
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);
    serv_addr_len = sizeof(serv_addr);

    connect(cfd, (struct sockaddr*)&serv_addr, serv_addr_len);
    char buf[BUFSIZ];
    fgets(buf, sizeof(buf), stdin);
    write(cfd, buf, strlen(buf));
    int n = read(cfd, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, n);
    close(cfd);

    return 0;
}
