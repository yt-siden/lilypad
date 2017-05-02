#include <iostream>
#include <complex>

#include "lilypad.hpp"
#include "lilypad_exec_util.hpp"

int main(int argc, char* argv[])
{
    using cmplx = std::complex<double>;

    lilypad::Global global(argc, argv);
    if (global.is_root())
        lilypad::show_info();

    lilypad::Args arg = lilypad::parse_arguments(argc, argv);
    if (global.is_root())
        lilypad::show_arguments(arg);

    lilypad::MultiVector<cmplx> A(global.comm(), arg.N, arg.L);
    A.fill_random();

    lilypad::MultiVector<cmplx> Q(A);
    lilypad::LocalMatrix<cmplx> R(arg.L, arg.L);

    lilypad::cholesky_QR(A, Q, R);

    // check decomposition and orthogonality
    int M = A.local_rows();
    int L = R.rows();
    const cmplx_z z_zero(0.0, 0.0), z_one(1.0, 0.0);

    // tmp <- Q*R
    lilypad::MultiVector<cmplx> tmp(A);
    lilypad::wrapper::gemm('N', 'N', M, L, L, z_one, Q.ptr(), Q.ld(), R.ptr(), R.ld(),
            z_zero, tmp.ptr(), tmp.ld());

    // tmp -= A
    tmp = tmp - A;

    double norm = tmp.F_norm();
    if (A.comm().is_root())
        std::cout << "||Q*R - A||_F = " << std::scientific << norm << std::endl;

    // Orthogonality of Q
    lilypad::MultiVector<cmplx> Q_(Q);
    lilypad::LocalMatrix<cmplx> QQ(L, L), I(L, L);
    I.set_Eye();

    // QQ <- Q'*Q
    lilypad::wrapper::gemm('C', 'N', L, L, M, z_one, Q_.ptr(), Q_.ld(), Q.ptr(), Q.ld(),
            z_zero, QQ.ptr(), QQ.ld());
    Q.comm().Allreduce_sum(QQ);

    QQ = QQ - I;
    double d_work;
    double norm_QQ = lilypad::wrapper::lange('F', QQ.rows(), QQ.cols(), QQ, QQ.ld(), &d_work);
    if (A.comm().is_root())
        std::cout << "||Q^H*Q - I||_F = " << std::scientific << norm_QQ << std::endl;
}
