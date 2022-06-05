#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pwd.h>
#include <dirent.h>
#include <pthread.h>

#define PORT_NUM 39999 // port number
#define BUFF_SIZE 1024 // buffer size

int check_url(int *hit_cnt, int *miss_cnt, int *process_cnt, char *url, char *http_req);
void chld_handler(void);
void alrm_handler(void);
void int_handler(void);
char *get_ip_handler(char *addr);
char *getHomeDir(char *home);
void repeat(int semid);
int p(int semid);
int v(int semid);
void *thread_routine(int pid);

int main()
{
    int serv_fd, cli_fd, semid, idx;
    int hit_cnt, miss_cnt, process_cnt, opt_val;

    struct sockaddr_in serv_addr, cli_addr;

    pid_t pid;
    union semun
    {
        int val;
        struct semid_ds *buf;
        unsigned short int *array;
    } arg;

    hit_cnt = 0;
    miss_cnt = 0;
    process_cnt = 0;
    opt_val = 1;

    if ((semid = semget((key_t)PORT_NUM, 1, IPC_CREAT | 0666)) == -1)
    { // create semaphore
        perror("semget failed");
        exit(1);
    }

    arg.val = 1; // set semaphore value to 1
    if ((semctl(semid, 0, SETVAL, arg)) == -1)
    { // set the initial value of the semaphore
        perror("semctl failed");
        exit(1);
    }

    serv_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_fd < 0) // create socket. IPv4 Internet protocal + TCP connection
    {
        printf("Server : Can't open stream socket\n");
        return (0);
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr)); // define socket addr of server side
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // convert host_byte_order to network_byte_order
    serv_addr.sin_port = htons(PORT_NUM);          // convert short_integer to networ_byte_order

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
        pthread_t tid;
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

        pid = fork();
        if (pid < 0)
        {
            printf("Server : fork failed\n");
            close(cli_fd);
        }

        if (pid == 0)
        {

            printf("*PID# %d is waiting for the semaphore.\n", getpid());
            p(semid); // start critical zone
            // sleep(5);
            printf("*PID# %d is in the critical zone.\n", getpid());
            if (pthread_create(&tid, NULL, thread_routine((int)getpid()), NULL) < 0)
            {
                printf("Thread: create failed\n");
            }

            len = read(cli_fd, http_req, BUFF_SIZE); // Read data from clinet_fd and store it in variables
            strcpy(tmp, http_req);
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

            tok = strtok(http_req, " ");
            tok = strtok(NULL, "//");
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
            is_hit = check_url(&hit_cnt, &miss_cnt, &process_cnt, url, http_req);

            v(semid); // end critical zone
            printf("*PID# %d exited the critical zone.\n", getpid());
            if (is_hit == 1)
                ;
            else
            {
                alarm(10);
                if (read(sock_fd, buf, BUFF_SIZE) > 0)
                    alarm(0);
            }

            send(sock_fd, http_req, strlen(http_req), 0);
            while ((len = recv(sock_fd, tmp, BUFF_SIZE - 1, 0)) > 0)
            {
                tmp[len] = '\0';
                write(cli_fd, tmp, len);
            }

            memset(http_req, 0, sizeof(http_req));
            memset(tmp, 0, sizeof(tmp));
            memset(url, 0, sizeof(url));

            close(cli_fd);
        }

        close(cli_fd);
    }
}

void *thread_routine(int pid)
{
    pthread_t tid;

    tid = pthread_self();
    printf("*PID# %d create the  *TID# %d\n", pid, tid);
}

int p(int semid)
{ // wait
    struct sembuf pbuf;

    pbuf.sem_num = 0;
    pbuf.sem_op = -1;
    pbuf.sem_flg = SEM_UNDO;
    if ((semop(semid, &pbuf, 1)) == -1)
    {
        perror("p : semop failed");
        exit(1);
    }
    else
    {
        return 1;
    }
}

int v(int semid)
{ // quit
    struct sembuf vbuf;

    vbuf.sem_num = 0;
    vbuf.sem_op = 1;
    vbuf.sem_flg = SEM_UNDO;
    if ((semop(semid, &vbuf, 1)) == -1)
    {
        perror("v : semop failed");
        exit(1);
    }
    else
    {
        return 1;
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
