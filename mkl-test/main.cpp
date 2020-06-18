#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"
#include "likwid.h"
int main()
{
    float *A, *B, *C;
    int m, n, k, i, j;
    float alpha, beta;

    printf ("\n This example computes real matrix C=alpha*A*B+beta*C using \n"
            " Intel(R) MKL function dgemm, where A, B, and  C are matrices and \n"
            " alpha and beta are float precision scalars\n\n");

    m = N_M;
	k = N_K;
	n = N_N;
    printf (" Initializing data for matrix multiplication C=A*B for matrix \n"
            " A(%ix%i) and matrix B(%ix%i)\n\n", m, k, k, n);
    alpha = 1.0; beta = 0.0;

    printf (" Allocating memory for matrices aligned on 64-byte boundary for better \n"
            " performance \n\n");
    A = (float *)mkl_malloc( m*k*sizeof( float ), 32 );
    B = (float *)mkl_malloc( k*n*sizeof( float ), 32 );
    C = (float *)mkl_malloc( m*n*sizeof( float ), 32 );
    if (A == NULL || B == NULL || C == NULL) {
      printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
      mkl_free(A);
      mkl_free(B);
      mkl_free(C);
      return 1;
    }

    printf (" Intializing matrix data \n\n");
    for (i = 0; i < (m*k); i++) {
        A[i] = (float)(i+1);
    }

    for (i = 0; i < (k*n); i++) {
        B[i] = (float)(-i-1);
    }

    for (i = 0; i < (m*n); i++) {
        C[i] = 0.0;
    }
	mkl_set_num_threads_local(4);
	printf("num of thread : %d\n", mkl_get_max_threads());

LIKWID_MARKER_INIT;
#pragma omp parallel
{
	LIKWID_MARKER_THREADINIT;
}		

#pragma omp parallel
{
	LIKWID_MARKER_START("Compute");
}
    printf (" Computing matrix product using Intel(R) MKL dgemm function via CBLAS interface \n\n");
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                m, n, k, alpha, A, k, B, n, beta, C, n);

#pragma omp parallel
{    
	LIKWID_MARKER_STOP("Compute");
}
LIKWID_MARKER_CLOSE;

	printf ("\n Computations completed.\n\n");
    mkl_free(A);
    mkl_free(B);
    mkl_free(C);
	
	return 0;
}
