#include <iostream>
#include <vector>
#include <algorithm>

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

#define N (1024)

using namespace std;

int main(int argc, char *argv[]) {
    vector<float> a(N);
    vector<float> b(N);
    vector<float> c(N);
        printf("Likwid Test ..\n");
    srand(42);
        LIKWID_MARKER_INIT;
        LIKWID_MARKER_THREADINIT;
        LIKWID_MARKER_REGISTER("Compute");

    for (int i = 0; i < N; i++) {
        a[i] = rand();
        b[i] = rand();
    }

        LIKWID_MARKER_START("Compute");
        for (int i = 0; i < N; ++i) {
        c[i] = a[i] + b[i];
    }
        LIKWID_MARKER_STOP("Compute");
        LIKWID_MARKER_CLOSE;
}

