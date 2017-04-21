# bin - contains executables

## examples

Example programs which use lilypad

Currently, no programs are available.

## testing

Testing programs which checks lilypad functionality

Currently, following programs are available.

### testing\_info: shows version, git hash and configure date

### testing\_args: tests command line argument parsing

### testing\_global: tests MPI environment and its RAII class

### testing\_type\_traits: tests type traits

### testing\_cholQR: tests Cholesky QR method for double precision complex matrix

Example:

```
mpirun -np 4 ./testing_cholQR --nprow 4 --npcol 1 --N 40000 --L 512
```

This performs QR factorization and calculation check for randomly generated 40000-by-512 matrix over 4-by-1 process grid.

Currenly, `N` must be divisable by `nprow`.

## util

Utilities used from executables only
