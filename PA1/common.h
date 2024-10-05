/**
 * Some common headers and definitions helpful for your impl:
 * 1. `sched_attr` definition for SYS_sched_getattr and SYS_sched_setattr
 * 2. `get_sched_name` to get scheduling algo name based on macro defn
 * 3. `HANDLE_ERROR` macro helpful to handler error
 * 
 * You SHALL NOT change this file
 */

#pragma once // avoid redefinition

#define _GNU_SOURCE // for glibc
#include <sched.h>  // for scheduling
#include <time.h>   // for timing

#define MAX_PROMPT_LEN 256 // maximum characters allowed for each user type in
#define MAX_NEW_TOKENS 256 // maximum tokens allowed for each forward loop

// manually define as Linux don't in the header though syscall is supported
// @see https://man7.org/linux/man-pages/man7/sched.7.html
struct sched_attr {
	unsigned int size; // size of this struct
	unsigned int sched_policy; // scheduling policy, see below
	unsigned long long sched_flags; // internal use only

	/* SCHED_NORMAL, SCHED_BATCH */
	signed int sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	unsigned int sched_priority;

	/* SCHED_DEADLINE (nsec) */
	unsigned long long sched_runtime;
	unsigned long long sched_deadline;
	unsigned long long sched_period;

    /* Utilization hints */
    unsigned int sched_util_min;
    unsigned int sched_util_max;
};

/**
Get Schduler Name by revert the original macro definition:
#define SCHED_OTHER		0
#define SCHED_FIFO		1
#define SCHED_RR		2
#define SCHED_BATCH		3
#define SCHED_ISO		4
#define SCHED_IDLE		5
#define SCHED_DEADLINE  6
use it like get_sched_name(attr.sched_policy)
@note you don't need to free the const char* returned
 */
const char* get_sched_name(int policy) {
    switch (policy) {
        case SCHED_OTHER:     return "SCHED_OTHER";
        case SCHED_FIFO:      return "SCHED_FIFO";
        case SCHED_RR:        return "SCHED_RR";
        case SCHED_BATCH:     return "SCHED_BATCH";
        case SCHED_ISO:       return "SCHED_ISO";
        case SCHED_IDLE:      return "SCHED_IDLE";
        case SCHED_DEADLINE:  return "SCHED_DEADLINE";
        default:              return "Unknown scheduling policy";
    }
}

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define FILELINE __FILE__ ":" TOSTRING(__LINE__)

// a helper macro to locate error and reason, add to anywhere might raise
#define HANDLE_ERROR() do { \
    perror(FILELINE);       \
    exit(EXIT_FAILURE);     \
} while(0)

// ----------------------------------------------------------------------------
// utilities: time

long time_in_ms() {
    // return time in milliseconds, for benchmarking the model speed
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return time.tv_sec * 1000 + time.tv_nsec / 1000000;
}
