OSX (homebrew) precompiled binaries
====
**note**: all libraries are compiled for 64bits MacOSX 10.9 (Maverick)

## Clang + OpenMP (including STL headers!)

To install the precompiled OSX10.9.2 **clang-omp**:

    ~/Developer/homebrew: brew install https://github.com/drtaglia/homebrew/raw/master/clangomp.rb


To install the **openmp runtime libraries** as mentioned :

    ~/Developer/homebrew: brew install https://github.com/drtaglia/homebrew/raw/master/openmprtl.rb
    
You can then download the **cpp example** with wget (brew install wget, if necessary):

    ~/Developer/homebrew: wget https://raw.githubusercontent.com/drtaglia/homebrew/master/clangomp.cpp
    
And finally **compile/execute** it!! 

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


## Qt 4.8.3 

As Qt was already in homebrew I used the **bottle** to package the binaries.
The following first downloads the tar.gz archive, then installs it with brew:

    wget https://raw.githubusercontent.com/drtaglia/homebrew/master/qt-4.8.5.mavericks.bottle.5.tar.gz
    brew install qt-4.8.5.mavericks.bottle.5.tar.gz
