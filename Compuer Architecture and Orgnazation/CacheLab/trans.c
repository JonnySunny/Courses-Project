/* 
 * Zhongyi Sun
 * Sunx0725
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int i,j,tmp = 0 ,index = 0 ;
    int block_row, block_col, block_size;
    //first case is 32*32 matrix
    if(M == 32 && N == 32){
        block_size = 8; 
        // since for a cache which can store 8 ints with a cold miss
       // that's more effiecient than one line by one line when transpose matrix
        for(block_row = 0;block_row < N ;block_row += block_size){
            for(block_col =0 ;block_col < M; block_col+= block_size){
                for(i=block_row ; i< block_row + block_size;i++){
                    for(j=block_col;j< block_col + block_size;j++){
        //notice that line there may exist a conflict because they can by relect the same line when dealing with the diagonal element. 
                        if(i!=j){
                            B[j][i] = A[i][j];
                        }else{
        //thus , when occurs diagoal element, we can store them frist and deal with it after the loop finished.
                            tmp = A[i][j];         
                            index = i;
                        }
                    }
                    if(block_col == block_row){
                        B[index][index] = tmp;
                    }
                }
            }
        }
    }
    //64 * 64 matrix
    else if (M == 64 && N == 64){
		//after tried differnet size of block, the performence is not as good as my expection
		//so, I decided to seperately to stroe the element for decreading the miss times and using 8*8 block at the same time.
      int v1,v2,v3,v4,v5,v6,v7,v8,counter;
       //using 8*8 matrix to seperate the larger matrix
        for(block_row = 0;block_row < N ;block_row += 8){
            for(block_col =0 ;block_col < M; block_col+= 8){
                for(counter = 0; counter < 8; counter ++){
					v1 = A[block_col + counter][block_row];
					v2 = A[block_col + counter][block_row+1];
					v3 = A[block_col + counter][block_row+2];
					v4 = A[block_col + counter][block_row+3];
				if(0 == counter){
					v5 = A[block_col + counter][block_row+4];
					v6 = A[block_col + counter][block_row+5];
					v7 = A[block_col + counter][block_row+6];
					v8 = A[block_col + counter][block_row+7];
					}
				B[block_row][block_col + counter] = v1;
				B[block_row][block_col + counter+64] = v2;
				B[block_row][block_col + counter+128] = v3;
				B[block_row][block_col + counter+192] = v4;
			}
			   for(counter = 7; counter > 0; counter --){
					v1 = A[block_col + counter][block_row+4];
					v2 = A[block_col + counter][block_row+5];
					v3 = A[block_col + counter][block_row+6];
					v4 = A[block_col + counter][block_row+7];
					B[block_row+4][block_col + counter] = v1;
					B[block_row+4][block_col + counter+64] = v2;
					B[block_row+4][block_col + counter+128] = v3;
					B[block_row+4][block_col + counter+192] = v4;
			}
					B[block_row+4][block_col + counter] = v5;
					B[block_row+4][block_col + counter+64] = v6;
					B[block_row+4][block_col + counter+128] = v7;
					B[block_row+4][block_col + counter+192] = v8;
           }
        }
    }
    // 61 * 67 matrix 
    else if (M == 61 && N == 67){
        //block_size = 16 * 16; 
        //using a 16*16 matrix to seperate the larger matrix
        for(block_col = 0;block_col < M ;block_col += 16){
            for(block_row = 0 ;block_row < N; block_row += 16){
                for(i=block_row ; (i< block_row + 16) && (i<N);i++){
                    for(j=block_col;(j< block_col + 16) && (j < M);j++){
        //notice that line there may exist a conflict because they can by relect the same line when dealing with the diagonal element. 
                        if(i != j ){
                            B[j][i] = A[i][j];
                        }else{
        //thus , when occurs diagoal element, we can store them frist and deal with it after the loop finished.
                            tmp = A[i][j];         
                            index = i;	
                        }
                    }
                    if(block_col == block_row){
}			 B[index][index] = tmp;
                }
            }
        }
    }




}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

