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
    lilypad::check_cholesky_QR(A, Q, R);
}
