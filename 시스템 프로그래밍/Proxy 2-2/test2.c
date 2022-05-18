#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#define PORTNO 39999
#define BUFFSIZE 1024

void handler(void)
{
    while ((waitpid(-1, NULL, WNOHANG)) > 0)
        ;
}

int main()
{
    /*main server process*/
    struct sockaddr_in server_addr, client_addr;
    int socket_fd, client_fd;
    int len;
    int state, opt = 1;
    char buf[BUFFSIZE] = {
        0,
    };
    char method[20] = {
        0,
    };
    char tmp[BUFFSIZE] = {
        0,
    };
    char url[BUFFSIZE] = {
        0,
    };
    char *tok;

    pid_t pid;

    // create socket
    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Server : Can't open stream socket\n");
        return 0;
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;                // IPv4 protocol
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 32bit address
    server_addr.sin_port = htons(PORTNO);            // 16-bit port number

    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // bind socket with sockaddr_in struct
    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Server : Can't bind local address\n");
        return 0;
    }
    // Change from client to standby for connection
    listen(socket_fd, 5);             // wait with queue whose size is 5
    signal(SIGCHLD, (void *)handler); // Installing the Signal Handler

    while (1)
    {
        bzero((char *)&client_addr, sizeof(client_addr));
        len = sizeof(client_addr);
        client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &len); // Server accepts client's connection
        if (client_fd < 0)
        {
            printf("Server : accept failed\n");
            return 0;
        }

        pid = fork();

        if (pid == -1) // error
        {
            close(client_fd);
        }
        if (pid == 0) // subprocess case
        {

            read(client_fd, buf, BUFFSIZE); // read request
            buf[strlen(buf) - 1] = 0;
            strcpy(tmp, buf);

            tok = strtok(tmp, " ");
            strcpy(method, tok);
            if (strcmp(method, "GET") == 0) // if GET method, extract url
            {
                tok = strtok(NULL, " ");
                strcpy(url, tok);
                printf("[%s : %d] client was connected\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
                SubServerProcess(client_fd, url, buf, client_addr); // start Subprocessor function
                printf("[%s : %d] client was disconnected\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
            }
            bzero(buf, sizeof(buf));
            bzero(tmp, sizeof(tmp));
            bzero(url, sizeof(url));
            close(client_fd);
        }
        close(client_fd);
    }
}