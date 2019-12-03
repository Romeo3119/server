#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <ctype.h>
#include <arpa/inet.h>


#define SERV_PORT 6666
#define SERV_IP "127.0.0.1"
int main(void)
{
    int lfd;
    int cfd; //accept()的返回值
    struct sockaddr_in serv_addr, clie_addr;
    socklen_t clie_addr_len;
    char buf[BUFSIZ];


    //创建socket
    lfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    //本地字节序转换为网络字节序
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    //最大上限为128
    listen(lfd, 128);
    //接收一个连接，返回新的文件描述符
    clie_addr_len = sizeof(clie_addr);
    //accept:参数2为传入参数，参数3为传入传出参数
    cfd = accept(lfd,(struct sockaddr*) &clie_addr, &clie_addr_len);

   int n =  read(cfd, buf, sizeof(buf));
   //小写转大写
   for(int i = 0; i<n; ++i)
   {
       buf[i] = toupper(buf[i]);
   }
   write(cfd, buf, n);
   close(lfd);
   close(cfd);
    return 0;
}
