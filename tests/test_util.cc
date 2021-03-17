#include "topson/topson.h"
#include <assert.h>

topson::Logger::ptr g_logger = TOPSON_LOG_ROOT();

void test_assert() {
    TOPSON_LOG_INFO(g_logger) << topson::BacktraceToString(10);
    TOPSON_ASSERT2(0 == 1, "abcdef xx");
}

int main(int argc, char** argv) {
    test_assert();
    return 0;
}
