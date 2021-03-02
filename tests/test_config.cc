#include "topson/config.h"
#include "topson/log.h"
#include "topson/util.h"

topson::ConfigVar<int>::ptr g_int_value_config = 
    topson::Config::Lookup("system.port", (int)8080, "system port");

topson::ConfigVar<float>::ptr g_float_value_config =
    topson::Config::Lookup("system.value", (float)10.2f, "system value");

void print_yaml(const YAML::Node& node, int level) {
    if(node.IsScalar()) {
        TOPSON_LOG_INFO(TOPSON_LOG_ROOT()) << std::string(level * 4, ' ')
            << node.Scalar() << " - "  << node.Type() << " - " << level;
    } else if(node.IsNull()) {
        TOPSON_LOG_INFO(TOPSON_LOG_ROOT()) << std::string(level * 4, ' ')
            << "NULL - " << node.Type() << " - " << level;
    } else if(node.IsMap()) {
        for(auto it = node.begin();
                it != node.end(); ++it) {
            TOPSON_LOG_INFO(TOPSON_LOG_ROOT()) << std::string(level * 4, ' ')
                << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second, level + 1);
        }
    } else if(node.IsSequence()) {
        for(size_t i = 0; i < node.size(); ++i) {
            TOPSON_LOG_INFO(TOPSON_LOG_ROOT()) << std::string(level * 4, ' ')
                << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i], level + 1);
        }
    }
}

void test_yaml() {
    YAML::Node root = YAML::LoadFile("/home/xin/github/topson/bin/conf/log.yml");
    print_yaml(root, 0);

    TOPSON_LOG_INFO(TOPSON_LOG_ROOT()) << root.Scalar();
}

void test_config() {
    TOPSON_LOG_INFO(TOPSON_LOG_ROOT()) << "before" << g_int_value_config->getValue();
    TOPSON_LOG_INFO(TOPSON_LOG_ROOT()) << "before" << g_float_value_config->getValue();

    YAML::Node root = YAML::LoadFile("/home/xin/github/topson/bin/conf/log.yml");
    topson::Config::LoadFromYaml(root);

    TOPSON_LOG_INFO(TOPSON_LOG_ROOT()) << "after" << g_int_value_config->getValue();
    TOPSON_LOG_INFO(TOPSON_LOG_ROOT()) << "after" << g_float_value_config->getValue();
}

int main(int argc, char** argv) {
    //test_yaml();
    test_config();
    return 0;
}
