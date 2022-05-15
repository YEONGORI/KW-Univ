//////////////////////////////////////////////////////////////////
// File Name		: proxy_cache.c				//
// Date			: 2022/04/05				//
// Os			: Ubuntu 16.04 LTS 64bits		//
// Author		: Lee Yeon Geol				//
// Student ID		: 2018202076				//
// ------------------------------------------------------------	//
// Title : System Programming Assignment #1-3 (proxy server)	//
// Description : separate Parent Process and Child Process and  //
// do what I did in Proxy1-2 in Child Process.                  //
//////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>

//////////////////////////////////////////////////////////////////
// sha1_hash							//
// ============================================================ //
// Input: char* -> input_url,					//
//	  char* -> hashed_url,					//
//	  Descrpition: input_url is the url which is input from //
//		       user and hashed_url is the string pointe //
//		       r in which the hashed url contains.	//
// Output: char* hashed_url					//
//	   Descrpition: hashedurl				//
// Purpose: To hash url using SHA1				//
//////////////////////////////////////////////////////////////////
char *sha1_hash(char *input_url, char *hashed_url) {
	unsigned char hashed_160bits[20];
	char hashed_hex[41];
	int i;
	
	SHA1(input_url, strlen(input_url), hashed_160bits); // hash url to 160 bits
		
	for(i=0; i < sizeof(hashed_160bits); i++) {
		sprintf(hashed_hex + i*2, "%02x", hashed_160bits[i]); // Insert hashed url into the hashed_hex variable in hexadecimal
	}

	strcpy(hashed_url, hashed_hex); // Copy the hashed url, which has been changed to a hexadecimal number, to the return value
	return hashed_url;
}


//////////////////////////////////////////////////////////////////
// getHomeDir							//
// ============================================================ //
// Input: char* -> home						//
//	  Descrpition: Empty variables that are expected to con	//
//		       tain Home Directory paths		//
// Output: char* -> home					//
//	   Descrpition: variable containing Home Directory path //
// Purpose: To find the Home directory path without using absol //
//          ute paths.						//
//////////////////////////////////////////////////////////////////
char *getHomeDir(char *home) {
	struct passwd *usr_info = getpwuid(getuid()); // Get the current uid and initialize the usr_info field of the structure passwd
	strcpy(home, usr_info->pw_dir); // access the structure field and copy the pwd

	return home;
}


//////////////////////////////////////////////////////////////////
// makeDir							//
// ============================================================ //
// Input: char* -> dir_path					//
//	  Descrpition: Name and path of the directory need	//
//		       to create				//
// Output: -							//
// Purpose: To create a directory file with the desired path	//
//	    and name,						//
//////////////////////////////////////////////////////////////////
void makeDir(char *dir_path) {
	umask(0); // Command to give directory all permissions
	int is_dir_created = mkdir(dir_path, 0777);
	if (is_dir_created == -1) { 
		printf("mkdir Error Occur!\n");
		return;
	}

	return;
}


//////////////////////////////////////////////////////////////////
// makeFile							//
// ============================================================ //
// Input: char* -> dir_path					//
//	  char* -> file_name					//
//	  Descrpition: Names and paths of directories and files //
//		       that need to be created			//
// Output: -							//
// Purpose: To create directories and files with the desired	//
//	    path and name,					//
//////////////////////////////////////////////////////////////////
void makeFile(char *dir_path, char *file_name) {
	char file_name_ow[256]; // overwrite to prevent null terminator from being included in file names
	strcpy(file_name_ow,file_name);
	strcat(dir_path, "/");
	strcat(dir_path, file_name_ow);

	int is_file_created = creat(dir_path, 0777);
	if (is_file_created == -1) {
		printf("creat Error Occur!\n");
		return;
	}

	return;
}


//////////////////////////////////////////////////////////////////
// main								//
// ============================================================ //
// Input: -							//
// Output: int  -   0 success					//
//		    1 error					//
// Purpose: Create directories and files by hash the URL enter	//
//	    ed by the user and checking if the URL is a previo	//
//	    usly entered value. Record all of these actions in	//
//	    the logfile. Separate Parent Process and Child      //
//          Process to proceed with the above work in Child     //
//          Process. And when all the work is finished, the pro //
//          gram is terminated in the Parent process.	        //
//////////////////////////////////////////////////////////////////
int main()
{	
        char input_cmd[1024];
        pid_t pid;
        pid_t pid_parent;
        int status;

	int sub_process = 0; // the number of sub process

	char *input_url;
	char *hashed_url;

	char home_dir[1024];
	char dir_name[256]={"0"};
	char file_name[256]={"0"}; // actual file name

	int hit_cnt = 0, miss_cnt = 0, while_cnt = 0;

	FILE *f = NULL;

	DIR *dir = NULL; // directory pointer declaration
	struct dirent *dir_entry = NULL, *file = NULL; 


	time_t current_time, start_time, end_time, start_time_program, end_time_program;
	struct tm *local_time;
	time(&current_time);
	local_time = localtime(&current_time); // Calculate the seconds that have passed so far and save them as local time in struct tm format
	if (local_time == NULL) {
		printf("plocal Error Occur!\n");
		return 1;
	}

	start_time = time(NULL); // Start recording process running time
        start_time_program = time(NULL); // Start recording program running time
        getHomeDir(home_dir); // Get Home Directory Path


        while (1)
        {
                printf("[%d] input CMD> ", (int)getpid()); // get process id
                scanf("%s", input_cmd);

                if (strcmp(input_cmd, "quit") == 0) { // end program
                        char logfile_address[1024];
                        strcpy(logfile_address, home_dir);
                        strcat(logfile_address, "/logfile/logfile.txt");

                        end_time_program = time(NULL);
                        int total_time_process = (int)(end_time_program - start_time_program);
                        f = fopen(logfile_address, "a");
                        fprintf(f, "**SERVER** [Terminated] run time: %d sec. #sub process: %d\n", total_time_process, sub_process); // leave a log record and terminate the program
                        fclose(f);
                        break;
                }
                else if (strcmp(input_cmd, "connect") == 0) { // Create sub process
                        pid = fork(); // Create child process
                        if (pid == -1) { // failed fork
                                return -1;
                        }
                        else if (pid == 0) { // Child Process 
                                while(1) {
                                        input_url = malloc(sizeof(char)* 1024); // dynamic memory allocation
                                        hashed_url = malloc(sizeof(char) * 1024);
                                        
                                        printf("[%d] input URL> ", getpid());
                                        scanf("%s", input_url);

                                        getHomeDir(home_dir); // Get Home Directory Path

                                        // Code to create cache or logfile directories if cache or logfile directories do not exist
                                        // from here
                                        dir = opendir(home_dir); // Open the Home Directory
                                        int is_cache_exist = 0, is_logfile_exist = 0;
                                        while ((dir_entry = readdir(dir)) != NULL) { // Check that the cache and logfile directories are in the Home directory.
                                                if (strcmp(dir_entry -> d_name, "cache") == 0 ) {
                                                        is_cache_exist = 1;
                                                }
                                                if (strcmp(dir_entry -> d_name, "logfile") == 0 ) {
                                                        is_logfile_exist = 1;
                                                }
                                        }

                                        if (is_cache_exist == 0) { // Make cache Directory
                                                char tmp[256];
                                                strcpy(tmp, home_dir);
                                                strcat(tmp, "/cache");
                                                makeDir(tmp);
                                        }
                                        if (is_logfile_exist == 0) { // Make logfile Directory and logfile.txt File
                                                char tmp[256];
                                                strcpy(tmp, home_dir);
                                                strcat(tmp, "/logfile");
                                                makeDir(tmp);
                                                makeFile(tmp, "logfile.txt");
                                        }
                                        // to here

                                        if (while_cnt == 0) { // open logfile.txt in the first loop only
                                                char tmp[1024];
                                                strcpy(tmp, home_dir);
                                                strcat(tmp, "/logfile/logfile.txt");
                                                f = fopen(tmp, "a");
                                        }

                                        if (strcmp(input_url, "bye") == 0) {
                                                free(hashed_url); // deallocation
                                                free(input_url);

                                                end_time = time(NULL); // end of running time record
                                                int running_time = (int)(end_time - start_time);
                                                
                                                fprintf(f, "[Terminated] run time: %d sec. #request hit : %d, miss : %d \n", running_time, hit_cnt, miss_cnt);
                                                if (while_cnt > 0) { 
                                                        fclose(f);
                                                }
                                                return 0;
                                        }

                                        sha1_hash(input_url, hashed_url); // url hashing


                                        for (int i = 0; i < 3; i++) {
                                                dir_name[i] = *(hashed_url + i);

                                        }
                                        strcat(home_dir, "/cache/");
                                        strcat(home_dir, dir_name);
                                        
                                        for (int i =3; (int)*(hashed_url + i) != 0; i++) {
                                                file_name[i-3] = *(hashed_url + i);
                                        }

                                        dir = opendir(home_dir);
                                        if (dir == NULL) {
                                                time(&current_time);
                                                local_time = localtime(&current_time); // current time reinitialization
                                                
                                                fprintf(f, "[MISS] %s - [%d/%d/%d, %d:%d:%d] \n", input_url, 1900+local_time->tm_year, local_time->tm_mon+1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec); // write the log file
                                                
                                                makeDir(home_dir);
                                                makeFile(home_dir, file_name);
                                                miss_cnt++;
                                        }
                                        else {
                                                for (file = readdir(dir); strlen(file->d_name) < 3; file = readdir(dir)) { // Search for files stored under hashed url names
                                                        continue;
                                                }

                                                if (strcmp(file -> d_name, file_name) == 0) {
                                                        time(&current_time);
                                                        local_time = localtime(&current_time);

                                                        fprintf(f, "[Hit] %s/ %s - [%d/%d/%d, %d:%d:%d] \n", dir_name, file->d_name, 1900+local_time->tm_year, local_time->tm_mon+1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
                                                        fprintf(f, "[Hit] %s \n", input_url);
                                                        
                                                        hit_cnt++;
                                                }
                                                else { // If only the directory name is the same but the file name is different
                                                        time(&current_time);
                                                        local_time = localtime(&current_time);

                                                        fprintf(f, "[MISS] %s - [%d/%d/%d, %d:%d:%d]\n", input_url, 1900+local_time->tm_year, local_time->tm_mon+1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
                                                        
                                                        makeDir(home_dir);
                                                        makeFile(home_dir, file_name);
                                                        miss_cnt++;
                                                }
                                        }
                                        closedir(dir);
                                
                                        free(hashed_url); // memory deallocation
                                        free(input_url);
                                        while_cnt++;
                                }
                        }
                        else { // Parent Process
                                sub_process+=1; // count sub process

                                pid_parent = wait(&status); // Waiting for child process to end
                                continue;
                        }
                }
                else {
                        printf("Wrong command Please enter exit or connect \n");
                        continue;
                }
        }	

	return 0;
}
