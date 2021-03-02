#ifndef __TOPSON_UTIL_H__
#define __TOPSON_UTIL_H__

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>

namespace topson {

pid_t GetThreadId();
uint32_t GetFiberId();

}

#endif
