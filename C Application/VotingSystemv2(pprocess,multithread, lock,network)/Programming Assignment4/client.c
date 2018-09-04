/************************************************
* login:   sunx0458        sunx0725
* name:    Connor C Sun    Zhongyi Sun
* id:      5116486         5320262
* section: 10 T TH 11:15 - 12:30
* date:    04/23/18
*************************************************/

#define _BSD_SOURCE
#define NUM_ARGS 3

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "util.h"


int get_add_region_num(char* file) {


  FILE* f = fopen(file, "r");
	char *buf= malloc(sizeof(char)*1024);
	char** argvp = malloc(sizeof(char)*1024);

	if(f == NULL)
	{
		perror("Error in get_vote. Failed to open file\n");
		exit(0);
	}
	int count = 0;
	while (1)
	{
		buf = read_line(buf, f);
		if(buf == NULL) break;
		int c = makeargv(buf, " ", &argvp);
		if( c < 0) {
			perror("Error Makeargv\n");
			exit(-1);
		}
		if(strcmp(argvp[0],"Add_Region") == 0) {
			count++;
		}
	}
	// fclose(f);
	return count;
}

char* get_vote(char* file, char* path)
{
	char** votes_string = malloc(sizeof(char)*1024);
	char** argvp = malloc(sizeof(char)*1024);
	char** buf = malloc(sizeof(char)*1024);
	char** num = malloc(sizeof(char)*1024);
	int c;
	char* temppath = malloc(sizeof(char)*1024);
	strcpy(temppath,path);
	strcat(temppath,"/");
	strcat(temppath,file);

  FILE* f = fopen(temppath, "r");
	dict_t dict = dict_new();

	if(f == NULL)
	{
		perror("Error in get_vote. Failed to open file\n");
		exit(0);
	}
	while (1)
	{
		buf = read_line(buf, f);
		if(buf == NULL) break;
		c = makeargv(buf, "\n", &argvp);
		int value = dict_find_value(dict, argvp[0]);
		value++;
		dict_add(dict, argvp[0], value);
	}

	for (int i = 0; i < dict->len; i++) {
			strcat(votes_string, dict->entry[i].key);
			strcat(votes_string, ":");
			sprintf(num, "%d",dict->entry[i].value );
			strcat(votes_string, num);
			// strcat(votes_string, ",");
			// differentiate the last candidate by the len
			if(i != dict->len - 1){
				strcat(votes_string,",");
			}
	}
	votes_string[sizeof(votes_string)] = '\0';
	//printf("before retrun votes_string: %s\n", votes_string);

	dict_free(dict);

	/*can't close f, will print out some unknow characters*/
	// fclose(f);

	return votes_string;
}

char* read_command(char* buffer, char * path)
{
	//printf("-in read_command buffer is: %s\n", buffer);
	int c;
	char** argvp = malloc(sizeof(char)*1024);
  char** command = malloc(sizeof(char)*1024);
	char** votes_string = malloc(sizeof(char)*1024);
	c = makeargv(buffer, " ", &argvp);

	if(strcmp(argvp[0], "Return_Winner") == 0)
	{
		strcat(command, "RW; ;\0");
	}
	else if(strcmp(argvp[0], "Count_Votes") == 0)
	{
		strcat(command, "CV;");
		strcat(command, argvp[1]);
		strcat(command, ";\0");
	}
  else if(strcmp(argvp[0], "Add_Region") == 0)
	{
		strcat(command, "AR;");
		strcat(command, argvp[1]);
		strcat(command, ";");
    strcat(command, argvp[2]);
    strcat(command,"\0");
	}
	else if(strcmp(argvp[0], "Open_Polls") == 0)
	{
		strcat(command, "OP;");
		strcat(command, argvp[1]);
		strcat(command, ";\0");
	}
	else if(strcmp(argvp[0], "Add_Votes") == 0)
	{
		strcat(command, "AV;");
		strcat(command, argvp[1]);
		//add vote number here
		votes_string = get_vote(argvp[2],path);
		strcat(command, ";");
		strcat(command, votes_string);
		strcat(command, "\0");
	}
	else if(strcmp(argvp[0], "Remove_Votes") == 0)
	{
		strcat(command, "RV;");
		strcat(command, argvp[1]);
		//remove vote number here
		votes_string = get_vote(argvp[2],path);
		strcat(command, ";");
		strcat(command, votes_string);
		strcat(command, "\0");
	}
	else if(strcmp(argvp[0], "Close_Polls") == 0)
	{
		strcat(command, "CP;");
		strcat(command, argvp[1]);
		strcat(command, ";\0");
	}
	else
		strcat(command, "UC; ;\0");

  return command;
}

int main(int argc, char** argv) {

	if (argc < NUM_ARGS + 1) {

		printf("Wrong number of args, expected %d, given %d\n", NUM_ARGS, argc - 1);
		printf("Usage:./client <REQ File> <SERVER IP> <SERVER PORT>\n");
		exit(1);
	}
	int SERVER_PORT = atoi(argv[3]);

	FILE* req, vote;
	// Create a TCP socket.
	int sock = socket(AF_INET , SOCK_STREAM , 0);

	// Specify an address to connect to (we use the local host or 'loop-back' address).
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(SERVER_PORT);
	address.sin_addr.s_addr = inet_addr(argv[2]);

	// Connect it.
	if (connect(sock, (struct sockaddr *) &address, sizeof(address)) == 0) {
		// unsigned long addr = address.sin_addr.s_addr;
		// char addr_s[256] = "127.0.0.1\0";
		unsigned short port = ntohs(address.sin_port);
		char addr_s[256] = "";
		strcpy(addr_s,inet_ntoa(address.sin_addr));
		printf("Initiated connection with server at %s:%hu\n", addr_s, port);
		// Buffer for data.
		char* buffer = malloc(sizeof(char)*1024);
		char* command = malloc(sizeof(char)*1024);
		char* pathname = malloc(sizeof(char)*1024);
		int n = get_add_region_num(argv[1]);
		req = fopen(argv[1], "r");
		pathname = get_current_directory_previous_path(argv[1]);
		if(req == NULL)
		{
			perror("Error! Failed to open file\n");
		}
		if(n != 0) {
				char num1[256] = "";
				char num[256] = "";
				strcpy(num1, "Extra!");
				sprintf(num,"%d",n);
				strcat(num1, num);
				write(sock, num1, 256);
		} else {
			char num1[256] = "";
			char num[256] = "";
			strcpy(num1, "Extra!");
			sprintf(num,"%d",n);
			strcat(num1, num);
			write(sock, num1 , 256);
		}
		while(1)
		{

			buffer = read_line(buffer,req);
			if(buffer == NULL) break;
			command = read_command(buffer,pathname);
			if(write(sock, command, 256)<0)
			{
				perror("Error! Failed to send buffer to server.\n");
			}
			char CODE[2];
			CODE[0] = command[0];
			CODE[1] = command[1];
			printf("Sending request to server: %s\n", command);
			char buffer1[256];
			recv(sock, buffer1, sizeof(buffer1), 0);
			printf("Received response from server: %s\n", buffer1);
		}
		printf("Closed connection with server at %s:%hu\n", addr_s, port);
		fclose(req);
		close(sock);

	} else {

		perror("Connection failed!");
	}
}
