#include <iostream>
#include <vector>
#include <algorithm>
#include <papi.h>

#define N (1024)

using namespace std;

int main(int argc, char *argv[]) {
    vector<float> a(N);
    vector<float> b(N);
    vector<float> c(N);
	printf("PAPI Test ..\n");
    srand(42);

    for (int i = 0; i < N; i++) {
        a[i] = rand();
        b[i] = rand();
    }

    int retval = PAPI_library_init(PAPI_VER_CURRENT);
    if ((retval != PAPI_VER_CURRENT && retval > 0) || retval < 0) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }


    int eventset = PAPI_NULL;
    if (PAPI_create_eventset(&eventset) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    /// Check event availibility
    int event_l1_miss = PAPI_NULL;
    if (PAPI_event_name_to_code("MEM_LOAD_UOPS_RETIRED:L1_MISS", &event_l1_miss) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    int event_l3_miss = PAPI_NULL;
    if (PAPI_event_name_to_code("MEM_LOAD_UOPS_RETIRED:L3_MISS", &event_l3_miss) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    int event_singlef_ops = PAPI_NULL;
    if (PAPI_event_name_to_code("PAPI_SP_OPS", &event_singlef_ops) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }


    /// Add event to eventset
    if (PAPI_add_event(eventset, event_l1_miss) != PAPI_OK) {
        exit(EXIT_FAILURE);
    }

    if (PAPI_add_event(eventset, event_l3_miss) != PAPI_OK) {
        exit(EXIT_FAILURE);
    }

    if (PAPI_add_event(eventset, event_singlef_ops) != PAPI_OK) {
        exit(EXIT_FAILURE);
    }


    long_long papi_vals[3];
    if (PAPI_start(eventset) != PAPI_OK) {
        printf("Exit %d\n", __LINE__);
        printf("error: %d\n", retval);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; ++i) {
        c[i] = a[i] + b[i];
    }

    if (PAPI_stop(eventset, papi_vals) != PAPI_OK) {
        printf("error: %d\n", retval);
        exit(EXIT_FAILURE);
    }
    
    printf("PAPI L1 miss: %lld\nPAPI L3 miss: %lld\nPAPI Single Precision OPS: %lld\n", papi_vals[0], papi_vals[1], papi_vals[2]);

    return 0;
}
