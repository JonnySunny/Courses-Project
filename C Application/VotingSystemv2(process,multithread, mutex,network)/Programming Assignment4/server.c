/************************************************
* login:   sunx0458        sunx0725
* name:    Connor C Sun    Zhongyi Sun
* id:      5116486         5320262
* section: 10 T TH 11:15 - 12:30
* date:    04/23/18
*************************************************/
#define _BSD_SOURCE
#define NUM_ARGS 2
#define MAX_CONNECTIONS 100
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
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

struct threadArg {
	struct node* mainnode;
	int accept_sock;
	pthread_mutex_t* mutex;
  struct sockaddr_in clientAddress;
} threadArg;
pthread_mutex_t* mutex;
int ind = 0;
struct node* temp_mainnode;
int id = 2;
int nodecounter(char *s)
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

//bring the input txt and build the nodes
int Node_Counter(char* filename)
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
            c += nodecounter(buf);
        }
				free(buf);
				fclose(f);
        return c+1;

		}

}
void buildNodes(char* filename, node_t * nodes, int num)
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
            parseInputline(buf, nodes, num );
        }
			free(buf);
		}
    fclose(f);
}



void parseInputline(char *s, node_t * nodes, int num)
{
    temp_mainnode = nodes;
    char ** argvp = NULL;
    int makeargv_return = makeargv(trimwhitespace(s), ":", &argvp);
    if(makeargv_return == -1)
    {
        perror("Error when using makeargv!!");
        exit(2);
    }
    int rund = 0;
    int count = 0;
    for(int j=0; j<makeargv_return; j++) {
        if(findnode(nodes, argvp[j], num) != NULL) {
          rund++;
          continue;
        }
        else{
        strcpy(nodes+ind, argvp[j]);
        strcpy((nodes+ind)->parent, argvp[0]);
        if(strcmp((nodes+ind)->parent, (nodes+ind)->name) == 0) {
          strcpy((nodes+ind)->parent, "NULL");
        }
        else {
          findnode(nodes, (nodes+ind)->parent, num)->children[count++] = (nodes+ind)->id;
        }
        ind++;
      }
    }
		for(int j=0; j<makeargv_return; j++) {
				if(strcmp(findnode(nodes, argvp[j], num)->name,argvp[0])== 0) {
					findnode(nodes, argvp[0], num)->child_num = makeargv_return-1;
				}
			}
}

void set_Successor(node_t * nodes, char* name, char* childname,int j) {
    struct node* node1 = findnode(nodes,name,numNodes(nodes));
    struct node* node = findnode(nodes,childname,numNodes(nodes));
    int numchildern = node->child_num;
    int childern[numchildern];
    for(int i = 0; i<numchildern;i++)
    {
      struct node* childnode = findNodeByID(nodes, node->children[i]);
      node1->successor[j] = childnode->id;

      j++;

    }
    j = j -1;
    for(int i = 0; i<numchildern;i++)
    {
      struct node* childnode = findNodeByID(nodes, node->children[i]);
      if(childnode->child_num == 0) {
        continue;
      }
      else{
        j++;
      set_Successor(nodes,name, childnode->name,j);
    }

    }


}

void Add_Votes(struct node* nodes, char* name, char* data, char* sendbackbuf) {
  struct node* node = findnode(nodes,name,numNodes(nodes));
    // Error Code NL
  if(node->child_num != 0) {
    strcpy(sendbackbuf, "NL;");
    strcat(sendbackbuf, name);
    strcat(sendbackbuf, ";\0");
    return;
  }
  if(node->poll == 1)
  {
    // Handle RC
    dict_t dict = findnode(nodes,name,numNodes(nodes))->dict;
		char str[1024];
		char str2[1024][1024];
		for(int k = 0; k < 1024; k++) {
			strcpy(str2[k],"");
		}
		strcpy(str, data);
		char* pch;
		char* pch2;
		char name[1024];
		pch = strtok(str, ",");
		int i = 0;
		while(pch != NULL) {
			strcpy(str2[i],pch);
			i++;
			pch = strtok(NULL,",");
		}
		for(int j = 0; j < sizeof(str2) && strcmp(str2[j], "") != 0; j++) {
				int i = 0;
				int update_value2 = 0;
					pch2 = strtok(str2[j],":");
					while (pch2 != NULL) {
						if(i == 0) {
							strcpy(name,pch2);
							update_value2 = dict_find_value(dict, name);
							i++;
						} else if (i == 1) {
							if(pch2 == NULL)
						  {
								update_value2 = 0;
							}
						  else
						  {
								update_value2 += atoi(pch2);
						  }
							dict_add(dict, name, update_value2);
						}
						pch2 = strtok(NULL,":");
					}
		}
    strcpy(sendbackbuf, "SC; ;");
    strcat(sendbackbuf, "\0");
  }
  else
  {
    strcpy(sendbackbuf, "RC;");
    strcat(sendbackbuf, findnode(nodes,name,numNodes(nodes))->name);
    strcat(sendbackbuf, "\0");
  }
}

void Remove_Votes(struct node* nodes, char* name, char* data, char* sendbackbuf) {
  struct node* node = findnode(nodes,name,numNodes(nodes));
  // Error Code NL
  if(node->child_num != 0) {
    strcpy(sendbackbuf, "NL;");
    strcat(sendbackbuf, name);
    strcat(sendbackbuf, ";\0");
    return;
  }
  if(node->poll == 1){
    // Handle RC
  dict_t dict = node->dict;
  int exist_flag = 0;
  char exist_flag_string[1024] = "";
  int negative_flag = 0;
  char negative_flag_string[1024] = "";
	char str[1024];
	char str2[1024][1024];
	for(int k = 0; k < 1024; k++) {
		strcpy(str2[k],"");
	}
	strcpy(str, data);
	char* pch;
	char* pch2;
	char name[1024];
	pch = strtok(str, ",");
	int i = 0;
	while(pch != NULL) {
		strcpy(str2[i],pch);
		i++;
		pch = strtok(NULL,",");
	}
	for(int j = 0; j < sizeof(str2) && strcmp(str2[j], "") != 0; j++) {
		pch2 = strtok(str2[j],":");
		int i = 0;
		int update_value2 = 0;
		while (pch2 != NULL) {
			if(i == 0) {
				strcpy(name,pch2);
				update_value2 = dict_find_value(dict, name);
				i++;
			} else if (i == 1) {
				if(update_value2 == 0) {
		      // node does not exist
		      exist_flag = 1;
		      strcat(exist_flag_string,name);
		      strcat(exist_flag_string,",");
		    } else {
		        //normal case
		        int recover_value = update_value2;
		        update_value2 -= atoi(pch2);
		        if(update_value2 >= 0) {
		          strcpy(sendbackbuf, "SC; ;");
		          strcat(sendbackbuf, "\0");
		          dict_add(dict, name, update_value2);
		        } else {
		        //substraction cause a negative number
		        negative_flag = 1;
		        strcat(negative_flag_string, name);
		        strcat(negative_flag_string,",");
		        dict_add(dict, name, recover_value);
		      }
		    }
			}
			pch2 = strtok(NULL,":");
		}
	}
	  // // error code IS
    if(negative_flag == 1) {
      negative_flag_string[strlen(negative_flag_string)-1] = ' ';
      strcpy(sendbackbuf, "IS;");
      strcat(sendbackbuf, negative_flag_string);
      strcat(sendbackbuf, ";\0");
      exist_flag = 0;
    } else if(exist_flag == 1) {
      exist_flag_string[strlen(exist_flag_string)-1] = ' ';
      strcpy(sendbackbuf, "IS;");
      strcat(sendbackbuf, exist_flag_string);
      strcat(sendbackbuf, ";\0");
    }
      }
      else
      {
        strcpy(sendbackbuf, "RC;");
        strcat(sendbackbuf, findnode(nodes,name,numNodes(nodes))->name);
        strcat(sendbackbuf, "\0");
      }

}
int Count_Votes(struct node* nodes, char* name, char* sendbackbuf) {
	  struct node* node = findnode(nodes,name,numNodes(nodes));
	  dict_t dict = dict_new();
    int numchildern = node->child_num;
    int childern[numchildern];
    set_Successor(nodes, name, name, 0);
    for(int i = 0; i<sizeof(node->successor) && node->successor[i] != 0; i++) {
      struct node* childnode = findNodeByID(nodes, node->successor[i]);
      dict_merge(childnode->dict, dict);
    }
    char votes_string[1024] = "";
    char* num = malloc(sizeof(char)*1024);
    for (int i = 0; i < dict->len; i++) {
        strcat(votes_string, dict->entry[i].key);
        strcat(votes_string, ":");
        sprintf(num, "%d",dict->entry[i].value );
        strcat(votes_string, num);
        // differentiate the last candidate by the len
        if(i != dict->len - 1){
          strcat(votes_string,",");
        }
    }
    if(dict->len > 0){
    strcpy(sendbackbuf, "SC;");
    strcat(sendbackbuf, votes_string);
    strcat(sendbackbuf, ";");
  } else {
    strcpy(sendbackbuf, "SC;");
    strcat(sendbackbuf, "No votes recorded");
    strcat(sendbackbuf, ";");
  }

    dict_free(dict);
    return 1;
}

int Open_Polls(struct node* nodes, char* name,int flag) {
  struct node* node = findnode(nodes,name,numNodes(nodes));
  // current node
  if(node->poll == 1)
  // open a opened node
  {
    flag = 1;
    return flag;
  }
  else if(node->poll == 0)
  // open a closed node
  {
    flag = 2;
    return flag;
  }
  else
  {
    Open_Polls_rec(nodes,name);
    return flag;
  }
}
void Open_Polls_rec(struct node* nodes, char* name) {
  struct node* node = findnode(nodes,name,numNodes(nodes));
  // current node
    // leaf node
    if(node->child_num == 0){
        if(node->poll == -1){
          node->poll = 1;
      }
    }
    // Non-Leaf node
    else
    {
      if(node->poll == -1)
       {
          node->poll = 1;
          int numchildern = node->child_num;
          for(int i = 0; i<numchildern;i++) {
            struct node* childnode = findNodeByID(nodes, node->children[i]);
            Open_Polls_rec(nodes, childnode->name);
        }
      }
    }
}

int Close_Polls(struct node* nodes, char* name, int flag) {
  struct node* node = findnode(nodes,name,numNodes(nodes));
  if(node->poll == 0)
  {
    flag = 1;
    return flag;
  }
  else if(node->poll == -1) {
    flag = 2;
    return flag;
  }
  else
  {
    Close_Polls_rec(nodes, name);
    return flag;
  }
}
void Close_Polls_rec(struct node* nodes, char* name) {
  struct node* node = findnode(nodes,name,numNodes(nodes));
    if(node->child_num == 0) {
       if(node->poll != 0 ){
        node->poll = 0;
        }
    } else {
      if(node->poll != 0) {
          node->poll = 0;
          int numchildern = node->child_num;
          for(int i = 0; i<numchildern;i++) {
            struct node* childnode = findNodeByID(nodes, node->children[i]);
            Close_Polls_rec(nodes, childnode->name);
        }
      }
    }

}
void Add_Region(struct node* nodes, char* parentname,char* childname,char* sendbackbuf) {
	struct node* parentnode = findnode(nodes,parentname,numNodes(nodes));
	struct node* childnode = findnode(nodes,childname,numNodes(nodes));
	if(strcmp(parentname,childname)==0) {
		return;
	}
	if(parentnode == NULL) {
		parentnode = findNodeByID(nodes,id);
		strcpy(parentnode->name,parentname);
		id++;
	}
	if(childnode == NULL) {
		childnode = findNodeByID(nodes,id);
		strcpy(childnode->name,childname);
		id++;
	}
	parentnode->children[parentnode->state] = childnode->id;
	parentnode->state++;
	parentnode->child_num = parentnode->state;
	strcpy(childnode->parent,parentnode->name);

	// print_nodes(nodes, numNodes(nodes));
}
void Return_Winner(struct node* nodes, char* sendbackbuf){
  struct node* node = findNodeByID(nodes,1);
  if(node->poll == 1) {
    strcpy(sendbackbuf, "RO;");
    strcat(sendbackbuf, node->name);
    strcat(sendbackbuf, ";\0");
    return ;
  } else if(node->poll == -1) {
    strcpy(sendbackbuf, "RC;");
    strcat(sendbackbuf, node->name);
    strcat(sendbackbuf, ";\0");
    return ;
  } else{
    dict_t dict = dict_new();
    set_Successor(nodes, node->name, node->name, 0);
    for(int i = 0; i<sizeof(node->successor) && node->successor[i] != 0; i++) {
      struct node* childnode = findNodeByID(nodes, node->successor[i]);
      dict_merge(childnode->dict, dict);
    }
    int max = 0;
  	char* winner = malloc(sizeof(char)*1024);
    for (int i = 0; i < dict->len; i++)
    {
      if(dict->entry[i].value >= max)
      {
  			max = dict->entry[i].value;
  		}
    }
    for (int i = 0; i < dict->len; i++) {
      if(dict->entry[i].value == max) {
  			strcpy(winner, dict->entry[i].key);
  			winner[strlen(winner)+1] = '\0';
      	break;
  		}
    }
    if(dict->len > 0){
      strcpy(sendbackbuf, "SC;Winner:");
      strcat(sendbackbuf, winner);
      strcat(sendbackbuf, ";");
    } else {
      strcpy(sendbackbuf, "SC;");
      strcat(sendbackbuf, "No votes");
      strcat(sendbackbuf, ";");
    }
    dict_free(dict);
  }
}

void thread_function(void* args) {
	pthread_mutex_lock(mutex);
  struct threadArg* arg = args;
  node_t* mainnode = arg->mainnode;
  int accept_sock = arg->accept_sock;
  struct sockaddr_in clientAddress = arg->clientAddress;
	 char addr[256] = "";
	 strcpy(addr,inet_ntoa(clientAddress.sin_addr));
	 unsigned short port = ntohs(clientAddress.sin_port);
	 if(accept_sock != -1) printf("Connection initiated from client at %s:%hu\n", addr, port); //problem with clientAddress
	 // Buffer for data.
	 char buffer[256];
	 int bytes;
	 //Read from the socket and print the contents.
	 int t;
	 while(t = read(accept_sock, buffer, sizeof(buffer)) > 0)
	 {

			 printf("Request received from client at %s:%hu, %s\n", addr, port, buffer);
			 char sendbackbuf[256] = "here is return message.\n";
			 char str[1024];
			 char name[1024];
			 char command[1024];
			 char data[1024];
 			 strcpy(str, buffer);
 			 char* pch;
 			 pch = strtok(str, ";");
 			 int i = 0;
 			 while(pch != NULL) {
 				 	if(i == 0) {
 						strcpy(command,pch);
						i++;
 					} else if(i == 1) {
 						strcpy(name,pch);
						i++;
 					} else if(i == 2) {
 						strcpy(data, pch);
 					}
 				 	pch = strtok(NULL,";");
 			 }

			 //if it's acceptable data
				if(findnode(mainnode,name,numNodes(mainnode)) == NULL && strcmp("RW", command) != 0 ) {
				 strcpy(sendbackbuf, "NR;");
				 strcat(sendbackbuf, name);
				 strcat(sendbackbuf, ";\0");
			 }
			 else
			 {

				 if(strcmp("AV", command) == 0)
				 {
					 Add_Votes(mainnode, name,data, sendbackbuf);
				 }
				 else if(strcmp("CV", command) == 0)
				 {
					 int count_vote = Count_Votes(mainnode, name, sendbackbuf);
				 }
				 else if(strcmp("AR", command) == 0)
				{
					Add_Region(mainnode, name,data,sendbackbuf);
					strcpy(sendbackbuf, "SC; ;");
				}
				 else if(strcmp("RV", command) == 0)
				 {
					 Remove_Votes(mainnode, name,data, sendbackbuf);
				 }
				 else if(strcmp("OP", command) == 0)
				 {
					 int open_value = Open_Polls(mainnode, name, 0);
					 if(open_value == 1) {
						 strcpy(sendbackbuf, "PF;");
						 strcat(sendbackbuf, name);
						 strcat(sendbackbuf, "open;\0");
					 } else if(open_value == 2) {
						 strcpy(sendbackbuf, "RR;");
						 strcat(sendbackbuf, name);
						 strcat(sendbackbuf, ";\0");
					 }
					 else{
						 strcpy(sendbackbuf, "SC; ;");
					 }
				 }
				 else if(strcmp("CP", command) == 0)
				 {
					 // Close_Polls(mainnode, argvp[1], sendbackbuf);
					 int close_value = Close_Polls(mainnode, name, 0);
					 if(close_value == 1) {
						 strcpy(sendbackbuf, "PF;");
						 strcat(sendbackbuf, name);
						 strcat(sendbackbuf, " closed;\0");
					 } else if(close_value == 2){
						 strcpy(sendbackbuf, "PF;");
						 strcat(sendbackbuf, name);
						 strcat(sendbackbuf, " unopened;\0");
					 }else{
						 strcpy(sendbackbuf, "SC; ;");
					 }
				 }
				 else if(strcmp("RW", command) == 0)
				 {
					 Return_Winner(mainnode, sendbackbuf);
				 }
				 else
				 {
					 // Unhandled Command
					 strcpy(sendbackbuf, "UC;");
					 strcat(sendbackbuf, command);
					 strcat(sendbackbuf, ";\0");
				 }
			 }
			 // handlde Unhandled ERROR
			 char command_r[3];
			 command_r[0] = sendbackbuf[0];
			 command_r[1] = sendbackbuf[1];
			 command_r[2] = '\0';
			 if(strcmp(command_r,"SC")==0||strcmp(command_r,"UC")==0||strcmp(command_r,"NR")==0||
			 strcmp(command_r,"RO")==0||strcmp(command_r,"RC")==0||strcmp(command_r,"RR")==0||
			 strcmp(command_r,"PF")==0||strcmp(command_r,"NL")==0||strcmp(command_r,"IS")==0){
				 send(accept_sock, sendbackbuf, sizeof(sendbackbuf), 0);
			 }
			 else {
				 strcpy(sendbackbuf, "UE;");
				 strcat(sendbackbuf, ";\0");
				 send(accept_sock, sendbackbuf, sizeof(sendbackbuf), 0);
			 }
			 printf("Sending response to client at %s:%hu, %s\n", addr, port, sendbackbuf);
	 }

	 //Close the connection.
	 printf("Closed connection with client at %s:%hu\n", addr, port);
	 close(accept_sock);

 // Close the server socket.
  // close(sock);
	pthread_mutex_unlock(mutex);
  pthread_detach(pthread_self());
}
int main(int argc, char** argv) {
  //checking number of argguments
	if (argc < NUM_ARGS + 1) {
		printf("Wrong number of args, expected %d, given %d\n", NUM_ARGS, argc - 1);
		printf("Usage:./server <DAG File> <SERVER PORT>\n");
		exit(1);
	}
	int SERVER_PORT = atoi(argv[2]);

	// Create a TCP socket.
	int sock = socket(AF_INET , SOCK_STREAM , 0);

	// Bind it to a local address.
	struct sockaddr_in servAddress;
	servAddress.sin_family = AF_INET;
	servAddress.sin_port = htons(SERVER_PORT);
	servAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (struct sockaddr *) &servAddress, sizeof(servAddress));
	// Listen on this socket.
	int backlog = 10;
	listen(sock, backlog);
  printf("Server listening on port %d\n", SERVER_PORT);
	mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex, NULL);
	// A server typically runs infinitely, with some boolean flag to terminate.
	while (1) {
		// Now accept the incoming connections.
		struct sockaddr_in clientAddress;
		socklen_t size = sizeof(struct sockaddr_in);
		// Accept a connection.
		int accept_sock = accept(sock, (const struct sockaddr *) &clientAddress, &size);
		char *buffer = malloc(sizeof(char)*256);
		int t = read(accept_sock, buffer, 256);
		char str[1024];
		strcpy(str, buffer);
		int numofNodes;
	 //  printf("Str here is %s\n",str[0]);
		if(str[0] == 'E')  {
			 char* pch;
			 pch = strtok(str, "!");
			 int i = 0;
			 while(pch != NULL) {
					if(i == 1) {
						numofNodes = atoi(pch);
						break;
					}
					i++;
					pch = strtok(NULL,"!");
			 }
		}
		else {
			numofNodes = 0;
		}
		//Build Node Tree baseded on }
		//Build Node Tree baseded on DAG
		int c = Node_Counter(argv[1]);
		struct node* mainnode = malloc(sizeof(node_t)*(c+numofNodes));
		for(int e = 0; e < c+numofNodes; e++)
		{
			(mainnode+e)->mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
			pthread_mutex_init((mainnode+e)->mutex, NULL);
			(mainnode+e)->dict = dict_new();
			(mainnode+e)->child_num = 0;
			(mainnode+e)->id = e+1;
			// 1 is true (open); 0 is false (close); -1 is initial state
			(mainnode+e)->poll = -1;
			(mainnode+e)->state = 0;
		}
		buildNodes(argv[1], mainnode,c+numofNodes);


	  pthread_t * thread = malloc(sizeof(pthread_t));
    struct threadArg *arg = malloc(sizeof(threadArg));
    arg->mainnode = mainnode;
    arg->accept_sock = accept_sock;
    arg->mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(arg->mutex, NULL);
    arg->clientAddress = clientAddress;
    int ret = pthread_create(thread, NULL, thread_function, (void*) arg);
    if(ret != 0) {
       printf ("Create pthread error!\n");
       exit (1);
     }
  }
	// Close the server socket.
	close(sock);
}
