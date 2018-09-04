/************************************************
* login:   sunx0458        sunx0725
* name:    Connor C Sun    Zhongyi Sun
* id:      5116486         5320262
* section: 10 T TH 11:15 - 12:30
* date:    04/10/18
*************************************************/

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

struct node* temp_mainnode;
int ind = 0;
struct Q * shared_q;
struct condQueue * shared_struct;
//check the directory if exist.
struct condQueue {
	struct Q *q;
  char* inputfilepath;
	char* inputfilename;
  char* outputfilepath;
  char* logfilepath;
  int id;
  node_t *nodes;
  int num_node;
	pthread_cond_t* cond;
	pthread_mutex_t* mutex;
	pthread_mutex_t* logmutex;
	dict_t dict;
};

int CheckDir(char* path)
{
    DIR* dir  = opendir(path);
    if (dir)
    {
        printf("The dirctory \"%s\" is exsit.\n", path);
        return 1;
    }
    else
    {
        printf("the Directory \"%s\" doesn't exsit.\n", path);
        return 0;
    }
}

//make the directory
void MakeDir(char* path)
{
    if (mkdir(path, 0777) == -1) {
        perror(path);
    }
}

//bring the input txt and build the nodes
int Node_Counter(char* filename, char* path)
{
    FILE* f = fopen(filename,"r");
    if(f == NULL)
    {
        perror("Error !! Failed when opening file\n ");
        exit(1);
    }
    else
    {
    char* buf = malloc(sizeof(char)*1024);
    int c = 0;
        while(1)
        {
            buf = read_line(buf,f);
            if(buf == NULL) break;
            // printf("here's the line: %s\n", buf);
            c += nodecounter(buf, path);
        }
				free(buf);
				fclose(f);
				// printf("the maximum node is %d\n",c+1 );
        return c+1;

		}


}
void buildNodes(char* filename, char* path, node_t * nodes, int num)
{
    FILE* f = fopen(filename,"r");
    if(f == NULL)
    {
        perror("Error !! Failed when opening file\n ");
        exit(1);
    }
    else
    {
    char* buf = malloc(sizeof(char)*1024);
        while(1)
        {
            buf = read_line(buf,f);
            if(buf == NULL) break;
            // printf("here's the line: %s\n", buf);
            parseInputline(buf, path, nodes, num );
        }
			free(buf);
		}
    fclose(f);
}

int nodecounter(char *s, char* path)
{
    char ** argvp = NULL;
    int makeargv_return = makeargv(trimwhitespace(s), ":", &argvp);
    if(makeargv_return == -1)
    {
        perror("Error when using makeargv!!");
        exit(2);
    }
		freemakeargv(argvp);
    return makeargv_return-1;
}

void parseInputline(char *s, char* path, node_t * nodes, int num)
{
    temp_mainnode = nodes;
    char ** argvp = NULL;
    int makeargv_return = makeargv(trimwhitespace(s), ":", &argvp);
    int flag = 999;

    if(makeargv_return == -1)
    {
        perror("Error when using makeargv!!");
        exit(2);
    }
    //argvp[0]
    int rund = 0;
    for(int j=0; j<makeargv_return; j++) {
        if(findnode(nodes, argvp[j], num) != NULL) {
          rund++;
          continue;
        }
        else{
        strcpy(nodes+ind, argvp[j]);
        strcpy((nodes+ind)->parent, argvp[0]);
				(nodes+ind)->child_num = makeargv_return-1;
				// printf("%s : %d\n", (nodes+ind)->name, (nodes+ind)->child_num);
        ind++;
      }
    }
		for(int j=0; j<makeargv_return; j++) {
					findnode(nodes, argvp[j], num)->child_num = 0;

			}
		for(int j=0; j<makeargv_return; j++) {
				if(strcmp(findnode(nodes, argvp[j], num)->name,argvp[0])== 0) {
					findnode(nodes, argvp[0], num)->child_num = makeargv_return-1;
				}
			}
}


void buildPath(node_t *nodes, char* output, int num) {
  // char* temp = malloc(sizeof(char)*1024);
  // char* temp2 = malloc(sizeof(char)*1024);
  // // strcpy(temp2,output);
  // temp2 = output;

  for (int i = 0; i < num; i++) {

      if(i == 0) {
        strcpy(nodes[i].path,output);
        strcat(nodes[i].path,"/");
        strcat(nodes[i].path,nodes[i].name);
      }
      else {
        strcpy(nodes[i].path,findnode(nodes, nodes[i].parent,num)->path);
        strcat(nodes[i].path,"/");
        strcat(nodes[i].path,nodes[i].name);
      }

  }
}
/*
			Taken from online

*/
int remove_directory(const char *path)
{
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;
   if (d)
   {
      struct dirent *p;
      r = 0;
      while (!r && (p=readdir(d)))
      {
          int r2 = -1;
          char *buf;
          size_t len;
          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
          {
             continue;
          }
          len = path_len + strlen(p->d_name) + 2;
          buf = malloc(len);
          if (buf)
          {
             struct stat statbuf;
             snprintf(buf, len, "%s/%s", path, p->d_name);
             if (!stat(buf, &statbuf))
             {
                if (S_ISDIR(statbuf.st_mode))
                {
                   r2 = remove_directory(buf);
                }
                else
                {
                   r2 = unlink(buf);
                }
             }
             free(buf);
          }
          r = r2;
      }
      closedir(d);
   }
   if (!r)
   {
      r = rmdir(path);
   }
   return r;
}

void buildDir(node_t *nodes, char* output, int num) {
    // printf("``%s\n", output);
		int flag = CheckDir(output);
		if (flag == 0) {
			MakeDir(output);
		} else {
			int delet = remove_directory(output);
			MakeDir(output);
		}

		MakeDir(output);

    for(int i = 0; i < num; i++)
    {
      MakeDir(nodes[i].path);
    }
}

void read_input_dir(char* path, Q_ q)
{
    DIR *dir;
    struct dirent *entry;
    if (!(dir = opendir(path)))
        return -1;

	    while ((entry = readdir(dir)) != NULL) {
	        if (entry->d_type != DT_DIR) {
            // avoid adding .DS_Store file into the queue by adding the last condition
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || (entry->d_name)[0] == '.')
                continue;
            enqueue(q,entry->d_name);
	        }
	    }
    closedir(dir);
}

char decry(char en) {
  int t = en;
  // char is Y, value is 89, we want to get A
  if(t == 89) {
    return 'A';
  }
    // char is Z, value is 89, we want to get B
  else if(t == 90) {
    return 'B';
  }
  // char is y, value is 89, we want to get a
  else if(t == 121) {
    return 'a';
  }
  // char is z, value is 89, we want to get b
  else if(t == 122) {
    return 'b';
  }
  else {
    char ans = t+2;
    return ans;
  }
}
char* decry_file_line(char *s, char* outputfilepath) {
  char ** argvp = NULL;
  //error handling
  // \n as the interminator to differentiate the new line and the current line
  int makeargv_return = makeargv(trimwhitespace(s), "\n", &argvp);
	char * decode = malloc(sizeof(char)*1024);
  if(makeargv_return == -1) {
    perror("Error when using makeargv!!");
    exit(4);
  }
  else if(makeargv_return == 0) {
    return -1;
  }
  else{
        strcpy(decode,"");
        for(int i = 0; i < strlen(argvp[0]); i++) {
          char* string = malloc(sizeof(char)*1024);
          sprintf(string,"%c\0", decry(*(argvp[0]+i)));
          strcat(decode,string);
        }
    }
    freemakeargv(argvp);
    return decode;
}

void decry_file(char *filename, char* outputfilepath) {
  char *filenamecpy = malloc(sizeof(char)*1024);
  strcpy(filenamecpy, filename);
  FILE* f = fopen(filenamecpy,"r");
  FILE* df = fopen(outputfilepath,"w");
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
          fprintf(df, decry_file_line(buf, outputfilepath));
					fprintf(df,"\0");
					fprintf(df,"\n");
        }

  }
	fclose(df);
	fclose(f);
	free(filenamecpy);
}

// parse input based on first assignment
void DictparseInput(char *filename, dict_t d) {
  FILE* f = fopen(filename,"r");
	char* buf = malloc(sizeof(char)*1024);
  // Error handle miss input file
  if(f == NULL) {
    perror("Error !! Failed when opening file\n ");
    exit(1);
  }
  else{
    char* buf = malloc(sizeof(char)*1024);
    // int num_candidates = 0;
		char line[1024];
    while(1) {
           buf = read_line(buf,f);
          if(buf == NULL) break; // break when read on the empty line
					DictparseInputLine(buf, d);
        }
    fclose(f);
  }
	free(buf);
}
void DictparseInputLine(char *s, dict_t d) {
  char ** argvp = NULL;
	char ** argvp2 = NULL;
	//error handling
  // \n as the interminator to differentiate the new line and the current line
  int makeargv_return = makeargv(trimwhitespace(s), "\n", &argvp);
	int makeargv_return2 = makeargv(trimwhitespace(argvp[0]), ":", &argvp2);

  if(makeargv_return == -1) {
    perror("Error when using makeargv!!");
    exit(4);
  }
	if(makeargv_return2 == -1) {
		perror("Error when using makeargv!!");
    exit(4);
  }
  else if(makeargv_return == 0 || makeargv_return2 == 0) {
    return -1;
  }
  else{
		 if(makeargv_return2 == 1){
			 // only characters
        int update_value = dict_find_value(d, argvp[0]);
        update_value++;
        dict_add(d, argvp[0], update_value);
			}
			else {
				// characters correspond votes
				int update_value2 = dict_find_value(d, argvp2[0]);
				// printf("update_value2 is %s : \n",argvp2[1] );
				if(argvp2[1] == NULL) {
					update_value2 = 0;
				} else{
				update_value2 = atoi(argvp2[1]);
				}
				dict_add(d, argvp2[0], update_value2);
			}
		}
    freemakeargv(argvp);
		freemakeargv(argvp2);

}
int generate_vote_file(char* filename, dict_t d) {
    // fectch the path and append .txt behind this path
    char *filenamecpy = malloc(sizeof(char)*1024);
    strcpy(filenamecpy, filename);
    //printf("Generate a Leaf file: %s\n", filenamecpy);
    int fd = open(filename, O_RDWR|O_CREAT);
    //Overwrite the file ever time you open it
    lseek(fd,0,SEEK_SET);
    char* buf = malloc(sizeof(char)*1024);
    char* buf2 = malloc(sizeof(char)*1024);
    //loop the whole dictionary to get the pair data and candidate:value
    for (int i = 0; i < d->len; i++) {
        strcpy(buf, d->entry[i].key);
        strcat(buf, ":");
        sprintf(buf2, "%d",d->entry[i].value );
        strcat(buf, buf2);
        // differentiate the last candidate by the len
        if(i != d->len - 1){
          strcat(buf,"\n");
        }
        write(fd,buf,strlen(buf));
    }
    write(fd,"\n",1);
    close(fd);
    free(filenamecpy);
    free(buf);
    free(buf2);
    return fd;
}


int FileExists(char* openfile, char* parentfilename, char *inputfilepath, node_t* nodes, int num,  dict_t dict, int flag){
	// printf("%s : File exists\n", openfile);
	char* filenamecpy = malloc(sizeof(char)*1024);
	strcpy(filenamecpy, inputfilepath);
	strcat(filenamecpy,"/");
	strcat(filenamecpy, get_current_directory_name(inputfilepath));
	strcat(filenamecpy,".txt");
	if(flag == 0) {
				DictparseInput(filenamecpy,dict);
				flag =1;
	}
	dict_t parentDict = dict_new();

	//sptore all information in "parent.txt" in the parentDict
	DictparseInput(openfile, parentDict);
	dict_merge(dict, parentDict);
	generate_vote_file(parentfilename, parentDict);
	dict_free(parentDict);
	free(filenamecpy);
	return flag;
}
int FileNoExists(char* openfile, char* parentfilename, char* inputfilepath, node_t* nodes,int num,dict_t  dict, int flag){
	//not exsits aggregate file
	FILE* file;
	file = fopen(openfile,"w");
	char* filenamecpy = malloc(sizeof(char)*1024);

	strcpy(filenamecpy, inputfilepath);
	strcat(filenamecpy,"/");
	strcat(filenamecpy, get_current_directory_name(inputfilepath));
	strcat(filenamecpy,".txt");

	if(flag == 0) {
		DictparseInput(filenamecpy,dict);
		flag =1;
	}
	generate_vote_file(parentfilename, dict);
	fclose(file);
	free(filenamecpy);
	return flag;
}

char* return_open_file(char* inputfilepath,char* parentName) {
		  char* openfile = malloc(sizeof(char)*1024);
			strcpy(openfile,get_current_directory_previous_path(inputfilepath));
			strcat(openfile,"/");
			strcat(openfile,parentName);
			strcat(openfile,".txt");
				openfile[strlen(openfile)+1] = '\0';
			return openfile;
			// try to open aggregate file

}
void aggregate(char* rootname, char* inputfilepath, node_t* nodes, int num,  dict_t dict, int flag) {
	// printf("here is aggregate funcion : %s\n", inputfilepath);
	// printf("%s\n", get_current_directory_name(inputfilepath));
	if(inputfilepath == NULL) {
		return;
	}
  char * parentName = malloc(sizeof(char)*1024);
	char * parentfilename = malloc(sizeof(char)*1024);
  parentName = findnode(nodes,get_current_directory_name(inputfilepath),num)->parent;
	node_t* parent = findnode(nodes,parentName,num);
	if(strcmp(parentName,rootname) == 0) {
    // printf("In aggregate function: reach to the root\n");
    // printf("Parend name is %s\n", parentName);
		//root dir
    if(parentName == NULL) {
      return;
    }
		else {

      FILE* file;
      char* openfile = malloc(sizeof(char)*1024);
			strcpy(openfile,return_open_file(inputfilepath, parentName));
			strcpy(parentfilename,openfile);
      file = fopen(openfile,"r");
			//try to open aggregate file
      if(file) {

				//exists aggregate file
				pthread_mutex_lock(parent->mutex);
				fclose(file);
				//  printf("in the lock during root path, related node is %s \n", get_current_directory_name(inputfilepath));
				flag = FileExists(openfile, parentfilename,inputfilepath, nodes, num, dict,flag);

				pthread_mutex_unlock(parent->mutex);
      } else {
				//not exsits aggregate file
      //  printf("%s : File doesn't exists\n", openfile);
				pthread_mutex_lock(parent->mutex);
				// printf("in the lock during root path, related node is %s \n", get_current_directory_name(inputfilepath));
				flag = FileNoExists(openfile, parentfilename,inputfilepath, nodes, num, dict,flag);
				pthread_mutex_unlock(parent->mutex);
      }
			 return;
    }

	}
		//not root dir
	else {

    // char * parentName = malloc(sizeof(char)*1024);
    // parentName = findnode(nodes,get_current_directory_name(inputfilepath),num)->parent;
    // printf("Parend name is %s\n", parentName);
    if(parentName == NULL) {
      return;
    }
    else{
      // node_t* parent = findnode(nodes,parentName,num);

      //printf("in the lock during child path\n");
			FILE* file;
			char* openfile = malloc(sizeof(char)*1024);
			strcpy(openfile,return_open_file(inputfilepath, parentName));
			strcpy(parentfilename,openfile);
			file = fopen(openfile,"r");
			if(file) {
				//exists aggregate file
				pthread_mutex_lock(parent->mutex);
				fclose(file);
				//printf("In aggregate function: Child path related node is %s \n", get_current_directory_name(inputfilepath));
				flag = FileExists(openfile, parentfilename,inputfilepath, nodes, num, dict,flag);

				pthread_mutex_unlock(parent->mutex);
			} else {
				//doesnot exist aggregate file
				pthread_mutex_lock(parent->mutex);
				//printf("In aggregate function: Child path related node is %s \n", get_current_directory_name(inputfilepath));
				flag = FileNoExists(openfile, parentfilename,inputfilepath, nodes, num, dict,flag);
				pthread_mutex_unlock(parent->mutex);
			}
			aggregate(rootname,get_current_directory_previous_path(inputfilepath),nodes,num, dict, flag);
    }

	}
}





void logStart(int id, char* logpath, char* nodename, pthread_mutex_t* mutex) {
	pthread_mutex_lock(mutex);
	FILE* f;
	f = fopen(logpath, "a");
	if(f == NULL) {
		printf("Error when opening file\n");
		exit(-1);
	}
	fprintf(f, "%s:%ld:start\n", nodename, id);
	fclose(f);
	pthread_mutex_unlock(mutex);
}
void logEnd(long int id, char* logpath, char* nodename, pthread_mutex_t* mutex) {
	pthread_mutex_lock(mutex);
	FILE* f;
	f = fopen(logpath, "a");
	if(f == NULL) {
		printf("Error when opening file\n");
		exit(-1);
	}
	fprintf(f, "%s:%ld:end\n", nodename, id);
	fclose(f);
	pthread_mutex_unlock(mutex);
}
void childthread(void* arg) {

  char* enname = malloc(sizeof(char)*1024);
	char* dename = malloc(sizeof(char)*1024);
  struct condQueue* cq1 = (struct condQueue*) arg;
	pthread_mutex_lock(shared_struct->mutex);
	char* dequeueName = dequeue(shared_q);
	node_t* node = malloc(sizeof(node_t));
	node = findnode(cq1->nodes, dequeueName, cq1->num_node);
	node->id = pthread_self();
	logStart(node->id,cq1->logfilepath, node->name, shared_struct->logmutex);
	strcpy(cq1->outputfilepath, node->path);
	strcpy(cq1->inputfilepath, return_input_file_path(cq1->inputfilename,dequeueName));
	pthread_mutex_unlock(shared_struct->mutex);
	//
  strcpy(dename,cq1->outputfilepath);
  strcat(dename,"/");
  strcat(dename,node->name);
  strcat(dename,".txt");
  strcpy(enname,cq1->inputfilepath);
	//	Decry file
	decry_file(enname, dename);
	//	aggregate file
	//printf("before enter aggregate the input path is %s, dename is %s\n",node->path, dename );

	//want to assign the output dir path to the aggregate since this path represents the child node
	aggregate(cq1->nodes[0].name,node->path,cq1->nodes,cq1->num_node, findnode(cq1->nodes,get_current_directory_name(enname), cq1->num_node)->dict, 0);
	//printf("******** out aggregate\n");
	// log end
	logEnd(node->id,cq1->logfilepath, node->name, shared_struct->logmutex);
}

int num_thread(Q_ q){
  return num_element(q);
}

int main(int argc, const char *argv[])
{
    if (argc < 4) {
		printf("Wrong number of args, expected 3, given %d\n", argc - 1);
		exit(1);
	}




    int c = Node_Counter(argv[1], argv[3]);
		struct node* mainnode = malloc(sizeof(node_t)*c);
    for(int e = 0; e < c; e++) {
      (mainnode+e)->mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
      pthread_mutex_init((mainnode+e)->mutex, NULL);
			(mainnode+e)->dict = dict_new();
			(mainnode+e)->child_num = 0;
    }

    buildNodes(argv[1], argv[3], mainnode,c);
    buildPath(mainnode, argv[3], c);
    buildDir(mainnode, argv[3], c);
		int count_leaf = 0;
		for(int e = 0; e < c; e++) {
			if((mainnode+e)->child_num == 0){
				count_leaf++;
			}
		}

    char* a = malloc(sizeof(char)*1024);
		strcpy(a,argv[3]);
    // a = return_log_file_path(argv[3]);
		strcpy(a, return_log_file_path(a));
    FILE* df = fopen(a,"w");
		fclose(df);

 	//	shared queue
    Q_ q2 = queue_new();
		char* a2 = malloc(sizeof(char)*1024);
		strcpy(a2,argv[2]);
		read_input_dir(a2, q2);
		if(empty(q2)) {
			printf("error:input directory is empty!\n");
			exit(-1);
		}
		if(num_element(q2) != count_leaf) {
			perror("Number of Leaf node files is different.\n");
		}
    int numOfthreads = num_thread(q2);

    struct condQueue* cq = (struct condQueue*) malloc(sizeof(struct condQueue));
    cq->inputfilepath = malloc(sizeof(char)*1024);
		cq->inputfilename = malloc(sizeof(char)*1024);
    cq->outputfilepath = malloc(sizeof(char)*1024);
    cq->logfilepath = malloc(sizeof(char)*1024);
  	cq->q = malloc(sizeof(struct Q));
    cq->nodes = malloc(sizeof(node_t)*c);
    cq->num_node = c;
  	cq->cond = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
  	cq->mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
		cq->logmutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    cq->q = q2;
    cq->nodes = mainnode;
		cq->dict = dict_new();
  	pthread_cond_init(cq->cond, NULL);
  	pthread_mutex_init(cq->mutex, NULL);
		pthread_mutex_init(cq->logmutex, NULL);
		char* a3 = malloc(sizeof(char)*1024);
		strcpy(a3,argv[3]);
		strcpy(cq->logfilepath,return_log_file_path(a3));
		strcpy(cq->inputfilename, a2);
		shared_q = cq->q;
		shared_struct = cq;
    pthread_t condPool[numOfthreads];
    for (int i=0; i < numOfthreads; ++i) {
     if(pthread_create(&condPool[i], NULL, childthread, (void*) cq)) {
       printf("pthread erroe\n");
     }
   }
   for (int i=0; i < numOfthreads; ++i) pthread_join(condPool[i], NULL);

	 //declare winner
	 char* winnerfile = malloc(sizeof(char)*1024);
	 winnerfile = return_input_file_path(a3,cq->nodes[0].name);
	 strcat(winnerfile, "/");
	 strcat(winnerfile,cq->nodes[0].name);
	 strcat(winnerfile,".txt");
	//  printf("%s\n",winnerfile);
	 FILE* f1 = fopen(winnerfile, "a");
	 dict_t winnerDict = dict_new();
	 DictparseInput(winnerfile,winnerDict);
	 if(f1 == NULL) {
		 printf("error When opening file\n" );
	 }
	 char* winner = malloc(sizeof(char)*1024);
	 winner = returnWinner(winnerDict);
	//  printf("%s\n",winner );
	 fprintf(f1, "WINNER:%s\n",winner);
	//  free(winnerfile);
	 fclose(f1);
	 free(a3);
	 free(a2);
	 dict_free(winnerDict);
    return 0;
}
