#indicates the name of resulting workspace
cmake_minimum_required(VERSION 2.8.3)
project (akshay)


#setting compiler and library support for ISO c++ 2011 standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")



#adding extra include directories
include_directories(/usr/local/include)

#adding extra lib directories
link_directories(/usr/local/lib)
link_directories(/opt/pleora/ebus_sdk/Ubuntu-x86_64/lib)
#adds an executable target to the build process (no ext_libraries here)
add_executable (akshay wavtomp3.cpp)



#specify dependency on an extra library


target_link_libraries(akshay libmp3lame.so)

