cmake_minimum_required(VERSION 3.10)
project(blt_hello_world)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wzero-as-null-pointer-constant -Winit-self -Wswitch-default -Wfloat-equal -Wno-unused-parameter -fPIC -march=native")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")

find_package(BearLibTerminal REQUIRED)
include_directories(SYSTEM ${BLT_INCLUDE_DIRS})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)

file(COPY ${PROJECT_SOURCE_DIR}/scene DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.h)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

include_directories(${PROJECT_HEADERS_DIR})

target_link_libraries(${PROJECT_NAME} ${BLT_LIBRARIES})

file(COPY ${BLT_LIBRARY} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add linting before compilation
include(CppLint)
ADD_STYLE_CHECK_TARGET(lint ${PROJECT_NAME} ${PROJECT_HEADERS_DIR} ${PROJECT_SOURCES_DIR})
add_dependencies(${PROJECT_NAME} lint)
