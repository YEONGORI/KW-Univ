#include <sys/socket.h>     //socket
#include <netinet/in.h>
#include <signal.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>          //sprintf()
#include <string.h>         //strcpy()
#include <openssl/sha.h>    //SHA1()
#include <stdbool.h>        //bool

//fork
#include <sys/wait.h>
#include <unistd.h>

//getHomeDirectory
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

//mkdir
#include <sys/stat.h>

//creat
#include <fcntl.h>

//opendir, readdir
#include <dirent.h>

//localtime
#include <time.h>



#define BUFFSIZE 1024
#define PORTNO 39999

static void handler()
{
    pid_t pid;
    int status;
    while((pid = waitpid(-1, &status, WNOHANG))>0);
}


//////////////////////////////////////////////////////////////
// sha1_hash                                                //
// ======================================================== //
// Input: char* -> Input Url                                //
// Output: char* -> Hashed Url                              //
// Purpose: Hashing Url with SHA1                           //
//////////////////////////////////////////////////////////////

char *sha1_hash(char *input_url, char *hashed_url){
    unsigned char hashed_160bits[20];
    char hashed_hex[41];
    int i;

    SHA1(input_url, strlen(input_url),hashed_160bits);

    for(i=0; i<sizeof(hashed_160bits); i++)
        sprintf(hashed_hex + i*2, "%02x", hashed_160bits[i]);
    
    strcpy(hashed_url, hashed_hex);

    return hashed_url;
}

//////////////////////////////////////////////////////////////
// getHomeDir                                               //
// ======================================================== //
// Input: -                                                 //
// Output: char* -> Home Directory Path                     //
// Purpose: Get Home Directory Path                         //
//////////////////////////////////////////////////////////////

char *getHomeDir(char *home) {
    struct passwd *usr_info = getpwuid(getuid());
    strcpy(home, usr_info->pw_dir);
    
    return home;
}

//////////////////////////////////////////////////////////////
// getUrl                                                   //
// ======================================================== //
// Input: homeDir, mkdirPath, logfilePath, FILE* fp         //
// Output: char[] result ( HIT or MISS)                     //
// Purpose: Get URL, Write logfile, Make Cache              //
//////////////////////////////////////////////////////////////

const char* getUrl(int* countHit, int* countMiss,char URL[], char homeDir[],char mkdirPath[], char logfilePath[]){
    FILE* fp;                               //make txt file
    char temp[100];
    char hashedUrl[100];
    char inputUrl[100];
    char *ptr;
    sprintf(inputUrl,"%s",strtok(URL,"\n"));
    ptr=strtok(inputUrl,"://");
    ptr=strtok(NULL,"://");
    strcpy(inputUrl,ptr);
    char firstThree[4];
    
    char fileName[100];

    char systemMessage[400];
    int isExistFile=0;

    struct tm *date;
    time_t t = time(NULL);
    
    DIR* dirCur=NULL;
    struct dirent* fileCur = NULL;

    bzero(systemMessage,sizeof(systemMessage));
    strcpy(mkdirPath,homeDir);
    strcat(mkdirPath,"/cache");         //set Path
        
    sha1_hash(inputUrl, hashedUrl);        //hasing with sha1

    firstThree[0]=hashedUrl[0];         //cut front three char
    firstThree[1]=hashedUrl[1];
    firstThree[2]=hashedUrl[2];
    firstThree[3]='\0';
    strcat(mkdirPath,"/");
    strcat(mkdirPath,firstThree);
    umask(0);
    mkdir(mkdirPath, S_IRWXU | S_IRWXG | S_IRWXO);  //create directory    
    dirCur=opendir(mkdirPath);

    int j =0;
    while(1)
    {
        fileName[j]=hashedUrl[j+3];     //make filename from hashedUrl[3~]
        if(hashedUrl[j+3]=='\0'){
            break;
        }
        j++;
    }

    strcat(mkdirPath,"/");
    strcat(mkdirPath,fileName);    

    while((fileCur=readdir(dirCur))!= NULL)
    {
        if(strcmp(fileCur->d_name,fileName)==0) //already exist
        {
            isExistFile=1;
            break;
        }
    }

    if(isExistFile==0)                        //MISS
    {
        (*countMiss)++;
        creat(mkdirPath, 0777);             //create file
        //write Miss info at logfile.txt
        t = time(NULL);
        date = localtime(&t);
        sprintf(systemMessage,"[Miss] ServerPID : %d | %s-[%d/%d/%d, %d:%d:%d]\n",getpid(),inputUrl,date->tm_year+1900,date->tm_mon+1,date->tm_mday,date->tm_hour,date->tm_min,date->tm_sec);
        fp= fopen(logfilePath,"a+");
        fputs(systemMessage, fp);           //write logfile
        fclose(fp); 
        return("MISS\0");
    }
    else                                        //HIT
    {
        (*countHit)++;
        //write Hit info at logfile.txt
        t = time(NULL);
        date = localtime(&t);
        sprintf(systemMessage,"[Hit] ServerPID : %d | %s/%s-[%d/%d/%d, %d:%d:%d]\n[Hit]%s\n"pid(),firstThree, fileName,date->tm_year+1900,date->tm_mon+1,date->tm_mday,date->tm_hour,date->tm_min,date->tm_sec,inputUrl);
        fp= fopen(logfilePath,"a+");
        fputs(systemMessage, fp);           //write logfile
        fclose(fp);
        return("HIT\0");
    }
        
}

int main()
{
    struct sockaddr_in server_addr, client_addr;
    int socket_fd, client_fd;
    int len, len_out;
    int state;
    int Hit =0;
    int Miss =0;
    int* countHit=&Hit;
    int* countMiss=&Miss;
    char buf[BUFFSIZE];
    char systemMessage[100];
    pid_t pid;


    time_t startTime, endTime;
    char homeDir[100];
    char mkdirPath[100];
    char logfilePath[100];
    
    
    getHomeDir(homeDir);                            //save home directory
    strcpy(mkdirPath,homeDir);
    strcpy(logfilePath,homeDir);
    strcat(mkdirPath,"/cache");
    strcat(logfilePath,"/logfile");
    umask(0);                                       //set umask
    mkdir(mkdirPath,S_IRWXU | S_IRWXG | S_IRWXO);   //create cache directory
    mkdir(logfilePath,S_IRWXU | S_IRWXG | S_IRWXO); //create logfile directory

    strcat(logfilePath,"/logfile.txt");
    FILE* fp; 

    if((socket_fd = socket(PF_INET, SOCK_STREAM, 0))<0){
        printf("Server: Can't open stream socket.");
        return 0;
    }

    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;                   //set socket address
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORTNO);
    if(bind(socket_fd, (struct sockaddr *)&server_addr,sizeof(server_addr))<0){     //binding server
        printf("Server: Can't bind local address.\n");
        close(socket_fd);
        return 0;
    }
    listen(socket_fd, 5);
    signal(SIGCHLD,(void*)handler);

    while(1)
    {
        bzero((char*)&client_addr, sizeof(client_addr));
        
        struct in_addr inet_client_address;
        char response_header[BUFFSIZE]={0, };
        char response_message[BUFFSIZE] ={0, };
        char tmp[BUFFSIZE] = {0,};
        char method[20] = {0, };
        char url[BUFFSIZE] ={0,};
        char *tok = NULL;
        char result[10]={0,};


        len = sizeof(client_addr);
        client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &len);        //accept client

        if(client_fd < 0)
        {
            printf("Server : accept failed  %d\n", getpid());
            close(socket_fd);
            return 0;
        }
        startTime = time(NULL);                                     //if connected with client, start timer
        inet_client_address.s_addr = client_addr.sin_addr.s_addr;
        u_int ipAddress=ntohl(client_addr.sin_addr.s_addr);
        printf("[%d.%d.%d.%d : %d] client was connected\n", ipAddress>>24, (u_char)(ipAddress>>16),(u_char)(ipAddress>>8),(u_char)(ipAddress),client_addr.sin_port);
        pid=fork();
        
    
        if(pid==-1)
        {
            close(client_fd);
            close(socket_fd);
            continue;
        }
        if(pid==0)
        {
            read(client_fd, buf, BUFFSIZE);
            strcpy(tmp, buf);
            puts("================================================");
            printf("Request from [%s : %d]\n", inet_ntoa(inet_client_address), client_addr.sin_port);
            puts(buf);
            puts("================================================");
            tok = strtok(tmp, " ");
            strcpy(method, tok);
            if(strcmp(method, "GET")==0)
            {
                tok=strtok(NULL," ");
                strcpy(url, tok);
            }
            strcpy(result,getUrl(countHit, countMiss, buf, homeDir, mkdirPath, logfilePath));      //getUrl and write logfile
            if(strcmp("HIT",result)==0)                                     //if HIT
            {
                sprintf(response_message,
                "<h1>HIT</h1><br>"
                "Hello %s:%d<br>"
                "%s<br>"
                "kw2018202048", inet_ntoa(inet_client_address), client_addr.sin_port, url);
            }
            else{                                                           //if MISS
                sprintf(response_message,
                "<h1>MISS</h1><br>"
                "Hello %s:%d<br>"
                "%s<br>"
                "kw2018202048", inet_ntoa(inet_client_address), client_addr.sin_port, url);
            }
            sprintf(response_header,
                "HTTP/1.0 200 ok\r\n"
                "Server:2018 simple web server\r\n"
                "Content-length:%lu\r\n"
                "Content-type:text/html\r\n\r\n", strlen(response_message));
            write(client_fd, response_header, strlen(response_header));     //send header
            write(client_fd, response_message, strlen(response_message));   //send message

            printf("[%s : %d] client was disconnected\n", inet_ntoa(inet_client_address), client_addr.sin_port);
            close(client_fd);

            endTime=time(NULL); 
            sprintf(systemMessage,"[Terminated] ServerPID : %d | run time: %d sec. #request hit : %d, miss : %d\n",getpid(), (int)(endTime-startTime),Hit, Miss);
            fp = fopen(logfilePath,"a+"); 
            fputs(systemMessage,fp);
            fclose(fp);
            exit(0);
        }
        close(client_fd);
    }
    close(socket_fd);
    fclose(fp);

    return 0;
}