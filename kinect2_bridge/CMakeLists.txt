cmake_minimum_required(VERSION 2.8.3)
project(kinect2_bridge)

#option(USE_OPENCL_REGISTRATION "Use OpenCL implementation of the depth registration" ON)
#option(USE_OPENCV_OPENCL       "Use OpenCV OpenCL functions for rectification"       OFF)
#set(MIN_WORKER_THREADS 2 CACHE STRING "Minimum number of worker threads")

#set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE RelWithDebInfo)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -std=c++11 -DBT_USE_DOUBLE_PRECISION -Wall")
# Unused warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuninitialized -Winit-self -Wunused-function -Wunused-label
#-Wunused-variable -Wunused-but-set-variable -Wunused-but-set-parameter")
# Additional warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Warray-bounds -Wtype-limits -Wreturn-type -Wsequence-point -Wparentheses
#-Wmissing-braces -Wchar-subscripts -Wswitch -Wwrite-strings -Wenum-compare -Wempty-body -Wlogical-op")

find_package(catkin REQUIRED COMPONENTS roscpp rostime std_msgs sensor_msgs cv_bridge
compressed_depth_image_transport depth_registration nodelet)
find_package(cmake_modules QUIET)

find_package(OpenCV REQUIRED)
find_package(OpenMP)

if(OPENMP_FOUND)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

catkin_package(
  INCLUDE_DIRS include
)

#execute_process(COMMAND find ${PROJECT_SOURCE_DIR} -type f OUTPUT_VARIABLE FILES_STRING)
#string(REPLACE "\n" ";" FILES_LIST ${FILES_STRING})
#add_custom_target(additional_files_${PROJECT_NAME}
#  SOURCES
#  ${FILES_LIST}
#  ${PROJECT_SOURCE_DIR}/../README.md
#)

include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIR}
)

#if(USE_OPENCL_REGISTRATION)
#  add_definitions(-DUSE_OPENCL_REGISTRATION)
#endif()
#if(USE_OPENCV_OPENCL)
#  add_definitions(-USE_OPENCV_OPENCL)
#endif()
#add_definitions(-DMIN_WORKER_THREADS=${MIN_WORKER_THREADS})
#add_definitions(-DK2_CALIB_PATH="${PROJECT_SOURCE_DIR}/data/")

#add_executable(kinect2_bridge src/kinect2_bridge.cpp)
#target_link_libraries(kinect2_bridge
#  ${catkin_LIBRARIES}
#  ${OpenCV_LIBRARIES}
#  freenect2
#)

add_library(freenect2_camera src/freenect2_bridge.cpp src/freenect2_nodelet.cpp)
target_link_libraries(freenect2_camera
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
  freenect2)

add_executable(freenect2_node src/freenect2_node.cpp)
target_link_libraries(freenect2_node freenect2_camera ${catkin_LIBRARIES})