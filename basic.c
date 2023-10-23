#include "basic.h"

double get_fps(struct timespec start, struct timespec stop) {
    unsigned long time_taken; // number of nanoseconds
    clock_gettime( CLOCK_REALTIME, &stop);
    time_taken = (stop.tv_sec - start.tv_sec) * BILLION;
    time_taken += stop.tv_nsec - start.tv_nsec;
    printf("Start of frame time:    %lld.%.9ld\n", start.tv_sec, start.tv_nsec);
    printf("End of frame time:      %lld.%.9ld\n", stop.tv_sec, stop.tv_nsec);
    printf("Time taken:             .%.9lu\n", time_taken);
    double framerate = 1000000000.0/time_taken;
    return framerate;
}
