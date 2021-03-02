cmake_minimum_required(VERSION 2.8)
project(topson)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(.)

find_library(YAMLCPP yaml-cpp)
message("***", ${YAMLCPP})

set(LIB_SRC
    topson/log.cc
    topson/util.cc
    topson/config.cc
    )

add_library(topson SHARED ${LIB_SRC})
#add_library(topson_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (topson_static PROPERTIES OUTPUT_NAME "topson")

add_executable(test tests/test.cc)
add_dependencies(test topson)
target_link_libraries(test topson ${YAMLCPP})

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config topson)
target_link_libraries(test_config topson ${YAMLCPP})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
