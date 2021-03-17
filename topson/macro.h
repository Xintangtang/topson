#ifndef __TOPSON_MARCO_H__
#define __TOPSON_MARCO_H__

#include <string.h>
#include <assert.h>
#include "util.h"

#define TOPSON_ASSERT(x) \
    if(!(x)) { \
        TOPSON_LOG_ERROR(TOPSON_LOG_ROOT()) << "ASSERTION: " << #x \
            << "\nbacktrace:\n" \
            << topson::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

#define TOPSON_ASSERT2(x, w) \
    if(!(x)) { \
        TOPSON_LOG_ERROR(TOPSON_LOG_ROOT()) << "ASSERTION: " << #x \
            << "\n" << w \
            << "\nbacktrace:\n" \
            << topson::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

#endif
