# Tested on OSX MOUNTAIN LION and Cuda6.0
cmake_minimum_required(VERSION 3.0)
project(cudaopengl)

find_package(CUDA REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${CUDA_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})

#--- Compiler for C++ side
set(CUDA_HOST_COMPILER "/usr/bin/clang++")

#--- NVCC Compiler Flags
#set(CUDA_NVCC_FLAGS "-gencode arch=compute_10,code=sm_10") # warning about obsolete
#set(CUDA_NVCC_FLAGS "-gencode arch=compute_20,code=sm_20") # invalid device function 
set(CUDA_NVCC_FLAGS "-gencode arch=compute_30,code=sm_30") # OK!!!!
#set(CUDA_NVCC_FLAGS "-gencode arch=compute_32,code=sm_32") # invalid device function 
#set(CUDA_NVCC_FLAGS "-gencode arch=compute_35,code=sm_35") # invalid device function 
#set(CUDA_NVCC_FLAGS "-gencode arch=compute_50,code=sm_50") # invalid device function

cuda_add_executable(cudaopengl main.cu)
target_link_libraries(cudaopengl ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
