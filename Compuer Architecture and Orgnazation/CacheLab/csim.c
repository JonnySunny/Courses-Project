/* 
 *Zhongyi Sun
 *sunx0725
 * csim.c - A cache simulator that can replay traces from Valgrind
 *     and output statistics such as number of hits, misses, and
 *     evictions.  The replacement policy is MRU.
 *
 *
 * The function printSummary() is given to print output.
 * Please use this function to print the number of hits, misses and evictions.
 * This is crucial for the driver to evaluate your work. 
 */
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "cachelab.h"

//#define DEBUG_ON 
#define ADDRESS_LENGTH 64

/* Type: Memory address */
typedef unsigned long long int mem_addr_t;

/* Type: Cache line
   MRU is a counter used to implement MRU replacement policy  */
typedef struct cache_line {
    char valid;
    mem_addr_t tag;
    unsigned long long int mru;
} cache_line_t;

typedef cache_line_t* cache_set_t;
typedef cache_set_t* cache_t;

/* Globals set by command line args */
int verbosity = 0; /* print trace if set */
int s = 0; /* set index bits */
int b = 0; /* block offset bits */
int E = 0; /* associativity */
char* trace_file = NULL;

/* Derived from command line args */
int S; /* number of sets */
int B; /* block size (bytes) */

/* Counters used to record cache statistics */
int miss_count = 0;
int hit_count = 0;
int eviction_count = 0;
unsigned long long int mru_counter = 1;

/* The cache we are simulating */
cache_t cache;  
mem_addr_t set_index_mask, set_tag_mask;

/* 
 * initCache - Allocate memory, write 0's for valid and tag and MRU
 * also computes the set_index_mask
 */
void initCache()
{
	int i,j;
	set_index_mask = 0x7fffffff >> (31-s);
	set_tag_mask = 0x7fffffff >> (31-s-b);
	cache= malloc(S*sizeof(cache_line_t));

	for(i = 0; i<S;i++){
		cache[i] = malloc(E*sizeof(cache_line_t));
		for(j = 0; j<E;j++){
			cache[i][j].valid = '0';
			cache[i][j].tag = 0;
			cache[i][j].mru = 0;
			}
	
      }
}


/* 
 * freeCache - free allocated memory
 */
void freeCache()
{
    int i;
    for (i=0; i<S; i++){
        free(cache[i]);
    }
    free(cache);
}


/* 
 * accessData - Access data at memory address addr.
 *   If it is already in cache, increast hit_count
 *   If it is not in cache, bring it in cache, increase miss count.
 *   Also increase eviction_count if a line is evicted.
 */
void accessData(mem_addr_t addr)
{
    
     mem_addr_t get_setNo, get_tag, max_mru;
     get_setNo = (addr >> b) & set_index_mask;
     get_tag = (addr>>(b+s)) & set_tag_mask;
     max_mru = 0;
     mru_counter++;
       for ( int i = 0; i < E ; i++){
			if(cache[get_setNo][i].valid == '1'  && get_tag == cache[get_setNo][i].tag ){
			hit_count++;
			cache[get_setNo][i].mru = mru_counter;
			return;
	  }
    }
   for ( int j = 0; j < E  ; j++){
	  if(cache[get_setNo][j].mru> max_mru){
		  max_mru = cache[get_setNo][j].mru;
		  }
	  if(cache[get_setNo][j].valid == '0'){
		  
		  cache[get_setNo][j].valid = '1';
		  cache[get_setNo][j].tag = get_tag;
		  cache[get_setNo][j].mru = mru_counter;
		  miss_count++;
		  return ;
		  }
	}
   
	for ( int k = 0; k < E ; k++){
	  if(cache[get_setNo][k].mru == max_mru){
		 cache[get_setNo][k].tag = get_tag;
		  cache[get_setNo][k].mru = mru_counter;
		  miss_count++;
		  eviction_count++;
		  return; 

		}
	} 
 
   
}


/*
 * replayTrace - replays the given trace file against the cache 
 */
void replayTrace(char* trace_fn)
{
    char buf[1000];
    mem_addr_t addr=0;
    unsigned int len=0;
    FILE* trace_fp = fopen(trace_fn, "r");

    if(!trace_fp){
        fprintf(stderr, "%s: %s\n", trace_fn, strerror(errno));
        exit(1);
    }

    while( fgets(buf, 1000, trace_fp) != NULL) {
        /* buf[Y] gives the Yth byte in the trace line */

        /* Read address and length from the trace using sscanf 
           E.g. sscanf(buf+3, "%llx,%u", &addr, &len);
         */
		switch(buf[1]){
			case 'M':sscanf(buf+3, "%llx,%u", &addr, &len);
				accessData(addr);
				accessData(addr);
			break;
			case 'S':sscanf(buf+3, "%llx,%u", &addr, &len);
				accessData(addr);
			break;
			case 'L':sscanf(buf+3, "%llx,%u", &addr, &len);
				accessData(addr);
			break;	
			
			}
        /*  
         *    ACCESS THE CACHE, i.e. CALL accessData
		 *    Be careful to handle 'M' accesses	
         */
    }

    fclose(trace_fp);
}

/*
 * printUsage - Print usage info
 */
void printUsage(char* argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}

/*
 * main - Main routine 
 */
int main(int argc, char* argv[])
{
    char c;

    while( (c=getopt(argc,argv,"s:E:b:t:vh")) != -1){
        switch(c){
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            trace_file = optarg;
            break;
        case 'v':
            verbosity = 1;
            break;
        case 'h':
            printUsage(argv);
            exit(0);
        default:
            printUsage(argv);
            exit(1);
        }
    }

    /* Make sure that all required command line args were specified */
    if (s == 0 || E == 0 || b == 0 || trace_file == NULL) {
        printf("%s: Missing required command line argument\n", argv[0]);
        printUsage(argv);
        exit(1);
    }

    /* Compute S, E and B from command line args */
    S = 2<<s;
    B = 2<<b;
 
    /* Initialize cache */
    initCache();

#ifdef DEBUG_ON
    printf("DEBUG: S:%u E:%u B:%u trace:%s\n", S, E, B, trace_file);
    printf("DEBUG: set_index_mask: %llu\n", set_index_mask);
#endif
    
	/* Read the trace and access the cache */
    replayTrace(trace_file);

    /* Free allocated memory */
    freeCache();

    /* Output the hit and miss statistics for the autograder */
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
