#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "mkl.h"

int main(int argc, char *argv[]) {
    double *A, *Amkl;
    int N, i, j, k;
    double alpha, beta;

    int ii = 1;
    if (argc > ii) N = atoi(argv[ii++]);

    A = (double *) mkl_malloc(N * N * sizeof(double), 64);
    Amkl = (double *) mkl_malloc(N * N * sizeof(double), 64);
    if (A == NULL || Amkl == NULL) {
        printf("\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
        mkl_free(A);
        mkl_free(Amkl);
        return 1;
    }

    printf(" Intializing matrix data \n");

    for (int i = 0; i < N;  i++) {
        for (int j = 0; j < i + 1; j++) {
          double num = rand() % 1000 + 1;
          A[i*N+j] = num;
          A[j*N+i] = num;
        }
      }

      for (int i = 0; i < N;  i++) {
        for (int j = 0; j < i + 1; j++) {
          double num = rand() % 1000 + 1;
          Amkl[i*N+j] = num;
          Amkl[j*N+i] = num;
        }
      }


    // for (int i = 0; i < N; i++) {
    //     printf("\n\t");
    //     for (int j = 0; j < N; j++) {
    //         printf("%f ", A[i * N + j]);
    //     }
    // }
    LAPACKE_dpotrf (CblasRowMajor , 'L' , N , Amkl , N );

        //naive reference
        for (i = 0; i < N; i++) {
            for (j = 0; j < i; j++) {
                for (k = 0; k < j; k++) {
                    A[i * N + j] -= A[i * N + k] * A[j * N + k];
                }
                A[i * N + j] /= A[j * N + j];
            }
            // i == j case
            for (k = 0; k < i; k++) {
                A[i * N + i] -= A[i * N + k] * A[i * N + k];
            }
            A[i * N + i] = sqrtf(A[i * N + i]);
        }

        printf("\n After factor matrix data \n");
        for (int i = 0; i < N; i++) {
            printf("\n");
            for (int j = 0; j < i+1; j++) {
                printf("%f ", A[i * N + j]);
            }
        }
        printf("\n");

        printf("After factor MKL matrix data \n");
        for (int i = 0; i < N; i++) {
            printf("\n");
            for (int j = 0; j < i+1; j++) {
                printf("%f ", A[i * N + j]);
            }
        }

        printf("\n");
        mkl_free(A);
        mkl_free(Amkl);

        return 0;
    }

