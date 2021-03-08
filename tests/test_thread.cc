#include "topson/topson.h"
#include <unistd.h>

topson::Logger::ptr g_logger = TOPSON_LOG_ROOT();

void fun1() {
    TOPSON_LOG_INFO(g_logger) << "name: " << topson::Thread::GetName()
                              << " this.name: " << topson::Thread::GetThis()->getName()
                              << " id: " << topson::GetThreadId()
                              << " this.id: " << topson::Thread::GetThis()->getId();
    sleep(20);
}

void func2() {
}

int main(int argc, char** argv) {
    TOPSON_LOG_INFO(g_logger) << "thread test begin";
    std::vector<topson::Thread::ptr> thrs;
    for(int i = 0; i < 5; ++i) {
        topson::Thread::ptr thr(new topson::Thread(&fun1, "name_" + std::to_string(i)));
        thrs.push_back(thr);
    }

    for(int i = 0; i< 5; ++i) {
        thrs[i]->join();
    }
    TOPSON_LOG_INFO(g_logger) << "thread test end";
    return 0;
}
