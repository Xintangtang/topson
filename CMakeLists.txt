cmake_minimum_required(VERSION 2.8)
project(topson)

include (cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

include_directories(.)



set(LIB_SRC
    topson/config.cc
    topson/fiber.cc
    topson/log.cc
    topson/scheduler.cc
    topson/thread.cc
    topson/util.cc
    )

add_library(topson SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(topson) #__FILE__
#add_library(topson_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (topson_static PROPERTIES OUTPUT_NAME "topson")

find_library(YAMLCPP yaml-cpp)
find_library(PTHREAD pthread)




set(LIBS
        topson
        pthread
        yaml-cpp)

message("***", ${LIBS})

add_executable(test tests/test.cc)
add_dependencies(test topson)
force_redefine_file_macro_for_sources(test) #__FILE__
target_link_libraries(test topson ${LIBS})

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config topson)
force_redefine_file_macro_for_sources(test_config) #__FILE__
target_link_libraries(test_config topson ${LIBS})

add_executable(test_thread tests/test_thread.cc)
add_dependencies(test_thread topson)
force_redefine_file_macro_for_sources(test_thread) #__FILE__
target_link_libraries(test_thread topson ${LIBS})

add_executable(test_util tests/test_util.cc)
add_dependencies(test_util topson)
force_redefine_file_macro_for_sources(test_util) #__FILE__
target_link_libraries(test_util ${LIBS})

add_executable(test_fiber tests/test_fiber.cc)
add_dependencies(test_fiber topson)
force_redefine_file_macro_for_sources(test_fiber) #__FILE__
target_link_libraries(test_fiber ${LIBS})

add_executable(test_scheduler tests/test_scheduler.cc)
add_dependencies(test_scheduler topson)
force_redefine_file_macro_for_sources(test_scheduler) #__FILE__
target_link_libraries(test_scheduler ${LIBS})

#add_executable(test_iomanager tests/test_iomanager.cc)
#add_dependencies(test_iomanager topson)
#force_redefine_file_macro_for_sources(test_iomanager) #__FILE__
#target_link_libraries(test_iomanager ${LIBS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
