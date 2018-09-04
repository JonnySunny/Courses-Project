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
#include "makeargv.h"

#define MAX_NODES 100

// variables
char* candidates;
int num_candidates;
struct node* temp_mainnode;
struct node* current_parent_node;
struct node* temp_node;
//Function signatures
int parseInput(char *filename, node_t *n);
int parseInputLine(char *s, node_t *n);
void execNodes(node_t *n);
void find_circle(node_t *n);
/**Function : parseInput
 * Arguments: 'filename' - name of the input file
 *               'n' - Pointer to Nodes to be allocated by parsing
 * Output: Number of Total Allocated Nodes
 * About parseInput: parseInput is supposed to
 * 1) Open the Input File [There is a utility function provided in utility handbook]
 * 2) Read it line by line : Ignore the empty lines [There is a utility function provided in utility handbook]
 * 3) Call parseInputLine(..) on each one of these lines
 ..After all lines are parsed(and the DAG created)
 4) Assign node->"prog" ie, the commands that each of the nodes has to execute
 For Leaf Nodes: ./leafcounter <arguments> is the command to be executed.
 Please refer to the utility handbook for more details.
 For Non-Leaf Nodes, that are not the root node(ie, the node which declares the winner):
 ./aggregate_votes <arguments> is the application to be executed. [Refer utility handbook]
 For the Node which declares the winner:
 This gets run only once, after all other nodes are done executing
 It uses: ./find_winner <arguments> [Refer utility handbook]
 */
int parseInput(char *filename, node_t *n) {
  num_candidates = 0;
  temp_mainnode = n;
  FILE* f = fopen(filename,"r");
  // Error handle miss input file
  if(f == NULL) {
    perror("Error !! Failed when opening file\n ");
    exit(1);
  }
  else{
    char* buf = malloc(sizeof(char)*1024);
    int num_node = 0;
    while(1) {
          buf = read_line(buf,f);
          if(buf == NULL) break; // break when read on the empty line
          if(buf[0] == '#') {
            printf("Reading comment line right now, ignore it!\n");
          } else {
            num_node += parseInputLine(buf, n);
          }
        }
    fclose(f);
    int i = 0;
    while(i < num_node+1) {
      // root node
      if(strcmp((n+i)->name, "Who_Won") == 0) {
        strcpy((n+i)->prog, "./find_winner");
      }
      // not Leaf nodes
      else if((n+i)->num_children != 0) {
        strcpy((n+i)->prog, "./aggregate_votes");
      }
      // leaf node
      else {
        strcpy((n+i)->prog, "./leafcounter");
      }
        i++;
      }
        free(buf);
        return num_node;
    }

}
/**Function : parseInputLine
 * Arguments: 's' - Line to be parsed
 *               'n' - Pointer to Nodes to be allocated by parsing
 * Output: Number of Region Nodes allocated
 * About parseInputLine: parseInputLine is supposed to
 * 1) Split the Input file [Hint: Use makeargv(..)]
 * 2) Recognize the line containing information of
 * candidates(You can assume this will always be the first line containing data).
 * You may want to store the candidate's information
 * 3) Recognize the line containing "All Nodes"
 * (You can assume this will always be the second line containing data)
 * 4) All the other lines containing data, will show how to connect the nodes together
 * You can choose to do this by having a pointer to other nodes, or in a list etc-
 * */
 int parseInputLine(char *s, node_t *n) {
   char ** argvp = NULL;
   // to differentiate first two lines with others by ":"
   //error handling
   int makeargv_return = makeargv(trimwhitespace(s), ":", &argvp);
   if(makeargv_return == -1) {
     perror("Error when using makeargv!!");
     exit(4);
   }
   else{
     if(makeargv_return == 1) {
     // if the argvp[0] is "Who_Won", then it must be the second line, else it must be the first_line accroding to our assumptions.
         int temp = makeargv(trimwhitespace(s), " ", &argvp);
         // Error handling
         if(temp == -1) {
           perror("Error when using makeargv!!");
           exit(4);
         } else{
          //error handle non number candidates
           if(strcmp(argvp[0], "Who_Won") != 0) {
               char* str = malloc(sizeof(char)*1024);
               strcpy(str, argvp[0]);
               for(int i = 0; str[i] != '\0'; i++) {
                 if(isdigit(str[i]) == 0) {
                     perror("Error !! The number of candidates input is not combined by all digits!!\n");
                     exit(7);
                 }
               }
               free(str);
             }
       // first_line
         if(strcmp(argvp[0], "Who_Won") != 0) {
             num_candidates = atoi(argvp[0]);
             //error handle incorrect number of candidates
             //count how many actual candidates
              int count = 1;
              while(1) {
                if(argvp[count] == NULL) break;
                count++;
              }
              count--;
              // compare count with num_candidates, if they are different, then we know the information is not correct
              if(count != num_candidates) {
                printf("Number candidates input is %d \n", num_candidates);
                printf("Actual numer candidates is %d \n ", count);
                perror(" 'Number' candidates is different with actual number candidates \n");
                exit(6);
              }
             // error handle: The first_line starts not beggining with #
                 if(num_candidates < 0) {
                     perror("Error !! The first number is negative, change it to positve");
                     num_candidates = (-1)*num_candidates;
                 }
               // normal case
                 candidates = (char*) malloc(sizeof(char)*(num_candidates+1));
                 strcpy(candidates, s);
                 free(argvp);
                 return 0;}
            else {
                 // second line
             char* str = "Output_";
             int num_nodes = 0;
             for(int i = 0; argvp[i] != '\0'; i++){
                num_nodes++;
                 // give name to each node
                 strcpy((n+i)->name, argvp[i]);
                 // give Input to each nodes
                 strcpy((n+i)->input, argvp[i]);
                 // give output to each node
                 strcpy((n+i)->output, argvp[i]);
                 prepend((n+i)->output, str);
                 // give id to each node starting from 1, 0 means no child
                 (n+i)->id = i+1;
                 (n+i)->status = 0;
                 // give pid to each node;
                 (n+i)->pid = i+1;}
         // perror("Read sencond line error ");
                  free(argvp);
                 return num_nodes;}}
       } else {
       // after first two lines, the format for the rest is
       // parent : children1 children2 etc
         int  num_children = 0;

         int  makeargv_value = makeargv(trimwhitespace(s), " ", &argvp);
         if(makeargv_value == -1) {
           perror("Error !! The first_line starts not beggining with number");
           exit(2);
         } else {
           // struct node*
           current_parent_node = (struct node*)malloc(sizeof(struct node));
           for(int i = 0; argvp[i] != '\0'; i++){
               // first node is current parent node in this line
               if(i == 0) {
                  current_parent_node = findnode(n, argvp[i]);
               }
               if(strcmp(":", argvp[i]) != 0 && i != 0) {
                 (current_parent_node->children)[num_children] = (findnode(n, argvp[i]))->id;
                 num_children++;
               }
           }
           current_parent_node->num_children = num_children;

           }
            free(argvp);
            return 0;
         }
       }
     }

/**Function : execNodes
 * Arguments: 'n' - Pointer to Nodes to be allocated by parsing
 * About execNodes: parseInputLine is supposed to
 * If the node passed has children, fork and execute them first
 * Please note that processes which are independent of each other
 * can and should be running in a parallel fashion
 * */
void execNodes(node_t *n) {

 if(n->num_children == 0){

   // parse args
    char str[10];
    sprintf(str, "%d", num_candidates);
    char *args [4+num_candidates+1];
    args[0] = n->prog;
    args[1] = n->input;
    FILE* f = fopen(args[1],"r");
    // Error handle miss input file
    if(f == NULL) {
      printf("Error !! Failed when opening file %s, creating a new one to make sure the Out_put_Who_Won will be generated \n ", args[1]);
      FILE* nf = fopen(args[1],"w");
      fprintf(nf, "0");
      fclose(nf);
      // re - call execNode again
      execNodes(n);
    }
    else {
      fclose(f);
      args[2] = n->output;
      args[3] = str;
      // loop through the candidates
      char** s;
      int makeargv_return = makeargv(trimwhitespace(candidates), " ", &s);
      if(makeargv_return == -1) {
          perror("Error when using makeargv!!\n");
          exit(4);
      } else {
        for(int i = 1; i < num_candidates+1; i++) {
          args[3+i] = s[i];
        }
        args[3+num_candidates+1] = NULL;
        //After gather args
        int execv_return = execv(args[0], args);
        if(execv_return == -1) {
          perror("Error !! when excuting leafcounter\n");
          exit(5);
        }
    }
      free(s);
    }
}
  else {

    // parse args2
    char str[10];
    sprintf(str, "%d", num_candidates);
    char str2[10];
    sprintf(str2, "%d", n->num_children);
    pid_t pid;
    char *args2[4+num_candidates+n->num_children+1];
    args2[0] = n->prog;
    args2[1] = str2;
    for(int i = 0; i< n->num_children; i++ ) {
      args2[2+i] = findNodeByID(temp_mainnode, n->children[i])->input;
    }
    args2[2+n->num_children] = n->output;
    args2[3+n->num_children] = str;
    // loop through the candidates
    char** s;
    int makeargv_return = makeargv(trimwhitespace(candidates), " ", &s);
    if(makeargv_return == -1) {
        perror("Error when using makeargv!!\n");
        exit(4);
    } else{
        for(int i = 1; i < num_candidates+1; i++) {
          args2[3+n->num_children+i] = s[i];
        }
        args2[4+n->num_children+num_candidates] = NULL;
        //After gather args2 recursive call the execNodes
        for(int i = 0; i< n-> num_children;i++) {
          pid = fork();
          if(pid == 0 ) {
            // find the current children
            temp_node = findNodeByID(temp_mainnode, n->children[i]);
            execNodes(temp_node);
          } else if (pid == -1 ) {
            perror("Error when calling fork\n");
            exit(3);
          }
        }
        // wait all children finished
        for(int i = 0; i< n-> num_children; i++) {
          wait(NULL);;
        }
        // adding agrs2 wait for exec
        for(int i = 0; i< n->num_children; i++ ) {
          args2[2+i] = prepend(findNodeByID(temp_mainnode, n->children[i])->input, "Output_");
        }
        free(s);
        int execv_return = execv(args2[0], args2);
        if(execv_return == -1) {
          perror("Error !!");
          if(strcmp(args2[0],"./aggregate_votes")) {
            perror("Error happened During aggregate_votes!!\n");
          } else if(strcmp(args2[0],"./find_winner")) {
            perror("Error happened During find_winner!!\n");}
          exit(5);}
        }

      }
  }

void find_circle(node_t *n) {
  if (n->num_children == 0 ) {
    n->status = 1;
  }
   else {
         for(int i = 0; i< n-> num_children;i++) {
             temp_node = findNodeByID(temp_mainnode, n->children[i]);
             if(temp_node->status == 1) {
               printf("Circle found at %s! It doesn't run the execNodes.\n", temp_node->name);
               exit(8);
             }
             temp_node->status = 1;
             find_circle(temp_node);
           }
       }
     }
struct node* get_current_parent_node(){
  return current_parent_node;
}
struct node* get_candidates(){
  return candidates;
}
struct node* get_temp_mainnodes(){
  return temp_mainnode;
}
int main(int argc, char **argv){
    //Allocate space for MAX_NODES to node pointer
    struct node* mainnodes=(struct node*)malloc(sizeof(struct node)*MAX_NODES);
    struct node* current_parent_node;
    struct node* candidates;
    struct node* temp_mainnode;
    if (argc != 2){
        printf("Usage: %s Program\n", argv[0]);
        return -1;
    }
    //call parseInput
    int num = parseInput(argv[1], mainnodes);
    printf("Number of nodes is %d\n", num);
    find_circle(mainnodes);
    execNodes(mainnodes);
    current_parent_node = get_current_parent_node();
    candidates = get_candidates();
    temp_mainnode = get_temp_mainnodes();
    free(candidates);
    free(current_parent_node);
    free(mainnodes);
    free(temp_mainnode);
    return 0;

}
