#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pwd.h>
#include <dirent.h>


#define PORT_NUM 39999 // port number
#define BUFF_SIZE 1024  // buffer size

int check_url(int *hit_cnt, int *miss_cnt, int* process_cnt, char *tokenized_req);
void chld_handler(void);
void alrm_handler(void);
void int_handler(void);
char *get_ip_handler(char *addr);
char *getHomeDir(char *home);

FILE *get_logfile() {
        int is_cache_exist = 0, is_logfile_exist = 0;
        char home_dir[1024];
        char dir_name[256] = {"0"};
        char file_name[256] = {"0"}; // actual file name

        FILE *f = NULL;
        DIR *dir = NULL; // directory pointer declaration
        struct dirent *dir_entry = NULL, *file = NULL;

        start_time = time(NULL); // Start recording program running time

        getHomeDir(home_dir); // Get Home Directory Path

        // Code to create cache or logfile directories if cache or logfile directories do not exist
        // from here
        dir = opendir(home_dir); // Open the Home Directory

        while ((dir_entry = readdir(dir)) != NULL)
        { // Check that the cache and logfile directories are in the Home directory.
                if (strcmp(dir_entry->d_name, "cache") == 0)
                {
                    is_cache_exist = 1;
                }
                if (strcmp(dir_entry->d_name, "logfile") == 0)
                {
                        is_logfile_exist = 1;
                }
        }

        if (is_cache_exist == 0)
        { // Make cache Directory
                char tmp[256];
                strcpy(tmp, home_dir);
                strcat(tmp, "/cache");
                makeDir(tmp);
        }
        if (is_logfile_exist == 0)
        { // Make logfile Directory and logfile.txt File
                char tmp[256];
                strcpy(tmp, home_dir);
                strcat(tmp, "/logfile");
                makeDir(tmp);
                makeFile(tmp, "logfile.txt");
        }
        // to here

        // open logfile.txt
        char tmp2[1024];
        strcpy(tmp2, home_dir);
        strcat(tmp2, "/logfile/logfile.txt");
        f = fopen(tmp2, "w+");
        return (f);
}

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

    time_t current_time, start_time, end_time;
    struct tm *local_time;
    time(&current_time);
    local_time = localtime(&current_time); // Calculate the seconds that have passed so far and save them as local time in struct tm format
    if (local_time == NULL)
    {
            printf("plocal Error Occur!\n");
            return 0;
    }

    FILE *f = get_logfile();

    serv_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_fd < 0) // create socket. IPv4 Internet protocal + TCP connection
    {
        printf("Server : Can't open stream socket\n");
        return (0);
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr)); // define socket addr of server side
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // convert host_byte_order to network_byte_order
    serv_addr.sin_port = htons(PORT_NUM); // convert short_integer to networ_byte_order

    setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val)); // setting details for sockets

    int is_bind = bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)); // bind to server_address and server_fd
    if (is_bind < 0)
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
        struct sockaddr_in addr_sock;

        int len, is_hit, sock_fd;
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

        len = sizeof(cli_addr);
        memset((char *)&cli_addr, 0, len); // initialize memory

        cli_fd = accept(serv_fd, (struct sockaddr *)&cli_addr, &len);
        if (cli_fd < 0)
        {
            printf("Server : accept failed\n");
            close(serv_fd);
        }


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

            sock_fd = socket(PF_INET, SOCK_STREAM, 0); // create socket for IPv4, TCP
            if (sock_fd < 0)
            {
                printf("Server : Can't open stream socket\n");
                return (0);
            }
            tok = strtok(url, "://");
            tok = strtok(NULL, "/");
            ip_addr = get_ip_handler(tok);
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

            is_hit = check_url(&hit_cnt, &miss_cnt, & process_cnt, url);
            if (is_hit == 1)
                ;
            else
            {
                alarm(10);
                if (read(sock_fd, buf, BUFF_SIZE) > 0)
                    alarm(0);
            }

            send(sock_fd, http_req, strlen(http_req), 0);
            while ((len = recv(sock_fd, tmp, BUFF_SIZE - 1, 0)) > 0) {
                tmp[len] = '\0';
                write(cli_fd, tmp, len);
            }

            printf("[%s : %d] client was disconnected\n\n", inet_ntoa(cli_addr.sin_addr), cli_addr.sin_port);

            memset(http_req, 0, sizeof(http_req));
            memset(tmp, 0, sizeof(tmp));
            memset(url, 0, sizeof(url));

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