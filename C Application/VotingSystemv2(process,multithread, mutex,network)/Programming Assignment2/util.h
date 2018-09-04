#include <errno.h>
#include <stdlib.h>
#include <string.h>

/* The maximum amount of bytes for a file name */
#define MAX_FILE_NAME_SIZE 255

/* The maximum amount of bytes for each I/O operation */
#define MAX_IO_BUFFER_SIZE 1024


FILE* file_open(char* file_name) {
	FILE* file;
	file = fopen(file_name, "r");
	return file;
}
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



/**********************************
*
* Taken from stack overflow website, and changes some
* https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c
*
*********************************/
//creat a dictionary which store the vote information dynamicly
//And also define the realted functions which can be convenient to store information
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

void view_dict_info(dict_t dict) {
  for (int i = 0; i < dict->len; i++) {
    printf("Entry %d : Name is %s , Value is %d\n",(i+1),dict->entry[i].key,dict->entry[i].value );
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
		return argvp[makeargv_return-1];
	}
}
