cmake_minimum_required(VERSION 3.17)
project(fast_web_server)

set(CMAKE_CXX_STANDARD 20)

FIND_PACKAGE( Boost  )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(SERVER_SRCS
        "${PROJECT_SOURCE_DIR}/server/server.cpp"
        "${PROJECT_SOURCE_DIR}/http/http.cpp"
        "${PROJECT_SOURCE_DIR}/request/request.cpp"
        "${PROJECT_SOURCE_DIR}/response/response.cpp"
        "${PROJECT_SOURCE_DIR}/socket/socket.cpp"
        "${PROJECT_SOURCE_DIR}/socket/scope_guard.cpp"
        )

find_package(Threads)

add_executable(fast_web_server main.cpp ${SERVER_SRCS})

target_link_libraries(fast_web_server LINK_PUBLIC ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_SOURCE_DIR}/http"
        "${PROJECT_SOURCE_DIR}/server"
        "${PROJECT_SOURCE_DIR}/response"
        "${PROJECT_SOURCE_DIR}/request"
        "${PROJECT_SOURCE_DIR}/socket"
        "${PROJECT_SOURCE_DIR}/socket"
        )
