CPR installation:

git clone https://github.com/libcpr/cpr.git
cd cpr && mkdir build && cd build
cmake .. -DCPR_USE_SYSTEM_CURL=ON -DBUILD_SHARED_LIBS=OFF
cmake --build . --parallel
sudo cmake --install .
cd ..
cd ..

CMakeLists.txt:

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

find_package(cpr REQUIRED)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE cpr::cpr)
