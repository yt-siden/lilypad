#include <iostream>
#include "lilypad_exec_util.hpp"
#include "lilypad/type_traits.hpp"

// check function
template <typename T>
void check()
{
    std::cout << "is_complex: " << is_complex<T>::value << std::endl;
    std::cout << "is_blas_implemented_floating_point_type: " << is_blas_implemented_floating_point_type<T>::value << std::endl;
    std::cout << "is_blas_implemented_type: " << is_blas_implemented_type<T>::value << std::endl << std::endl;
}

int main(int argc, char* argv[])
{
    lilypad::show_info();

    // check
    std::cout << "int" << std::endl;
    check<int>();
    std::cout << "unsigned" << std::endl;
    check<unsigned>();
    std::cout << "long" << std::endl;
    check<long>();
    std::cout << "long long" << std::endl;
    check<long long>();
    std::cout << "unsigned long long" << std::endl;
    check<unsigned long long>();
    std::cout << "char" << std::endl;
    check<char>();
    std::cout << "std::string" << std::endl;
    check<std::string>();
    std::cout << "float" << std::endl;
    check<float>();
    std::cout << "double" << std::endl;
    check<double>();
    std::cout << "long double" << std::endl;
    check<long double>();
    std::cout << "std::complex<float>" << std::endl;
    check<std::complex<float>>();
    std::cout << "std::complex<double>" << std::endl;
    check<std::complex<double>>();
    std::cout << "std::complex<long double>" << std::endl;
    check<std::complex<long double>>();
}
