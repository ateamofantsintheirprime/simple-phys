#ifndef BASIC_H
#define BASIC_H

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define MAX_FPS 300
#define BILLION 1000000000L;

#define THREAD_COUNT 4

#define AGENT_RADIUS 3
#define MAX_AGENT_COUNT 2000

#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>

double get_fps(struct timespec start, struct timespec stop);

#endif
