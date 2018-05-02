/* 
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
		int r1,r2;
		switch(M){
				case 32:{
								for(int i = 0; i < M; i+=8){
										for(int j = 0; j < N; j+=8){
												for(int k = j; k < j+8&& k < N; ++k){
														for(int l = i; l < i+8&& l < M; ++l){
																if(k!=l)B[l][k] = A[k][l];
																else {
																		r1 = k;
																		r2 = A[k][k];
																}	
														}
														if(i==j){
																B[r1][r1] = r2;
														}
												}
										}
								}
								break;
						}
				case 64:{
								for(int i = 0; i < N; i+=8){
										for(int j = 0; j < M; j+=8){
												for(int k = i; k < i+8; ++k){
														for(int l = j; l < j+8; ++l){
															B[l][k] = A[k][l];
														}
												}
										
										}
								}
								break;
						}
				case 61:{
								for(int i = 0; i < M; i+=16){
										for(int j = 0; j < N; j+=4){
												for(int k = j; k < j+4&& k < N; ++k){
														for(int l = i; l < i+16&& l < M; ++l){
																B[l][k] = A[k][l];	
														}
												}
										}
								}
								break;
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

