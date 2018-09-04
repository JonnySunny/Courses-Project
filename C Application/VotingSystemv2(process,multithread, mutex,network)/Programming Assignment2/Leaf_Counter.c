/*login:Zhongyi Sun sunx0725
* date: mm/dd/yy
* name: Connor C Sun, Zhongyi Sun
* id: 5116486, 5320262 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include "util.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>

// based on lab 5, read over all of the file in the current dirctory
int checkFileExist(char* path)
{
    DIR *dir;
    struct dirent *entry;
    if (!(dir = opendir(path)))
        return -1;

	    while ((entry = readdir(dir)) != NULL) {
	        if (entry->d_type != DT_DIR) {
						struct stat* stats = malloc(sizeof(struct stat));
						stat(entry->d_name, stats);
						printf("File name: %s\n",entry->d_name );
            if(strcmp(entry->d_name,"votes.txt") == 0) {
              return 1;
              // continue;
            } else {
              printf("Nodt a leaf node\n" );
              return 0;
              // break;
            }
	        }
	    }
    closedir(dir);
}

// parse input based on first assignment
int parseInput(char *filename, dict_t d) {
  char *filenamecpy = malloc(sizeof(char)*1024);
  strcpy(filenamecpy, filename);
  strcat(filenamecpy,"/");
  strcat(filenamecpy,"votes.txt");
  FILE* f = fopen(filenamecpy,"r");

  // Error handle miss input file
  if(f == NULL) {
    perror("Error !! Failed when opening file\n ");
    exit(1);
  }
  else{
    char* buf = malloc(sizeof(char)*1024);
    // int num_candidates = 0;
    while(1) {
          buf = read_line(buf,f);
          if(buf == NULL) break; // break when read on the empty line
          printf("%s\n", buf);
          parseInputLine(buf, d);
        }
    fclose(f);
    // free(filenamecpy);
  }
}
int parseInputLine(char *s, dict_t d) {
  char ** argvp = NULL;
  //error handling
  // \n as the interminator to differentiate the new line and the current line
  int makeargv_return = makeargv(trimwhitespace(s), "\n", &argvp);

  if(makeargv_return == -1) {
    perror("Error when using makeargv!!");
    exit(4);
  }
  else if(makeargv_return == 0) {
    return -1;
  }
  else{
        // printf("here, %d, %s\n", makeargv_return, argvp[0]);
        int update_value = dict_find_value(d, argvp[0]);
        update_value++;
        dict_add(d, argvp[0], update_value);
    }
    return 0;
}
int generate_flag_file(char* filename) {
    char *filenamecpy = malloc(sizeof(char)*1024);
    strcpy(filenamecpy, filename);
    strcat(filenamecpy,"/");
    strcat(filenamecpy, "1.txt");
    int fd = open(filenamecpy, O_RDWR|O_CREAT);
    close(fd);
    // free(filenamecpy);
    return fd;
}
// int generate_vote_file(char* filename, dict_t d) {
//   char ** argvp = NULL;
//   //error handling
//   // \n as the interminator to differentiate the new line and the current line
//   int makeargv_return = makeargv(trimwhitespace(filename), "/", &argvp);
//
//   if(makeargv_return == -1) {
//     perror("Error when using makeargv!!");
//     exit(4);
//   }
//   else {
//     // int i = 0;
//     // printf("%d\n",makeargv_return);
//     // while(i < makeargv_return) {
//     //   printf("%d: %s\n", i, argvp[i]);
//     //   i++;
//     // }
//     // printf("current dir name : %s\n", argvp[makeargv_return-1]);
//     char *filenamecpy = malloc(sizeof(char)*1024);
//     strcpy(filenamecpy, filename);
//     strcat(filenamecpy,"/");
//     strcat(filenamecpy, argvp[makeargv_return-1]);
//     strcat(filenamecpy, ".txt");
//     printf("generate a file: %s\n", filenamecpy);
//     int fd = open(filenamecpy, O_RDWR|O_CREAT);
//     char* buf = malloc(sizeof(char)*1024);
//     char* buf2 = malloc(sizeof(char)*1024);
//     for (int i = 0; i < d->len; i++) {
//         printf("Entry %d : Name is %s , Value is %d\n",(i+1),d->entry[i].key,d->entry[i].value );
//         strcpy(buf, d->entry[i].key);
//         strcat(buf, ":");
//         sprintf(buf2, "%d",d->entry[i].value );
//         printf("%s\n",buf2 );
//         strcat(buf, buf2);
//         strcat(buf,"\n");
//         printf("%s\n",buf );
//         write(fd,buf,strlen(buf));
//     }
//     return fd;
//   }
// }

int generate_vote_file2(char* filename, dict_t d) {

    char *filenamecpy = malloc(sizeof(char)*1024);
    strcpy(filenamecpy, filename);
    strcat(filenamecpy,"/");
    strcat(filenamecpy, get_current_directory_name(filename));
    strcat(filenamecpy, ".txt");
    printf("generate a file: %s\n", filenamecpy);
    int fd = open(filenamecpy, O_RDWR|O_CREAT);
    char* buf = malloc(sizeof(char)*1024);
    char* buf2 = malloc(sizeof(char)*1024);
    for (int i = 0; i < d->len; i++) {
        printf("Entry %d : Name is %s , Value is %d\n",(i+1),d->entry[i].key,d->entry[i].value );
        strcpy(buf, d->entry[i].key);
        strcat(buf, ":");
        sprintf(buf2, "%d",d->entry[i].value );
        printf("%s\n",buf2 );
        strcat(buf, buf2);
        strcat(buf,"\n");
        printf("%s\n",buf );
        write(fd,buf,strlen(buf));
    }
    return fd;
}

int main(int argc, char** argv) {

  if (argc < 1) {
		printf("Wrong number of args, expected 2, given %d", argc - 1);
		exit(1);
	}
  dict_t dict = dict_new();
	int num_check_vote_file = checkFileExist(argv[1]);
  if(num_check_vote_file == -1) {
    return -1;
  }
  else {
    int num_check_parseInput_return = parseInput(argv[1], dict);
    view_dict_info(dict);
    printf("here in main %s\n", argv[1]);
    generate_vote_file2(argv[1], dict);
    get_current_directory_name(argv[1]);
    // generate_flag_file(argv[1]);
  }
}
