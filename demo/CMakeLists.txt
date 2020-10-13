#
# For x64 compile, please use command
# cmake -DCMAKE_BUILD_TYPE=Debug ..
# For arm cross compile, please use command
# For Debug Version
# cmake -DPLATFORM=arm -DCMAKE_BUILD_TYPE=Debug ..
# For Release Version
# cmake -DPLATFORM=arm -DCMAKE_BUILD_TYPE=Release ..
# make -j4 && make install
#

cmake_minimum_required(VERSION 3.5)
include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt)

add_executable(demo demo.cpp)
set_property(TARGET demo PROPERTY CXX_STANDARD 11)
set_property(TARGET demo PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(demo glog dl)