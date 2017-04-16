#ifndef LILYPAD_LOCALMATRIX_HPP
#define LILYPAD_LOCALMATRIX_HPP

#include <vector>

namespace lilypad {
    template <typename T>
    class LocalMatrix {
        private:
            std::vector<T> data_;
            int rows_;
            int cols_;
            int ld_;
        public:
            LocalMatrix(int rows, int cols, int ld)
                : rows_(rows), cols_(cols), ld_(ld)
            {
                data_.resize(ld_*cols_);
            }
            LocalMatrix(int rows, int cols)
            {
                LocalMatrix(rows, cols, rows);
            }

            int rows() const { return rows_; }
            int cols() const { return cols_; }
            int ld() const { return ld_; }
            T* ptr() const { return &data_[0]; }
            T* ptr() { return const_cast<T*>( static_cast<const LocalMatrix*>(this)->ptr() ); }
    };
}

#endif // LILYPAD_LOCALMATRIX_HPP
