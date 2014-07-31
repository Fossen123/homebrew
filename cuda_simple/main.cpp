// @note CUDA6 supports clang, but DO NOT support libc++, so you need to use libstdc++!!!
//
// /usr/local/cuda/bin/nvcc simple.cu -c -o simple.cu.o -ccbin /usr/local/bin/clang++ -Xcompiler -stdlib=libstdc++
// /usr/bin/ar cr libcuda.a simple.cu.o
// /usr/local/bin/clang++ main.cpp libcuda.a /usr/local/cuda/lib/libcudart.dylib -Wl,-rpath -Wl,/usr/local/cuda/lib -Wl,-rpath,/usr/local/cuda/lib

#include "simple.cuh"

int main(void){ 
    simple();
    return 0; 
}
