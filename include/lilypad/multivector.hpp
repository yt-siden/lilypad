#ifndef LILYPAD_MULTIVECROR_HPP
#define LILYPAD_MULTIVECROR_HPP

#include <vector>
#include "lilypad/communicator.hpp"
#include "lilypad/localmatrix.hpp"

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
            {
            }

            T* ptr() const { return data_.ptr(); }
            T* ptr() { const_cast<T*>(static_cast<const MultiVector*>(this)->ptr()); }
            int global_rows() const { return global_rows_; }
            int local_rows() const { return local_rows_; }
            int cols() const { return cols_; }
            int ld() const { return ld_; }
    };
}

#endif // LILYPAD_MULTIVECROR_HPP
