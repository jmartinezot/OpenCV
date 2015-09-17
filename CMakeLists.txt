cmake_minimum_required(VERSION 2.4.6)

SET( CMAKE_CXX_COMPILER "/usr/bin/g++" )
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wuninitialized -Wunused-function -Wunused-label -Wunused-value -Wunused-variable")

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(src)

find_package(OpenCV REQUIRED)

link_directories(/usr/lib)

add_executable (DrawBubble.out src/DrawBubble.cpp)
add_executable (FindColourObjectFile.out src/FindColourObjectFile.cpp)
add_executable (FindColourObjectWebcam.out src/FindColourObjectWebcam.cpp)
add_executable (HistExample.out src/HistExample.cpp)
add_executable (ShowWebcam.out src/ShowWebcam.cpp)
add_executable (BackProjectionExample.out src/BackProjectionExample.cpp)
 
target_link_libraries(DrawBubble.out boost_program_options ${OpenCV_LIBS})
target_link_libraries(FindColourObjectFile.out boost_program_options ${OpenCV_LIBS})
target_link_libraries(FindColourObjectWebcam.out boost_program_options ${OpenCV_LIBS})
target_link_libraries(HistExample.out boost_program_options ${OpenCV_LIBS})
target_link_libraries(ShowWebcam.out boost_program_options ${OpenCV_LIBS})
target_link_libraries(BackProjectionExample.out boost_program_options ${OpenCV_LIBS})



