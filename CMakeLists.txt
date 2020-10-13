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

cmake_minimum_required (VERSION 3.5)

option(BUILD_SHARED_LIBS "Build the project shared library" ON)
option(SET_OUTPUT_FILE_PATH "Set the bin output file paht" OFF)

# Set project name.
project(pro)

# Set C and C++ build version.
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# Set the library version.
if(BUILD_SHARED_LIBS)
    set(VERSION_MAJOR 1)
    set(VERSION_MINOR 0)
    set(VERSION_PATCH 0)

    configure_file (
        "${CMAKE_CURRENT_LIST_DIR}/version/version.h.in"
        "${CMAKE_CURRENT_LIST_DIR}/version/version.h"
        )
    include_directories(${CMAKE_CURRENT_LIST_DIR}/version)
endif(BUILD_SHARED_LIBS)

# Set the bin output file.
if(SET_OUTPUT_FILE_PATH)
    SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        CACHE PATH
        ""
    )

    SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        ""
    )

    SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        CACHE PATH
        ""
    )
endif(SET_OUTPUT_FILE_PATH)

# Set the lib output path
# set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/build/libs/lib)
# file(GLOB_RECURSE ALL_HEARD_FILE ${CMAKE_CURRENT_LIST_DIR}/include/*.h)
# file(COPY ${ALL_HEARD_FILE} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build/libs/include)

# Set the build type: Debug or Release
if (CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE MATCHES "None")
    MESSAGE(STATUS "CMAKE_BUILD_TYPE is Debug")
    set(CMAKE_BUILD_GLOG_LOG_LEVEL "INFO")
    set(CMAKE_BUILD_DEBUG_INFO "DEBUG_INFO_OPEN")
else()
    MESSAGE(STATUS "CMAKE_BUILD_TYPE is Release")
    set(CMAKE_BUILD_GLOG_LOG_LEVEL "ERROR")
    set(CMAKE_BUILD_DEBUG_INFO "DEBUG_INFO_CLOSE")
endif()

# Set the Debug Info Head Name.
set(CMAKE_BUILD_DEBUG_INFO_HEAD "SQL")

configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/macro/cmake_build_macro.h.in"
    "${CMAKE_CURRENT_LIST_DIR}/macro/cmake_build_macro.h"
)
include_directories(${CMAKE_CURRENT_LIST_DIR}/macro)

# Build different platformat code.
if (PLATFORM MATCHES "arm")
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR arm)

    MESSAGE(STATUS "PLATFORM NAME " ${PLATFORM})

    # Set the build cross tool.
    set(CMAKE_CXX_COMPILER /opt/arm-2014.05/bin/arm-none-linux-gnueabi-g++)
    set(CMAKE_C_COMPILER   /opt/arm-2014.05/bin/arm-none-linux-gnueabi-gcc)

    # Set the C or C++ cross tool build flag.
    set(GNU_FLAGS "-mfpu=vfp -fPIC -g -W -O2")
    set(CMAKE_CXX_FLAGS "${GNU_FLAGS}")
    set(CMAKE_C_FLAGS   "${GNU_FLAGS}")

    # Include the third use libs. 
    include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/glog/include)

    link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/glog/lib)

else()
    set(GNU_FLAGS "-DCOM_X64 -g -W")
    set(CMAKE_CXX_FLAGS "${GNU_FLAGS}")
    set(CMAKE_C_FLAGS   "${GNU_FLAGS}")

    # Include the third use libs. 
    include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/glog/include)
    include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/sqlite3/include)


    link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/glog/lib)
    link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/sqlite3/lib)

endif()

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src ALL_SRC)

# Set share library
if (BUILD_SHARED_LIBS)
    add_library(pro SHARED ${ALL_SRC})
else()
    add_library(pro STATIC ${ALL_SRC})
endif()

# Set C++ target
set_property(TARGET pro PROPERTY CXX_STANDARD 11)
set_property(TARGET pro PROPERTY CXX_STANDARD_REQUIRED ON)

if (PLATFORM MATCHES "arm")
    target_link_libraries(pro dl pthread rt
        ${CMAKE_CURRENT_LIST_DIR}/libs/arm/glog/lib/libglog.a)

else()
    target_link_libraries(pro dl pthread rt glog
        ${CMAKE_CURRENT_LIST_DIR}/libs/x64/glog/lib/libglog.a
        ${CMAKE_CURRENT_LIST_DIR}/libs/x64/sqlite3/lib/libsqlite3.a)

endif()

# Set C target
# set_property(TARGET pro PROPERTY C_STANDARD 99)
# set_property(TARGET pro PROPERTY C_STANDARD_REQUIRED ON)

if (BUILD_SHARED_LIBS)
set_target_properties(pro
    PROPERTIES
        SOVERSION ${VERSION_MAJOR}
        VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    )
endif()



