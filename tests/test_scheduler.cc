#include "topson/topson.h"

static topson::Logger::ptr g_logger = TOPSON_LOG_ROOT();

void test_fiber() {
    static int s_count = 5;
    TOPSON_LOG_INFO(g_logger) << "test in fiber s_count=" << s_count;

    sleep(1);
    if(--s_count >= 0) {
        topson::Scheduler::GetThis()->schedule(&test_fiber, topson::GetThreadId());
    }
}

int main(int argc, char** argv) {
    TOPSON_LOG_INFO(g_logger) << "main";
    topson::Scheduler sc(3, false, "test");
    sc.start();
    sleep(2);
    TOPSON_LOG_INFO(g_logger) << "schedule";
    sc.schedule(&test_fiber);
    sc.stop();
    TOPSON_LOG_INFO(g_logger) << "over";
    return 0;
}
