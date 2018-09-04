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

int num_dir(char* path)
{
    DIR *dir;
    struct dirent *entry;
    if (!(dir = opendir(path)))
        return -1;
      int num = 0;
	    while ((entry = readdir(dir)) != NULL ) {
	        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            // printf("%s\n", entry->d_name);
            num++;
          }
	    }
    closedir(dir);
    return num;
}
void call_Leaf_counter(char* path) {
  execv("./Leaf_Counter", path);
}


void printStats(char* path, dict_t dict)
{
    if(num_dir(path) == 0) {
      pid_t pid;
      pid = fork();
      printf("%s\n",path );
      if(pid == 0) {
          char* arg[]= {"/a", path, NULL};
          printf("this is leaf watting for execv\n");
          int num = execv("./a", arg);

      }
      if(pid > 0) {
        wait(NULL);
      }
      // return;
    }
    else{

      printf("current path is %s\n",path );
      DIR *dir;
      struct dirent *entry;
      int num_children = num_dir(path);
      char children_dir[num_children][1024];
        if (!(dir = opendir(path)))
            return;
        int i = 0;
    	    while ((entry = readdir(dir)) != NULL) {

    	        if (entry->d_type == DT_DIR) {
                  char* path1 = malloc(sizeof(char)*1024);
    	            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
    	                continue;
    							strcpy(path1, path);
                  strcat(path1, "/");
    							strcat(path1, entry->d_name);
                  strcpy(children_dir[i], path1);
                  i++;
                  }
  	       }

          close(dir);
          for(int i = 0; i<num_children;i++) {
            printf("in the children_dir list :%s\n", children_dir[i]);
            pid_t pid;
            pid = fork();
            if(pid == 0) {
              execl("./b","./b", children_dir[i],NULL);
            }
          }
          for(int i = 0; i< num_children; i++) {
            wait(NULL);;
          }

          char *filenamecpy = malloc(sizeof(char)*1024);
          strcpy(filenamecpy, path);
          strcat(filenamecpy,"/");
          strcat(filenamecpy, get_current_directory_name(path));
          strcat(filenamecpy, ".txt");
          int fd = open(filenamecpy, O_RDWR | O_CREAT | O_TRUNC);
          chmod(filenamecpy,0700);
          printf("creat a file %s\n", filenamecpy );
          for(int i = 0; i< num_children; i++) {
            char* chil_path = malloc(sizeof(char)*1024);
            strcpy(chil_path,children_dir[i]);
            strcat(chil_path,"/");
            strcat(chil_path,get_current_directory_name(children_dir[i]));
            strcat(chil_path,".txt");
            int fd_chil = open(chil_path,O_RDONLY);
            if(fd_chil < 0) {
              printf("open error since %s\n",chil_path );
            }
            printf("Now arrgreate %s !! to !! %s!\n", chil_path, filenamecpy );
            aggregate_file2(fd_chil,fd, dict);
            // close(fd_chil);
            // close(fd);
          }



    // closedir(dir);
  }
}
int aggregate_file2(int fromfd, int tofd, dict_t d) {
	char* bp;
	char buf[1024];
	int bytesread,byteswritten;
  bytesread = read(fromfd, buf, 1024);
  if (bytesread <= 0){
    return -1;
  }
	if(bytesread > 0) {
		bp = buf;
      //lseek(tofd,0,SEEK_SET);
      char ** argvp = NULL;
      char ** argvp2 = NULL;
      //error handling
      // \n as the interminator to differentiate the new line and the current line
      int makeargv_return = makeargv(trimwhitespace(bp), ",", &argvp);
      for(int j = 0; j < makeargv_return; j++) {
        printf("In the aggregate_file print the first makeargv elements %s\n", argvp[j]);
        int makeargv_return2 = makeargv(trimwhitespace(argvp[j]), ":", &argvp2);
        printf("Follow the previous the candidate is  %s\n", argvp2[0]);
        printf("vote is  %s\n", argvp2[1]);
        printf("value is to be adding is %d\n",atoi(argvp2[1]));
          if(dict_find_index(d,argvp2[0]) == -1) {
            dict_add(d, argvp2[0], atoi(argvp2[1]));
          }
          else {
            printf("the original value for %s , is %d\n",argvp2[0],dict_find_value(d,argvp2[0]) );
              dict_add(d, argvp2[0], dict_find_value(d,argvp2[0])+atoi(argvp2[1]));
              printf("After adding is %d\n",dict_find_value(d,argvp2[0]) );
          }
      }
      freemakeargv(argvp);
      freemakeargv(argvp2);
      view_dict_info(d);
      char* buf1 = malloc(sizeof(char)*1024);
      char* buf2 = malloc(sizeof(char)*1024);
      for (int i = 0; i < d->len; i++) {

          strcpy(buf1, d->entry[i].key);
          strcat(buf1, ":");
          sprintf(buf2, "%d",d->entry[i].value );
          strcat(buf1, buf2);
          if(i != d->len - 1){
            strcat(buf1,",");
          }
          printf("Writing this to file : %s\n",buf1 );

          int num = write(tofd,buf1,strlen(buf1));
if(num < 0){
perror("Writing fail");}
      }
    	//write(tofd,'\0', 1);
      free(buf1);
      free(buf2);
      // break;

  }
	return 1;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Wrong number of args, expected 2, given %d", argc - 1);
		exit(1);
	}
    // printf("%d \n", num);
    dict_t dict = dict_new();
    printStats(argv[1], dict);
    dict_free(dict);
}
