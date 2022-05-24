#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#define PORT_NUM 39999 // port number
#define BUFF_SIZE 1024  // buffer size

int check_url(int *hit_cnt, int *miss_cnt, int* process_cnt, char *tokenized_req);
void chld_handler(void);
void alrm_handler(void);
void int_handler(void);
char *get_ip_handler(char *addr);

int main()
{
    int serv_fd, cli_fd;
    int hit_cnt, miss_cnt, process_cnt, opt_val;

    struct sockaddr_in serv_addr, cli_addr;

    pid_t pid;

    hit_cnt = 0;
    miss_cnt = 0;
    process_cnt = 0;
    opt_val = 1;

    if (socket(PF_INET, SOCK_STREAM, 0) < 0) // create socket. IPv4 Internet protocal + TCP connection
    {
        printf("Server : Can't open stream socket\n");
        return (0);
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr)); // define socket addr of server side
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // convert host_byte_order to network_byte_order
    serv_addr.sin_port = htons(PORT_NUM);

    setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val)); // setting details for sockets

    if (bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr) < 0))
    {
        printf("Server : Can't bind local address\n");
        close(serv_fd);
        return (0);
    }

    listen(serv_fd, 5);
    signal(SIGCHLD, (void *)chld_handler); // prevent ended children becoming zombie state
    signal(SIGALRM, (void *)alrm_handler);
    signal(SIGINT, (void *)int_handler);
    while (1)
    {
        int len, is_hit;
        char *tok = NULL, *ip_addr;
        char http_req[BUFF_SIZE];
        char tmp[BUFF_SIZE] = {
            0,
        };
        char buf[BUFF_SIZE] = {
            0,
        };
        char url[BUFF_SIZE / 2] = {
            0,
        };
        char method[BUFF_SIZE] = {
            0,
        };
        char res_header[BUFF_SIZE] = {
            0,
        };
        char res_msg[BUFF_SIZE] = {
            0,
        };

        len = sizeof(cli_addr);
        memset((char *)&cli_addr, 0, len); // initialize memory

        cli_fd = accept(serv_fd, (struct sockaddr *)&cli_addr, &len);
        if (cli_fd < 0)
        {
            printf("Server : accept failed\n");
            close(serv_fd);
        }

        memset(res_header, 0, sizeof(res_header));
        memset(res_msg, 0, sizeof(res_msg));

        printf("[%s : %d] client was connected\n", inet_ntoa(cli_addr.sin_addr), cli_addr.sin_port);

        pid = fork();
        if (pid < 0)
        {
            printf("Server : fork failed\n");
            close(cli_fd);
        }

        if (pid == 0)
        {
            len = read(cli_fd, http_req, BUFF_SIZE); // Read data from clinet_fd and store it in variables
            strcpy(tmp, http_req);
            puts("===================================================");
            printf("Request from [%s : %d]\n", inet_ntoa(cli_addr.sin_addr), cli_addr.sin_port);
            puts(http_req);
            puts("===================================================");
            tok = strtok(tmp, " ");
            strcpy(method, tok);
            if (strcmp(method, "GET") == 0)
            {
                tok = strtok(NULL, " ");
                strcpy(url, tok);
            }

            is_hit = check_url(&hit_cnt, &miss_cnt, & process_cnt, url);
            
            if (is_hit == 1)
            {
                sprintf(res_msg,
                        "<h1>HIT</h1><br>"
                        "Hello %s:%d<br>"
                        "%s<br>"
                        "kw2018202076",
                        inet_ntoa(cli_addr.sin_addr), cli_addr.sin_port, url);
            }
            else
            {
                sprintf(res_msg,
                        "<h1>MISS</h1><br>"
                        "Hello %s:%d<br>"
                        "%s<br>"
                        "kw2018202076",
                        inet_ntoa(cli_addr.sin_addr), cli_addr.sin_port, url);

                int sock_fd = socket(PF_INET, SOCK_STREAM, 0); // create socket for IPv4, TCP
                if (sock_fd < 0)
                {
                    printf("Server : Can't open stream socket\n");
                    return (0);
                }
                tok = strtok(url, "://");
                tok = strtok(NULL, "/");
                ip_addr = get_ip_handler(tok);
                struct sockaddr_in addr_sock;
                bzero((char *)&addr_sock, sizeof(addr_sock)); // define socket addr of server side
                addr_sock.sin_family = AF_INET;
                addr_sock.sin_addr.s_addr = inet_addr(ip_addr);
                addr_sock.sin_port = htons(80);

                int is_connect = connect(sock_fd, (struct sockaddr *)&addr_sock, sizeof(addr_sock));
                if (is_connect < 0)
                {
                    printf("Server : connect failed\n");
                    close(sock_fd);
                }
                alarm(10);
                if (read(sock_fd, buf, BUFF_SIZE) > 0)
                    alarm(0);
            }
            sprintf(res_header,
                    "HTTP/1.0 200 ok\r\n"
                    "Server:2018 simple web server\r\n"
                    "Content-length:%lu\r\n"
                    "Content-type:text/html\r\n\r\n",
                    strlen(res_msg));
            write(cli_fd, res_header, strlen(res_header));
            write(cli_fd, res_msg, strlen(res_msg));
            write(cli_fd, http_req, len);

            printf("[%s : %d] client was disconnected\n\n", inet_ntoa(cli_addr.sin_addr), cli_addr.sin_port);

            bzero(http_req, sizeof(http_req));
            bzero(tmp, sizeof(tmp));
            bzero(url, sizeof(url));

            close(cli_fd);
        }

        close(cli_fd);
    }
}

void chld_handler(void)
{
    while ((waitpid(-1, NULL, WNOHANG)) > 0)
        ;
}

void alrm_handler(void)
{
    printf("\n\n========No Response========\n\n");
}

void int_handler(void)
{
    exit(0);
}

char *get_ip_handler(char *addr)
{
    struct hostent *hent;
    char *haddr;
    int len = strlen(addr);

    if ((hent = (struct hostent *)gethostbyname(addr)) != NULL)
        haddr = inet_ntoa(*((struct in_addr *)hent->h_addr_list[0]));

    return haddr;
}