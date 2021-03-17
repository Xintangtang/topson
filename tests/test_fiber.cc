#include "topson/topson.h"

topson::Logger::ptr g_logger = TOPSON_LOG_ROOT();

void run_in_fiber() {
    TOPSON_LOG_INFO(g_logger) << "run_in_fiber begin";
    topson::Fiber::YieldToHold();
    TOPSON_LOG_INFO(g_logger) << "run_in_fiber end";
    topson::Fiber::YieldToHold();
}

void test_fiber() {
    TOPSON_LOG_INFO(g_logger) << "main begin -1";
    {
        topson::Fiber::GetThis();
        TOPSON_LOG_INFO(g_logger) << "main begin";
        topson::Fiber::ptr fiber(new topson::Fiber(run_in_fiber));
        fiber->swapIn();
        TOPSON_LOG_INFO(g_logger) << "main after swapIn";
        fiber->swapIn();
        TOPSON_LOG_INFO(g_logger) << "main after end";
        fiber->swapIn();
    }
    TOPSON_LOG_INFO(g_logger) << "main after end2";
}

int main(int argc, char** argv) {
    topson::Thread::SetName("main");

    std::vector<topson::Thread::ptr> thrs;
    for(int i = 0; i < 3; ++i) {
        thrs.push_back(topson::Thread::ptr(
                    new topson::Thread(&test_fiber, "name_" + std::to_string(i))));
    }
    for(auto i : thrs) {
        i->join();
    }
    return 0;
}
