#ifndef LILYPAD_MULTIVECROR_HPP
#define LILYPAD_MULTIVECROR_HPP

#include <vector>
#include "lilypad/communicator.hpp"

namespace lilypad {
    template <typename T>
    class MultiVector {
        private:
            Communicator comm_;
            std::vector<T> data_;
            int local_rows_;
            int global_rows_;
            int cols_;
            int ld_; // leading dimension
        public:
            MultiVector(Communicator comm, int m, int n)
                : comm_(comm), global_rows_(m), cols_(n)
            {
                // TODO: Fix in case of comm_.size() is NOT a divisor of m
                // TODO: Fix in case of local_rows_ != ld_
                local_rows = ld_ = global_rows_ / comm_.size();
                data_.resize(ld_ * cols_);
            }

            T* ptr() const { return &data_[0]; }
            T* ptr() { const_cast<T*>(static_cast<const MultiVector*>(this)->ptr()); }
            int global_rows() const { return global_rows_; }
            int local_rows() const { return local_rows_; }
            int cols() const { return cols_; }
            int ld() const { return ld_; }
    };
}

#endif // LILYPAD_MULTIVECROR_HPP
