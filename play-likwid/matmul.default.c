#ifdef LIKWID_PERFMON                                                                                                                                                                                                                     
#include <likwid.h>
#else
#define LIKWID_MARKER_INIT
#define LIKWID_MARKER_THREADINIT
#define LIKWID_MARKER_SWITCH
#define LIKWID_MARKER_REGISTER(regionTag)
#define LIKWID_MARKER_START(regionTag)
#define LIKWID_MARKER_STOP(regionTag)
#define LIKWID_MARKER_CLOSE
#define LIKWID_MARKER_GET(regionTag, nevents, events, time, count)
#endif


#include <omp.h>
#include <math.h>
#define ceild(n,d)  (((n)<0) ? -((-(n))/(d)) : ((n)+(d)-1)/(d))
#define floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>

#define M 1000
#define N 1100
#define K 1200
#define alpha 1.2
#define beta 1

#pragma declarations
float (*A)[K];
float (*B)[N];
float (*C)[N];
#pragma enddeclarations

#ifdef PERFCTR
#include "papiStdEventDefs.h"
#include <papi.h>
#include "papi_defs.h"
#endif

#ifdef TIME
#define IF_TIME(foo) foo;
#else
#define IF_TIME(foo)
#endif

void init_array()
{
    for (int i = 0; i < M; i++){
        for (int j = 0; j < K; j++){
            A[i][j] = i;
        }
    }
    for (int i = 0; i < K; i++){
        for (int j = 0; j < N; j++){
            B[i][j] = M*K + i;
        }
    } 
}


void print_array()
{
    int i, j;

    for (i=0; i<M; i++) {
        for (j=0; j<N; j++) {
            fprintf(stderr, "%lf ", C[i][j]);
            if (j%80 == 79) fprintf(stderr, "\n");
        }
        fprintf(stderr, "\n");
    }
}

//stub to print address later
void print_array_elem_address(float *elem, int r)
{
    //remove me// printf("%d %p\n", r, elem);
}

double rtclock()
{
    struct timezone Tzp;
    struct timeval Tp;
    int stat;
    stat = gettimeofday (&Tp, &Tzp);
    if (stat != 0) printf("Error return from gettimeofday: %d",stat);
    return(Tp.tv_sec + Tp.tv_usec*1.0e-6);
}
double t_start, t_end;

int main()
{
    int i, j, k;
    int tt;

    A = (float (*)[K])aligned_alloc(64,M * K * sizeof(A[0][0]));
    B = (float (*)[N])aligned_alloc(64,N * K * sizeof(B[0][0]));
    C = (float (*)[N])aligned_alloc(64,M * N * sizeof(C[0][0]));

    init_array();

LIKWID_MARKER_INIT;
LIKWID_MARKER_THREADINIT;
LIKWID_MARKER_REGISTER("Compute");



#ifdef PERFCTR
    PERF_INIT; 
#endif

    IF_TIME(t_start = rtclock());
//for (tt = 0; tt < 100; tt++){
  int t1, t2, t3, t4, t5, t6;
 int lb, ub, lbp, ubp, lb2, ub2;
 register int lbv, ubv;
lbp=0;
ubp=31;
#pragma omp parallel for private(lbv,ubv,t2,t3,t4,t5,t6)

LIKWID_MARKER_START("Compute");

for (t1=lbp;t1<=ubp;t1++) {
  for (t2=0;t2<=34;t2++) {
    for (t3=0;t3<=37;t3++) {
      for (t4=32*t1;t4<=(min(999,32*t1+31))-7;t4+=8) {
        for (t5=32*t3;t5<=(min(1199,32*t3+31))-7;t5+=8) {
          lbv=32*t2;
          ubv=min(1099,32*t2+31);
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            C[t4][t6] += ((1.2 * A[t4][t5]) * B[t5][t6]);;
            C[(t4+1)][t6] += ((1.2 * A[(t4+1)][t5]) * B[t5][t6]);;
            C[(t4+2)][t6] += ((1.2 * A[(t4+2)][t5]) * B[t5][t6]);;
            C[(t4+3)][t6] += ((1.2 * A[(t4+3)][t5]) * B[t5][t6]);;
            C[(t4+4)][t6] += ((1.2 * A[(t4+4)][t5]) * B[t5][t6]);;
            C[(t4+5)][t6] += ((1.2 * A[(t4+5)][t5]) * B[t5][t6]);;
            C[(t4+6)][t6] += ((1.2 * A[(t4+6)][t5]) * B[t5][t6]);;
            C[(t4+7)][t6] += ((1.2 * A[(t4+7)][t5]) * B[t5][t6]);;
            C[t4][t6] += ((1.2 * A[t4][(t5+1)]) * B[(t5+1)][t6]);;
            C[(t4+1)][t6] += ((1.2 * A[(t4+1)][(t5+1)]) * B[(t5+1)][t6]);;
            C[(t4+2)][t6] += ((1.2 * A[(t4+2)][(t5+1)]) * B[(t5+1)][t6]);;
            C[(t4+3)][t6] += ((1.2 * A[(t4+3)][(t5+1)]) * B[(t5+1)][t6]);;
            C[(t4+4)][t6] += ((1.2 * A[(t4+4)][(t5+1)]) * B[(t5+1)][t6]);;
            C[(t4+5)][t6] += ((1.2 * A[(t4+5)][(t5+1)]) * B[(t5+1)][t6]);;
            C[(t4+6)][t6] += ((1.2 * A[(t4+6)][(t5+1)]) * B[(t5+1)][t6]);;
            C[(t4+7)][t6] += ((1.2 * A[(t4+7)][(t5+1)]) * B[(t5+1)][t6]);;
            C[t4][t6] += ((1.2 * A[t4][(t5+2)]) * B[(t5+2)][t6]);;
            C[(t4+1)][t6] += ((1.2 * A[(t4+1)][(t5+2)]) * B[(t5+2)][t6]);;
            C[(t4+2)][t6] += ((1.2 * A[(t4+2)][(t5+2)]) * B[(t5+2)][t6]);;
            C[(t4+3)][t6] += ((1.2 * A[(t4+3)][(t5+2)]) * B[(t5+2)][t6]);;
            C[(t4+4)][t6] += ((1.2 * A[(t4+4)][(t5+2)]) * B[(t5+2)][t6]);;
            C[(t4+5)][t6] += ((1.2 * A[(t4+5)][(t5+2)]) * B[(t5+2)][t6]);;
            C[(t4+6)][t6] += ((1.2 * A[(t4+6)][(t5+2)]) * B[(t5+2)][t6]);;
            C[(t4+7)][t6] += ((1.2 * A[(t4+7)][(t5+2)]) * B[(t5+2)][t6]);;
            C[t4][t6] += ((1.2 * A[t4][(t5+3)]) * B[(t5+3)][t6]);;
            C[(t4+1)][t6] += ((1.2 * A[(t4+1)][(t5+3)]) * B[(t5+3)][t6]);;
            C[(t4+2)][t6] += ((1.2 * A[(t4+2)][(t5+3)]) * B[(t5+3)][t6]);;
            C[(t4+3)][t6] += ((1.2 * A[(t4+3)][(t5+3)]) * B[(t5+3)][t6]);;
            C[(t4+4)][t6] += ((1.2 * A[(t4+4)][(t5+3)]) * B[(t5+3)][t6]);;
            C[(t4+5)][t6] += ((1.2 * A[(t4+5)][(t5+3)]) * B[(t5+3)][t6]);;
            C[(t4+6)][t6] += ((1.2 * A[(t4+6)][(t5+3)]) * B[(t5+3)][t6]);;
            C[(t4+7)][t6] += ((1.2 * A[(t4+7)][(t5+3)]) * B[(t5+3)][t6]);;
            C[t4][t6] += ((1.2 * A[t4][(t5+4)]) * B[(t5+4)][t6]);;
            C[(t4+1)][t6] += ((1.2 * A[(t4+1)][(t5+4)]) * B[(t5+4)][t6]);;
            C[(t4+2)][t6] += ((1.2 * A[(t4+2)][(t5+4)]) * B[(t5+4)][t6]);;
            C[(t4+3)][t6] += ((1.2 * A[(t4+3)][(t5+4)]) * B[(t5+4)][t6]);;
            C[(t4+4)][t6] += ((1.2 * A[(t4+4)][(t5+4)]) * B[(t5+4)][t6]);;
            C[(t4+5)][t6] += ((1.2 * A[(t4+5)][(t5+4)]) * B[(t5+4)][t6]);;
            C[(t4+6)][t6] += ((1.2 * A[(t4+6)][(t5+4)]) * B[(t5+4)][t6]);;
            C[(t4+7)][t6] += ((1.2 * A[(t4+7)][(t5+4)]) * B[(t5+4)][t6]);;
            C[t4][t6] += ((1.2 * A[t4][(t5+5)]) * B[(t5+5)][t6]);;
            C[(t4+1)][t6] += ((1.2 * A[(t4+1)][(t5+5)]) * B[(t5+5)][t6]);;
            C[(t4+2)][t6] += ((1.2 * A[(t4+2)][(t5+5)]) * B[(t5+5)][t6]);;
            C[(t4+3)][t6] += ((1.2 * A[(t4+3)][(t5+5)]) * B[(t5+5)][t6]);;
            C[(t4+4)][t6] += ((1.2 * A[(t4+4)][(t5+5)]) * B[(t5+5)][t6]);;
            C[(t4+5)][t6] += ((1.2 * A[(t4+5)][(t5+5)]) * B[(t5+5)][t6]);;
            C[(t4+6)][t6] += ((1.2 * A[(t4+6)][(t5+5)]) * B[(t5+5)][t6]);;
            C[(t4+7)][t6] += ((1.2 * A[(t4+7)][(t5+5)]) * B[(t5+5)][t6]);;
            C[t4][t6] += ((1.2 * A[t4][(t5+6)]) * B[(t5+6)][t6]);;
            C[(t4+1)][t6] += ((1.2 * A[(t4+1)][(t5+6)]) * B[(t5+6)][t6]);;
            C[(t4+2)][t6] += ((1.2 * A[(t4+2)][(t5+6)]) * B[(t5+6)][t6]);;
            C[(t4+3)][t6] += ((1.2 * A[(t4+3)][(t5+6)]) * B[(t5+6)][t6]);;
            C[(t4+4)][t6] += ((1.2 * A[(t4+4)][(t5+6)]) * B[(t5+6)][t6]);;
            C[(t4+5)][t6] += ((1.2 * A[(t4+5)][(t5+6)]) * B[(t5+6)][t6]);;
            C[(t4+6)][t6] += ((1.2 * A[(t4+6)][(t5+6)]) * B[(t5+6)][t6]);;
            C[(t4+7)][t6] += ((1.2 * A[(t4+7)][(t5+6)]) * B[(t5+6)][t6]);;
            C[t4][t6] += ((1.2 * A[t4][(t5+7)]) * B[(t5+7)][t6]);;
            C[(t4+1)][t6] += ((1.2 * A[(t4+1)][(t5+7)]) * B[(t5+7)][t6]);;
            C[(t4+2)][t6] += ((1.2 * A[(t4+2)][(t5+7)]) * B[(t5+7)][t6]);;
            C[(t4+3)][t6] += ((1.2 * A[(t4+3)][(t5+7)]) * B[(t5+7)][t6]);;
            C[(t4+4)][t6] += ((1.2 * A[(t4+4)][(t5+7)]) * B[(t5+7)][t6]);;
            C[(t4+5)][t6] += ((1.2 * A[(t4+5)][(t5+7)]) * B[(t5+7)][t6]);;
            C[(t4+6)][t6] += ((1.2 * A[(t4+6)][(t5+7)]) * B[(t5+7)][t6]);;
            C[(t4+7)][t6] += ((1.2 * A[(t4+7)][(t5+7)]) * B[(t5+7)][t6]);;
          }
        }
        for (;t5<=min(1199,32*t3+31);t5++) {
          lbv=32*t2;
          ubv=min(1099,32*t2+31);
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            C[t4][t6] += ((1.2 * A[t4][t5]) * B[t5][t6]);;
            C[(t4+1)][t6] += ((1.2 * A[(t4+1)][t5]) * B[t5][t6]);;
            C[(t4+2)][t6] += ((1.2 * A[(t4+2)][t5]) * B[t5][t6]);;
            C[(t4+3)][t6] += ((1.2 * A[(t4+3)][t5]) * B[t5][t6]);;
            C[(t4+4)][t6] += ((1.2 * A[(t4+4)][t5]) * B[t5][t6]);;
            C[(t4+5)][t6] += ((1.2 * A[(t4+5)][t5]) * B[t5][t6]);;
            C[(t4+6)][t6] += ((1.2 * A[(t4+6)][t5]) * B[t5][t6]);;
            C[(t4+7)][t6] += ((1.2 * A[(t4+7)][t5]) * B[t5][t6]);;
          }
        }
      }
      for (;t4<=min(999,32*t1+31);t4++) {
        for (t5=32*t3;t5<=min(1199,32*t3+31);t5++) {
          lbv=32*t2;
          ubv=min(1099,32*t2+31);
#pragma ivdep
#pragma vector always
          for (t6=lbv;t6<=ubv;t6++) {
            C[t4][t6] += ((1.2 * A[t4][t5]) * B[t5][t6]);;
          }
        }
      }
    }
  }
}
//}

LIKWID_MARKER_STOP("Compute");
LIKWID_MARKER_CLOSE;
    IF_TIME(t_end = rtclock());
    IF_TIME(fprintf(stdout, "%0.6lf", t_end - t_start));

#ifdef PERFCTR
    PERF_EXIT; 
#endif
  
  return 0;
}


