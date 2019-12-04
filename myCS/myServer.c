#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8080
int main()
{
    int sfd; //服务端创建socket返回的fd
    struct sockaddr_in serv_addr, clien_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);
    //用TCP协议，因此选择 AF_INET,第三个参数为0，代表流式套接字默认为TCP
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(sfd, 128);
    socklen_t clie_addr_len;
    clie_addr_len = sizeof(clien_addr);
    //accept()返回一个新的fd,用来和客户端进行通信
    char client_IP[BUFSIZ]; //保存登录该服务端的客户端的ip
    int cfd = accept(sfd, (struct sockaddr*)&clien_addr, &clie_addr_len);
    printf("client IP:%s, client Port:%d\n",
	    inet_ntop(AF_INET,&clien_addr.sin_addr.s_addr,
		client_IP, sizeof(client_IP)), 
		ntohs(clien_addr.sin_port));
    char buf[BUFSIZ];
	int n = read(cfd, buf, sizeof(buf));
	for(int i = 0; i<n; ++i)
	{
	    buf[i] = toupper(buf[i]);
	}
	write(cfd, buf, n);
    close(sfd);
    close(cfd);
    return 0;
}

