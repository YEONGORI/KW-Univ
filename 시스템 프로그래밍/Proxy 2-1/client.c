#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int clinet_sock;
    struct sockaddr_in server_addr;
    
    clinet_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clinet_sock == -1) {
        printf("socket error\n");
        return (0);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr
}