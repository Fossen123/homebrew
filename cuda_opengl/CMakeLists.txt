cmake_minimum_required(VERSION 3.0)
project(cuda_opengl4)

#--- Cuda
find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})
list(APPEND LIBRARIES ${CUDA_LIBRARIES})

#--- OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
LIST(APPEND LIBRARIES ${OPENGL_LIBRARIES})

#--- Qt
# Specify this manually if Qt complains
# set(CMAKE_PREFIX_PATH "/Developer/Qt/5.2.1/clang_64") 
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL) 
find_package(Qt5Xml)

#--- Enable warnings
set(CMAKE_CXX_FLAGS "-Wall -Wno-switch -Wno-unused-function")
#--- NVCC Compiler Flags
#set(CUDA_NVCC_FLAGS "-gencode arch=compute_10,code=sm_10") # warning about obsolete
#set(CUDA_NVCC_FLAGS "-gencode arch=compute_20,code=sm_20") # invalid device function 
set(CUDA_NVCC_FLAGS "-gencode arch=compute_30,code=sm_30") # OK!!!!
#set(CUDA_NVCC_FLAGS "-gencode arch=compute_32,code=sm_32") # invalid device function 
#set(CUDA_NVCC_FLAGS "-gencode arch=compute_35,code=sm_35") # invalid device function 
#set(CUDA_NVCC_FLAGS "-gencode arch=compute_50,code=sm_50") # invalid device function

#--- Allow logger?
add_definitions(-D_ELPP_PERFORMANCE_MICROSECONDS)
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-4.8")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions(-DWITH_LOGGER)

file(GLOB SOURCES "*.h")
file(GLOB HEADERS "*.cpp")
file(GLOB CUDAS "*.cu")

add_executable(cuda_opengl ${SOURCES} ${HEADERS} ${CUDAS} ${SHADER_RESOURCES})
#cuda_add_executable(cuda_opengl ${SOURCES} ${HEADERS} ${CUDAS} ${SHADER_RESOURCES})
target_link_libraries(cuda_opengl ${LIBRARIES})
qt5_use_modules(cuda_opengl Widgets OpenGL Xml)

