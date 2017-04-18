#ifndef LILYPAD_TYPE_TRAITS_HPP
#define LILYPAD_TYPE_TRAITS_HPP

#include <complex>
#include <type_traits>

// is_complex
template <typename T>
struct is_complex {
    const static bool value = false;
};

template <typename T>
struct is_complex< std::complex<T> > {
    const static bool value = true;
};

// is_blas_implemented_floating_point_type (:= float, double)
template <typename T>
struct is_blas_implemented_floating_point_type {
    const static bool value = false;
};

template<>
struct is_blas_implemented_floating_point_type<float> {
    const static bool value = true;
};

template<>
struct is_blas_implemented_floating_point_type<double> {
    const static bool value = true;
};

// is_blas_implemented_type (:= float, double, std::complex<float>, std::complex<double>)
template <typename T>
struct is_blas_implemented_type {
    const static bool value =
        is_blas_implemented_floating_point_type<T>::value;
};

template <typename T>
struct is_blas_implemented_type< std::complex<T> > {
    const static bool value =
        is_blas_implemented_floating_point_type<T>::value;
};

#endif // LILYPAD_TYPE_TRAITS_HPP
