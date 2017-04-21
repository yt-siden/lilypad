#ifndef LILYPAD_CHOLESKY_QR_HPP
#define LILYPAD_CHOLESKY_QR_HPP

#include <mpi.h>
#include <complex>
#include <iostream>
#include "lilypad/multivector.hpp"
#include "lilypad/localmatrix.hpp"
#include "lilypad/mkl_wrapper.hpp"

using cmplx_z = std::complex<double>;

namespace lilypad {
    // TODO: current: z only
    template <typename T>
    void cholesky_QR(const MultiVector<T>& A, MultiVector<T>& Q, LocalMatrix<T>& R)
    {
        double t_start = MPI_Wtime();
        // TODO: input check
        int M = A.local_rows();
        int L = R.rows();
        const std::complex<double> z_zero(0.0, 0.0), z_one(1.0, 0.0);

        // copy A to Q
        Q = A;
        double t_copy = MPI_Wtime();

        // local GEMM to R
        wrapper::gemm('C', 'N', L, L, M, z_one, A.ptr(), A.ld(), Q.ptr(), Q.ld(),
                z_zero, R.ptr(), R.ld());
        double t_gemm = MPI_Wtime();

        // Allreduce R
        Q.comm().Allreduce_sum(R);
        double t_reduce = MPI_Wtime();

        // cholesky factorization of R
        wrapper::potrf('U', L, R, R.ld());
        double t_chol = MPI_Wtime();

        // compute R^{-1}
        R.erase_lower_diag();
        LocalMatrix<T> R_(R);
        wrapper::trtri('U', 'N', L, R_, R_.ld());
        double t_inv = MPI_Wtime();

        // Q = A*R^{-1}
        wrapper::gemm('N', 'N', M, L, L, z_one, A.ptr(), A.ld(), R_.ptr(), R_.ld(),
                z_zero, Q.ptr(), Q.ld());
        double t_smgemm = MPI_Wtime();
    }

    // check
    template <typename T>
    void check_cholesky_QR(const MultiVector<T>& A, const MultiVector<T>& Q, const LocalMatrix<T>& R)
    {
        // TODO: input check
        int M = A.local_rows();
        int L = R.rows();
        const std::complex<double> z_zero(0.0, 0.0), z_one(1.0, 0.0);

        // tmp <- Q*R
        std::cout << "test1" << std::endl;
        MultiVector<T> tmp(A);
        wrapper::gemm('N', 'N', M, L, L, z_one, Q.ptr(), Q.ld(), R.ptr(), R.ld(),
                z_zero, tmp.ptr(), tmp.ld());

        // tmp -= A
        std::cout << "test2" << std::endl;
        tmp = tmp - A;

        std::cout << "test3" << std::endl;
        double norm = tmp.F_norm();
        if (A.comm().is_root())
            std::cout << "||Q*R - A||_F = " << std::scientific << norm << std::endl;
    }
}

#endif // LILYPAD_CHOLESKY_QR_HPP
