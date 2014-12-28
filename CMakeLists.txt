cmake_minimum_required(VERSION 2.4.6)

SET( CMAKE_CXX_COMPILER "/usr/bin/g++" )
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wuninitialized -Wunused-function -Wunused-label -Wunused-value -Wunused-variable")

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(src)

find_package(OpenCV REQUIRED)

link_directories(/usr/lib)

add_executable (DrawBubble src/DrawBubble.cpp)
 
target_link_libraries(DrawBubble boost_program_options ${OpenCV_LIBS})



