# Set the name and the supported language of the project
project(candy_pusher)

# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 2.8)
# Use the package PkgConfig to detect GTK+ headers/library files

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3          gtk+-3.0)
pkg_check_modules(LUA  REQUIRED lua5.2)

include_directories(${LUA_INCLUDE_DIRS})
link_directories(${LUA_LIBRARY_DIRS})


# Add other flags to the compiler
set(CMAKE_CXX_FLAGS "-std=c++11" )
add_definitions(${LUA_CFLAGS_OTHER})

add_library(common STATIC LedMatrix.cpp)

if(EXISTS /opt/vc/include/bcm_host.h)
	include_directories(/opt/vc/include)
	include_directories(/opt/vc/include/interface/vcos/pthreads)
	include_directories(/opt/vc/include/interface/vmcs_host)
	include_directories(/opt/vc/include/interface/vmcs_host/linux)

	link_directories(/opt/vc/lib)

	add_library(rpi_driver STATIC  rpi_driver.cpp common/imageLayer.c common/image.c  common/backgroundLayer.c )

	add_executable(candy_pusher_rpi candy_pusher_rpi.cpp )

	target_link_libraries(candy_pusher_rpi
	 common
	 rpi_driver
	 bcm_host
	 ${LUA_LIBRARIES} 
	 )
endif()

if(GTK3_FOUND)
	include_directories(${GTK3_INCLUDE_DIRS})
	link_directories(${GTK3_LIBRARY_DIRS})
	add_definitions(${GTK3_CFLAGS_OTHER})

	add_executable(candy_pusher     candy_pusher.cpp gtk_driver.cpp)

	target_link_libraries(candy_pusher
	 common
	 ${LUA_LIBRARIES}
	 ${GTK3_LIBRARIES}
	 )
endif()