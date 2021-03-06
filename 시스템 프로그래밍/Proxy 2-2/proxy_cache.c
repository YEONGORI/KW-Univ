#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#define PORT_NUM 39999
#define BUFFER_SIZE 1024

// int check_url(int *hit_cnt, int *miss_cnt, char *tokenized_req);
void sig_handler(void);

int main()
{
    int sock_fd_serv, sock_fd_client;
    int cnt_hit, cnt_miss;

    struct sockaddr_in addr_serv, addr_client;

    cnt_hit = 0;
    cnt_miss = 0;

    sock_fd_serv = socket(AF_INET, SOCK_STREAM, 0); // create socket for IPv4, TCP
    if (sock_fd_serv < 0)
    {
        printf("socket error\n");
        return (0);
    }

    memset(&addr_serv, 0, sizeof(addr_serv)); // define socket addr of server side
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_port = PORT_NUM;

    int is_bind = bind(sock_fd_serv, (struct sockaddr *)&addr_serv, sizeof(addr_serv)); // asscociate an address with a socket
    if (is_bind < 0)
    {
        printf("bind error\n");
        close(sock_fd_serv);
        return (0);
    }

    int is_listen = listen(sock_fd_serv, 5);
    if (is_listen < 0)
    {
        printf("listen error");
        close(sock_fd_serv);
        return (0);
    }

    signal(SIGCHLD, (void *)sig_handler); // prevent ended children becoming zombie state

    while (1)
    {
        int tmp, is_hit;
        char http_request[BUFFER_SIZE];
        char *method, *url;

        struct sockaddr_in inet_addr_client;
        inet_addr_client.sin_addr.s_addr = addr_client.sin_addr.s_addr;
        memset(&addr_client, 0, sizeof(addr_client));
        tmp = sizeof(addr_client);
        printf("@@@@\n");

        sock_fd_client = accept(sock_fd_serv, (struct sockaddr *)&addr_client, &tmp);
        printf("@@@\n");

        if (sock_fd_client < 0)
        {
            printf("accept error\n");
            close(sock_fd_serv);
            return (0);
        }
        printf("[%s : %d] client was connected\n", inet_ntoa(inet_addr_client.sin_addr), addr_client.sin_port);

        pid_t pid = fork();
        if (pid < 0)
        {
            printf("fork error\n");
            close(sock_fd_serv);
            close(sock_fd_client);
            continue;
        }

        if (pid == 0)
        {
            read(sock_fd_client, http_request, BUFFER_SIZE);
            puts("===================================================");
            printf("Request from [%s : %d]\n", inet_ntoa(inet_addr_client.sin_addr), addr_client.sin_port);
            puts(http_request);
            puts("===================================================");
            method = strtok(http_request, " ");
            if (strcmp(method, "GET") == 0)
                url = strtok(NULL, " ");
            else
                continue;
            // is_hit = check_url(&cnt_hit, &cnt_miss, url);
        }

        break;
    }
}

void sig_handler(void)
{
    while ((waitpid(-1, NULL, WNOHANG)) > 0)
        ;
}