cmake_minimum_required(VERSION 3.1)

# 工程名称
project(proccpp)

# 设置
set(CMAKE_CXX_STANDARD 14)

find_package( Boost COMPONENTS program_options REQUIRED )
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost Not found")
endif()
include_directories(${Boost_INCLUDE_DIR})

# 编译源码生成目标
add_executable(pcpp pcpp.cpp)
target_link_libraries(pcpp ${Boost_LIBRARIES})

install(TARGETS pcpp DESTINATION ${PROJECT_SOURCE_DIR}/bin)
