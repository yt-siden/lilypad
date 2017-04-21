# lilypad - A linear algebra library

Currently, basic linear algebra operation and cholesky QR for double precision complex is implemented.

# Requirements

- C++ compiler which supports C++11 (e.g. GCC 4.8.5 or later)
- Intel MKL (other BLAS/LAPACK support is progress)
- MPI Environment (e.g. OpenMPI, mpich)

Development Environment is following:

- OS: CentOS 6.9
- GCC 4.8.5
- Intel MKL 11.2.0
- OpenMPI 1.10.1

# How to use

1. clone this repository

2. clone Ryan's CMake Modules as submodule

```
git submodule init
gtt submodule update
```

3. configure and build using CMake

Note that out-of-tree build is **strictly recommended**.

Example:

```shell
mkdir /somewhere/to/build
cd /somewhere/to/build
# load required modules like this (if Environment Modules is used in your environment)
module load gcc/4.8.5 openmpi/1.10.1_gcc intel/mkl/11.2.0

CC=gcc CXX=g++ cmake /path/to/lilypad
make
```

# License

MIT.
see `LICENSE` file.

