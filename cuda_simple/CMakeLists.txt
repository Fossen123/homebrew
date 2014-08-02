cmake_minimum_required(VERSION 2.8)
project(cuda_simple)

#--- These settings will be inherited by CUDA
set(CMAKE_CXX_COMPILER "/usr/local/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")

#--- Setup
find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS}) 
list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_20,code=sm_20")
set(CUDA_HOST_COMPILER ${CMAKE_CXX_COMPILER})
# If you have some C++11 stuff you don't want to propagate
#set(CUDA_PROPAGATE_HOST_FLAGS False)

#-- Compile
cuda_add_library(cuda STATIC simple.cu simple.cuh)
add_executable(cuda_simple main.cpp)
target_link_libraries(cuda_simple cuda ${CUDA_LIBRARIES})
