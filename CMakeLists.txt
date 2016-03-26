# Set the name and the supported language of the project
project(candy_pusher)

# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 3.0)
# Use the package PkgConfig to detect GTK+ headers/library files
include(FindLua)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

include_directories(/opt/vc/include)
include_directories(/opt/vc/include/interface/vcos/pthreads)
include_directories(/opt/vc/include/interface/vmcs_host)
include_directories(/opt/vc/include/interface/vmcs_host/linux)
include_directories(${LUA_INCLUDE_DIR})

link_directories(/opt/vc/lib)

# Add other flags to the compiler
set(CMAKE_CXX_FLAGS "-std=c++11" )
add_definitions(${GTK3_CFLAGS_OTHER})

add_library(common STATIC  common/imageLayer.c common/image.c common/imageKey.c common/key.c common/font.c common/backgroundLayer.c common/imageGraphics.c common/hsv2rgb.c)

# Add an executable compiled from hello.c
add_executable(candy_pusher candy_pusher.cpp LedMatrix.cpp rpi_driver.cpp gtk_driver.cpp)

# Link the target to the GTK+ libraries
target_link_libraries(candy_pusher bcm_host common ${LUA_LIBRARIES} ${GTK3_LIBRARIES})
