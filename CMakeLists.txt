
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

find_package(cpr REQUIRED)

add_executable(server server.cpp)
target_link_libraries(server PRIVATE cpr::cpr)