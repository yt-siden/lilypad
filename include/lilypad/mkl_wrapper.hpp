#ifndef LILYPAD_MKL_WRAPPER_HPP
#define LILYPAD_MKL_WRAPPER_HPP

#include <mkl.h>
#include <complex>
#include "lilypad/localmatrix.hpp"
#include <iostream>

using cmplx_z = std::complex<double>;

namespace lilypad {
    namespace wrapper {
        // BLAS wrapper
        namespace blas {
            void gemm(const char transa, const char transb, const int M, const int N, const int K,
                    const cmplx_z alpha, const cmplx_z* A, const int lda, const cmplx_z* B, const int ldb,
                    const cmplx_z beta,  cmplx_z* C, const int ldc)
            {
                zgemm(&transa, &transb, &M, &N, &K, reinterpret_cast<const MKL_Complex16*>(&alpha),
                        reinterpret_cast<const MKL_Complex16*>(A), &lda,
                        reinterpret_cast<const MKL_Complex16*>(B), &ldb,
                        reinterpret_cast<const MKL_Complex16*>(&beta),
                        reinterpret_cast<MKL_Complex16*>(C), &ldc
                     );
            }
        }


        // LAPACK wrapper
        namespace lapack {
            void potrf(const char uplo, const int N, LocalMatrix<cmplx_z>& A, const int lda)
            {
                int info;
                zpotrf(&uplo, &N, reinterpret_cast<MKL_Complex16*>(A.ptr()), &lda, &info);
            }

            void trtri(const char uplo, const char diag, const int N, LocalMatrix<cmplx_z>& A, const int lda)
            {
                int info;
                ztrtri(&uplo, &diag, &N, reinterpret_cast<MKL_Complex16*>(A.ptr()), &lda, &info);
            }

            double lange(const char norm, const int M, const int N, const LocalMatrix<cmplx_z>& A, const int lda, double* work)
            {
                return zlange(&norm, &M, &N, reinterpret_cast<const MKL_Complex16*>(A.ptr()), &lda, work);
            }

            void larnv(const int idist, int* iseed, const int N, LocalMatrix<cmplx_z>& A)
            {
                zlarnv(&idist, iseed, &N, reinterpret_cast<MKL_Complex16*>( A.ptr() ));
            }
        }
    }
}

#endif // LILYPAD_LOCALMATRIX_HPP
