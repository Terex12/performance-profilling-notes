#ifdef PAPI_PERFMON
#include <papi.h>
#endif

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

#define N 4
#define aCO 8
#define bCO 1
#define aOH 56
#define bOH 14
#define aOW 14
#define bOW 4
#define CI 64
#define KH 3
#define KW 3
#define aVH 1
#define bVH 4
#define aVW 4
#define bVW 14
#define aVC 16
#define bVC 128

#ifdef A
static float i[N][aOH][aOW][CI][aVH+KH-1][aVW+KH-1], o[N][aCO*aVC][aOH*aVH][aOW*aVW], k[aCO][CI][KH][KW][aVC];
#endif

#ifdef B
static float i[N][bOH][bOW][CI][bVH+KH-1][bVW+KH-1], o[N][bCO*bVC][bOH*bVH][bOW*bVW], k[bCO][CI][KH][KW][bVC];
#endif

#ifdef C
//Version B sizes in Version A loop order
static float i[N][bOH][bOW][CI][bVH+KH-1][bVW+KH-1], o[N][bCO*bVC][bOH*bVH][bOW*bVW], k[bCO][CI][KH][KW][bVC];
#endif

#ifdef D
//Version A sizes in Version B loop order
static float i[N][aOH][aOW][CI][aVH+KH-1][aVW+KH-1], o[N][aCO*aVC][aOH*aVH][aOW*aVW], k[aCO][CI][KH][KW][aVC];
#endif


double rtclock(void) {
    struct timezone Tzp;
    struct timeval Tp;
    int stat;
    stat = gettimeofday(&Tp, &Tzp);
    if (stat != 0) printf("Error return from gettimeofday: %d", stat);
    return (Tp.tv_sec + Tp.tv_usec * 1.0e-6);
}


#ifdef A
void conv2d(){
  for (int n=0; n<N; n++)
    for (int co=0; co<aCO; co++)
      for (int oh=0; oh<aOH; oh++)
        for (int ow=0; ow<aOW; ow++)
          for (int ci=0; ci<CI; ci++)
            for (int kh=0; kh<KH; kh++)
              for (int kw=0; kw<KW; kw++)
                for (int vh=0; vh<aVH; vh++)
                  for (int vw=0; vw<aVW; vw++)
                    for (int vc=0; vc<aVC; vc++)
                      o[n][co*aVC+vc][oh*aVH+vh][ow*aVW+vw] = i[n][oh][ow][ci][vh+kh][vw+kw] * k[co][ci][kh][kw][vc];
}
#endif

#ifdef B
void conv2d(){
  for (int n=0; n<N; n++)
    for (int co=0; co<bCO; co++)
      for (int oh=0; oh<bOH; oh++)
        for (int ow=0; ow<bOW; ow++)
          for (int ci=0; ci<CI; ci++)
            for (int kh=0; kh<KH; kh++)
              for (int kw=0; kw<KW; kw++)
                for (int vc=0; vc<bVC; vc++)
                  for (int vh=0; vh<bVH; vh++)
                    for (int vw=0; vw<bVW; vw++)
                      o[n][co*bVC+vc][oh*bVH+vh][ow*bVW+vw] = i[n][oh][ow][ci][vh+kh][vw+kw] * k[co][ci][kh][kw][vc];
}
#endif

#ifdef C
//Version B sizes in Version A loop order
void conv2d(){
  for (int n=0; n<N; n++)
    for (int co=0; co<bCO; co++)
      for (int oh=0; oh<bOH; oh++)
        for (int ow=0; ow<bOW; ow++)
          for (int ci=0; ci<CI; ci++)
            for (int kh=0; kh<KH; kh++)
              for (int kw=0; kw<KW; kw++)
                for (int vh=0; vh<bVH; vh++)
                  for (int vw=0; vw<bVW; vw++)
                    for (int vc=0; vc<bVC; vc++)
                      o[n][co*bVC+vc][oh*bVH+vh][ow*bVW+vw] = i[n][oh][ow][ci][vh+kh][vw+kw] * k[co][ci][kh][kw][vc];
}
#endif

#ifdef D
//Version A sizes in Version B loop order
void conv2d(){
  for (int n=0; n<N; n++)
    for (int co=0; co<aCO; co++)
      for (int oh=0; oh<aOH; oh++)
        for (int ow=0; ow<aOW; ow++)
          for (int ci=0; ci<CI; ci++)
            for (int kh=0; kh<KH; kh++)
              for (int kw=0; kw<KW; kw++)
                for (int vc=0; vc<aVC; vc++)
                  for (int vh=0; vh<aVH; vh++)
                    for (int vw=0; vw<aVW; vw++)
                      o[n][co*aVC+vc][oh*aVH+vh][ow*aVW+vw] = i[n][oh][ow][ci][vh+kh][vw+kw] * k[co][ci][kh][kw][vc];
}
#endif
using namespace std;
int main() {
    double t1 = rtclock();

#ifdef PAPI_PERFMON
    int retval = PAPI_library_init(PAPI_VER_CURRENT);

    if ((retval != PAPI_VER_CURRENT && retval > 0) || retval < 0) {
         printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }
    int eventset = PAPI_NULL;
    int nevents = 4;
    if (PAPI_create_eventset(&eventset) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    int event_l1_miss = PAPI_NULL;
    if (PAPI_event_name_to_code("MEM_LOAD_UOPS_RETIRED:L1_MISS", &event_l1_miss) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }
   
    int event_l2_miss = PAPI_NULL;
    if (PAPI_event_name_to_code("MEM_LOAD_UOPS_RETIRED:L2_MISS", &event_l2_miss) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }
   

    int event_l3_miss = PAPI_NULL;
    if (PAPI_event_name_to_code("MEM_LOAD_UOPS_RETIRED:L3_MISS", &event_l3_miss) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    //  int event_l1_hit = PAPI_NULL;
    // if (PAPI_event_name_to_code("MEM_LOAD_UOPS_RETIRED:L1_HIT", &event_l1_hit) != PAPI_OK) {
    //     printf("Exit %d\n", __LINE__);
    //     exit(EXIT_FAILURE);
    // }

    //  int event_l2_hit = PAPI_NULL;
    // if (PAPI_event_name_to_code("MEM_LOAD_UOPS_RETIRED:L2_HIT", &event_l2_hit) != PAPI_OK) {
    //     printf("Exit %d\n", __LINE__);
    //     exit(EXIT_FAILURE);
    // }

    // int event_l3_hit = PAPI_NULL;
    // if (PAPI_event_name_to_code("MEM_LOAD_UOPS_RETIRED:L3_HIT", &event_l3_hit) != PAPI_OK) {
    //     printf("Exit %d\n", __LINE__);
    //     exit(EXIT_FAILURE);
    // }

    int event_singlef_ops = PAPI_NULL;
    if (PAPI_event_name_to_code("PAPI_SP_OPS", &event_singlef_ops) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    /// Add event to eventset
    if (PAPI_add_event(eventset, event_l1_miss) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    if (PAPI_add_event(eventset, event_l2_miss) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    if (PAPI_add_event(eventset, event_l3_miss) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    // if (PAPI_add_event(eventset, event_l1_hit) != PAPI_OK) {
    //     printf("Exit %d\n", __LINE__);
    //     exit(EXIT_FAILURE);
    // }

    // if (PAPI_add_event(eventset, event_l2_hit) != PAPI_OK) {
    //     printf("Exit %d\n", __LINE__);
    //     exit(EXIT_FAILURE);
    // }

    // if (PAPI_add_event(eventset, event_l3_hit) != PAPI_OK) {
    //     printf("Exit %d\n", __LINE__);
    //     exit(EXIT_FAILURE);
    // }

    if (PAPI_add_event(eventset, event_singlef_ops) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }
    long_long papi_vals[nevents];
    if (PAPI_start(eventset) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        printf("error: %d\n", retval);
        exit(EXIT_FAILURE);
    }
#endif

#ifdef LIKWID_PERFMON
    LIKWID_MARKER_INIT;
    LIKWID_MARKER_THREADINIT;
    LIKWID_MARKER_REGISTER("Compute");
    LIKWID_MARKER_START("Compute");
#endif

    /// code execute ///
    conv2d();

#ifdef PAPI_PERFMON
    if (PAPI_stop(eventset, papi_vals) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        printf("error: %d\n", retval);
        exit(EXIT_FAILURE);
    }
    // for (int i = 0; i < nevents; i++) {
    //      printf("PAPI Event %d : %lld\n", i, papi_vals[i]);
    // }
    printf("PAPI L1 miss  : %lld\n",papi_vals[0]);
    printf("PAPI L2 miss  : %lld\n",papi_vals[1]);
    printf("PAPI L3 miss  : %lld\n",papi_vals[2]);
    // printf("PAPI L1 hit  : %lld\n",papi_vals[3]);
    // printf("PAPI L2 hit  : %lld\n",papi_vals[4]);
    // printf("PAPI L3 hit  : %lld\n",papi_vals[5]);
    printf("PAPI SFlops  : %lld\n",papi_vals[4]);

#endif
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_STOP("Compute");
    LIKWID_MARKER_CLOSE;
#endif

    double t2 = rtclock();
    // Timing is use less here
    printf("Time = %.5f      %.2f\n", t2 - t1, o[0][0][0][0]);
    return 0;
}
