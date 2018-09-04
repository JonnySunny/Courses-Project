#include <errno.h>
#include <stdlib.h>
#include <string.h>

/* The maximum amount of bytes for a file name */
#define MAX_FILE_NAME_SIZE 255

/* The maximum amount of bytes for each I/O operation */
#define MAX_IO_BUFFER_SIZE 1024
/* same logic as PA1 Take from https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
*/
char* read_line(char* buffer, FILE* fp) {
	int ch;
	int i = 0;
 	size_t buff_len = 0;
  buffer = malloc(buff_len + 1);
 if (!buffer) return NULL;
 // Out of memory
  while ((ch = fgetc(fp)) != '\n' && ch != EOF)
	{
		buff_len++;
		void *tmp = realloc(buffer, buff_len + 1);
		if (tmp == NULL) { free(buffer); return NULL; }
			// Out of memory }
		 buffer = tmp; buffer[i] = (char) ch; i++;
	  }
		buffer[i] = '\0';
		 // Detect end
		if (ch == EOF && (i == 0 || ferror(fp))) { free(buffer); return NULL; } return buffer;
}


char* return_log_file_path(char* s) {
  char* logfilepath = malloc(sizeof(char)*1024);
  strcpy(logfilepath, s);
  strcat(logfilepath,"/");
  strcat(logfilepath,"log.txt");
	logfilepath[strlen(logfilepath)+1] = '\0';
  return logfilepath;
}
char* return_input_file_path(char* s, char* name) {
  char* inputfilepath = malloc(sizeof(char)*1024);
  char* inputfilename = malloc(sizeof(char)*1024);
  strcpy(inputfilepath, s);
  strcat(inputfilepath,"/");
  strcpy(inputfilename,name);
  strcat(inputfilepath,inputfilename);
	// strcat(inputfilepath,"\0");
	// logfilepath
	inputfilepath[strlen(inputfilepath)+1] = '\0';
  return inputfilepath;
}
/**********************************
*
* Taken from stack overflow website, and changes some
* https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c
*
*********************************/
//creat a dictionary which store the vote information dynamicly
//And also define the realted functions which can be convenient to store and manipulate information


/**********************************
*
* Taken from stack overflow website, and changes some
* https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c
*
*********************************/
//creat a dictionary which store the vote information dynamicly
//And also define the realted functions which can be convenient to store and manipulate information
typedef struct dict_entry_s {
    char *key;
    int value;
} dict_entry_s;

typedef struct dict_s {
    int len;
    int cap;
    dict_entry_s *entry;
} dict_s, *dict_t;

int dict_find_index(dict_t dict, char *key) {
    for (int i = 0; i < dict->len; i++) {
        if (strcmp(dict->entry[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

int dict_find_value(dict_t dict, char *key) {
    int idx = dict_find_index(dict, key);
    if(idx == -1) {
      return 0;
    }
    else {
      return dict->entry[idx].value;
    }
}

void dict_add(dict_t dict, char *key, int value) {
   int idx = dict_find_index(dict, key);
   if (idx != -1) {
       dict->entry[idx].value = value;
       return;
   }
   if (dict->len == dict->cap) {
       dict->cap *= 2;
       dict->entry = realloc(dict->entry, dict->cap * sizeof(dict_entry_s));
   }
   dict->entry[dict->len].key = strdup(key);
   dict->entry[dict->len].value = value;
   dict->len++;
}

dict_t dict_new(void) {
    dict_s proto = {0, 10, malloc(10 * sizeof(dict_entry_s))};
    dict_t d = malloc(sizeof(dict_s));
    *d = proto;
    return d;
}

void dict_free(dict_t dict) {
    for (int i = 0; i < dict->len; i++) {
        free(dict->entry[i].key);
    }
    free(dict->entry);
    free(dict);
}

void dict_merge(dict_t dict1, dict_t dict2) {
	if(dict1->len >= dict2-> len) {
		// first dictionay is longer than dict2
		// merging dict1 to dict2, dict2 has both information from 1 and 2;
		for(int i = 0; i < dict1->len; i++) {
			int val1 = dict_find_value(dict1, dict1->entry[i].key);
			int val2 = dict_find_value(dict2, dict1->entry[i].key);
			val2 += val1;
			dict_add(dict2,dict1->entry[i].key, val2);
		}
	}
	else {
		// dict2 is longer than dict1
		for(int i = 0; i < dict2->len; i++) {
			int val1 = dict_find_value(dict1, dict2->entry[i].key);
			int val2 = dict_find_value(dict2, dict2->entry[i].key);
			val2 += val1;
			dict_add(dict2,dict2->entry[i].key, val2);
		}
	}
}

void view_dict_info(dict_t dict) {
	if(dict->len == 0) {
		printf("Try to print the empty dictionary\n");
		return;
	}
  for (int i = 0; i < dict->len; i++) {
    printf("Entry %d : Name is %s , Value is %d\n",(i+1),dict->entry[i].key,dict->entry[i].value );
  }

}

void dict_clear(dict_t dict) {

		dict->len = 0;
}

char* returnWinner(dict_t dict) {
	int max = 0;
	char* winner = malloc(sizeof(char)*1024);

  for (int i = 0; i < dict->len; i++) {
    if(dict->entry[i].value >= max) {
			max = dict->entry[i].value;
		}
  }

  for (int i = 0; i < dict->len; i++) {
    if(dict->entry[i].value == max) {
			strcpy(winner, dict->entry[i].key);
			// strcat(winner,"\0");
			winner[strlen(winner)+1] = '\0';
			return winner;
			// return dict->entry[i].key;
		}
  }
}

/**********************************
*
* Taken from Unix Systems Programming, Robbins & Robbins, p37
*
*********************************/
int makeargv(const char *s, const char *delimiters, char ***argvp) {
   int error;
   int i;
   int numtokens;
   const char *snew;
   char *t;

   if ((s == NULL) || (delimiters == NULL) || (argvp == NULL)) {
      errno = EINVAL;
      return -1;
   }
   *argvp = NULL;
   snew = s + strspn(s, delimiters);
   if ((t = malloc(strlen(snew) + 1)) == NULL)
      return -1;
   strcpy(t,snew);
   numtokens = 0;
   if (strtok(t, delimiters) != NULL)
      for (numtokens = 1; strtok(NULL, delimiters) != NULL; numtokens++) ;

   if ((*argvp = malloc((numtokens + 1)*sizeof(char *))) == NULL) {
      error = errno;
      free(t);
      errno = error;
      return -1;
   }

   if (numtokens == 0)
      free(t);
   else {
      strcpy(t,snew);
      **argvp = strtok(t,delimiters);
      for (i=1; i<numtokens; i++)
         *((*argvp) +i) = strtok(NULL,delimiters);
   }
   *((*argvp) + numtokens) = NULL;
   return numtokens;
}

/**********************************
*
* Taken from Unix Systems Programming, Robbins & Robbins, p38
*
*********************************/
void freemakeargv(char **argv) {
   if (argv == NULL)
      return;
   if (*argv != NULL)
      free(*argv);
   free(argv);
}

char *trimwhitespace(char *str) {
  char *end;
  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;

  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}
char* get_current_directory_name(char* path) {
	char ** argvp = NULL;
	int makeargv_return = makeargv(trimwhitespace(path), "/", &argvp);
	if(makeargv_return == -1) {
		perror("Error when using makeargv!!");
		exit(4);
	}
	else {
		// int i = 0;
		// printf("%d\n",makeargv_return);
		// while(i < makeargv_return) {
		//   printf("%d: %s\n", i, argvp[i]);
		//   i++;
		// }
		// printf("current dir name : %s\n", argvp[makeargv_return-1]);
		char* temp = malloc(sizeof(char)*1024);
		strcpy(temp,argvp[makeargv_return-1] );
		// strcat(temp,"\0");
		temp[strlen(temp)+1] = '\0';
		return temp;
		// return argvp[makeargv_return-1];
	}
}
char* get_current_directory_previous_path(char* path) {
	char ** argvp = NULL;
	int makeargv_return = makeargv(trimwhitespace(path), "/", &argvp);
	if(makeargv_return == -1) {
		perror("Error when using makeargv!!");
		exit(4);
	}
	else if(makeargv_return == 1) {
		return NULL;
	}
	else {
		char* rest = malloc(sizeof(char)*1024);
		strncpy(rest, path, strlen(path)-strlen(argvp[makeargv_return-1])-1);
		*(rest+strlen(path)-strlen(argvp[makeargv_return-1])-1) = '\0';
		// strcmp(rest,'\0');
		return rest;
	}
}
/**********************************
*
* create mpde structure
*
*
*********************************/
typedef struct node{
	char name[1024];
	char path[1024];
	pthread_mutex_t* mutex;
	char parent[1024];
	dict_t dict;
	int id;
	int children[1024];
	int successor[1024];
	int child_num;
	int poll;
	int state;
} node_t;


node_t* findNodeByID(node_t* start, int tobefound){
	//Find the node in question
		node_t* temp = start;
		while(temp->id!=NULL){
			if( temp->id == tobefound){
				return temp;
			}
			temp++;
		}
		return NULL;
}

int numNodes(node_t* start){
	//Find the node in question
		int t = 0;
		node_t* temp = start;
		while(temp->id!=NULL){
			t++;
			temp++;
		}
		return t;
}
node_t* findnode(node_t *nodes, char* name, int num) {
	node_t* temp = nodes;
	for(int i = 0; i< num; i++) {
		if(strcmp(temp->name, name) == 0) {
			return temp;
		}
		temp++;
	}
	return NULL;
}

print_array(int num[]) {
	for(int i = 0;i<sizeof(num); i++){
		printf("%d\n",num[i]);
	}
}
print_nodes(node_t *mainnodes, int num) {
	int p;
	for (p = 0; p < num; p++){
		if(mainnodes[p].child_num==0){
			printf("%s","\n Leaf Node : ");
			printf("%s",mainnodes[p].name);
			printf("Successors are : \n");
			print_array(mainnodes[p].successor);
		}
		else{
			printf("\n Non-Leaf Nodes %s",mainnodes[p].name);
						printf("\n Non-Leaf Nodes Parent %s",mainnodes[p].parent);
						printf("Successors are : \n");
						print_array(mainnodes[p].successor);
			printf("\n Listing their children: ");
			int x;
			for(x=0;x<mainnodes[p].child_num;x++){
				printf("\n %d ",mainnodes[p].children[x]);
				printf(" %s ",(findNodeByID(mainnodes, mainnodes[p].children[x])->name));
				// printf("Successors are : \n");
				// print_array(mainnodes[p].successor);
			}
		}
	}
		printf("\n");
}
