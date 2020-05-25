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


#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define N 2048*2048

static float arr1[N], arr2[N];

double rtclock(void) {
    struct timezone Tzp;
    struct timeval Tp;
    int stat;
    stat = gettimeofday(&Tp, &Tzp);
    if (stat != 0) printf("Error return from gettimeofday: %d", stat);
    return (Tp.tv_sec + Tp.tv_usec * 1.0e-6);
}


using namespace std;
int main() {
  for (int n=0; n<N; n++)
      arr1[n] = 1e-4*n;

  double t1 = rtclock();

    LIKWID_MARKER_INIT;
#pragma omp parallel
{
  LIKWID_MARKER_THREADINIT;
}
    LIKWID_MARKER_REGISTER("Compute");
    

    /// code execute ///
    #pragma omp parallel
{
    LIKWID_MARKER_START("Compute");

    #pragma omp for
    for (int n=0; n<N; n++)
        arr2[n] = arr1[n];

    LIKWID_MARKER_STOP("Compute");
}

    
    LIKWID_MARKER_CLOSE;


    double t2 = rtclock();
    // Timing is use less here
    printf("Time = %.5f, %.2f\n", t2 - t1, arr2[N-1]);
    return 0;
}

