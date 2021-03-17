#include "topson/topson.h"
#include <unistd.h>

topson::Logger::ptr g_logger = TOPSON_LOG_ROOT();

int count = 0;
//topson::RWMutex s_mutex;
topson::Mutex s_mutex;

void fun1() {
    TOPSON_LOG_INFO(g_logger) << "name: " << topson::Thread::GetName()
                              << " this.name: " << topson::Thread::GetThis()->getName()
                              << " id: " << topson::GetThreadId()
                              << " this.id: " << topson::Thread::GetThis()->getId();

    for(int i = 0; i < 100000; ++i) {
        //topson::RWMutex::WriteLock lock(s_mutex);
        topson::Mutex::Lock lock(s_mutex);
        ++count;
    }
}

void fun2() {
    while(true) {
        TOPSON_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    }
}

void fun3() {
    while(true) {
        TOPSON_LOG_INFO(g_logger) << "========================================";
    }
}

int main(int argc, char** argv) {
    TOPSON_LOG_INFO(g_logger) << "thread test begin";
    YAML::Node root = YAML::LoadFile("bin/conf/log.yml");
    topson::Config::LoadFromYaml(root);

    std::vector<topson::Thread::ptr> thrs;
    for(int i = 0; i < 2; ++i) {
        topson::Thread::ptr thr(new topson::Thread(&fun2, "name_" + std::to_string(i * 2)));
        topson::Thread::ptr thr2(new topson::Thread(&fun3, "name_" + std::to_string(i * 2 + 1)));
        thrs.push_back(thr);
        thrs.push_back(thr2);
    }

    for(size_t i = 0; i < thrs.size(); ++i) {
        thrs[i]->join();
    }
    TOPSON_LOG_INFO(g_logger) << "thread test end";
    TOPSON_LOG_INFO(g_logger) << "count=" << count;

    return 0;
}
