#ifndef LILYPAD_MULTIVECROR_HPP
#define LILYPAD_MULTIVECROR_HPP

#include <unistd.h>
#include <vector>
#include <cmath>
#include "lilypad/communicator.hpp"
#include "lilypad/localmatrix.hpp"
#include "lilypad/mkl_wrapper.hpp"
#include "lilypad/type_traits.hpp"

namespace lilypad {
    template <typename T>
    class MultiVector {
        private:
            Communicator comm_;
            int global_rows_;
            int local_rows_;
            int cols_;
            int ld_; // leading dimension
            LocalMatrix<T> data_;
        public:
            // TODO: Fix in case of comm_.size() is NOT a divisor of m
            // TODO: Fix in case of local_rows_ != ld_
            MultiVector(Communicator comm, int m, int n)
                : comm_(comm), global_rows_(m), local_rows_(m / comm_.size()),
                  cols_(n), ld_(local_rows_), data_(local_rows_, cols_)
            {}

            const T* ptr() const { return data_.ptr(); }
            T* ptr() { const_cast<T*>(static_cast<const MultiVector*>(this)->ptr()); }
            int global_rows() const { return global_rows_; }
            int local_rows() const { return local_rows_; }
            int cols() const { return cols_; }
            int ld() const { return ld_; }
            Communicator comm() const { return comm_; }
            void fill_random() {
                // TODO: use C++11 random number generator
                int iseed[] = { comm_.rank(), comm_.rank(), comm_.rank(), 1 };
                wrapper::lapack::larnv(4, iseed, ld_*cols_, data_);
            }

            double F_norm() const {
                double tmp;
                double ret = wrapper::lapack::lange('F', local_rows_, cols_, data_, ld_, &tmp);
                ret *= ret;
                comm_.Allreduce_sum(ret);
                return sqrt(ret);
            }

            void dump()
            {
                for (int i=0; i<comm_.size(); ++i)
                {
                    if (i == comm_.rank())
                    {
                        std::cout << i << ':' << std::endl;
                        data_.dump();
                    }
                    sleep(1);
                    comm_.Barrier();
                }
            }

            // for s,d,c,z
            template <typename std::enable_if<is_blas_implemented_type<T>::value, std::nullptr_t>::type = nullptr>
            MultiVector& operator-(const MultiVector& rhs)
            {
                // TODO: size check
                data_ = data_ - rhs.data_;

                return *this;
            }
    };
}

#endif // LILYPAD_MULTIVECROR_HPP
