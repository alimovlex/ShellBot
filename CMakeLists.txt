cmake_minimum_required(VERSION 2.8.4)
project(tgbot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(inc /usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR} include/)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()
add_executable(tgbot src/bot_api.cpp main.cpp)

target_link_libraries(tgbot /usr/lib/libTgBot.so ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})

