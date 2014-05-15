OSX (homebrew) precompiled binaries
====
**note**: all libraries are compiled for 64bits MacOSX.

# Precompiled Clang for OSX 10.9 with OpenMP support

To install the precompiled OSX10.9.2 clang-omp:

    ~/Developer/homebrew: brew install http://lgg.epfl.ch/SHARE/clangomp.rb


To install the openmp runtime libraries:

    ~/Developer/homebrew: brew install http://lgg.epfl.ch/SHARE/openmprtl.rb
    
You can then compile the cpp example:

    ~/Developer/homebrew: wget http://lgg.epfl.ch/SHARE/hello_openmp.cpp
    
And compile/execute it with: 

    ~/Developer/homebrew: /usr/local/bin/clang++ -fopenmp clangomp.cpp -o clangomp
    ~/Developer/homebrew: ./clangomp
    Hello from thread 0, nthreads 8
    Hello from thread 3, nthreads 8
    Hello from thread 4, nthreads 8
    Hello from thread 2, nthreads 8
    Hello from thread 1, nthreads 8
    Hello from thread 5, nthreads 8
    Hello from thread 6, nthreads 8
    Hello from thread 7, nthreads 8
