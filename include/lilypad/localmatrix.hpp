#ifndef LILYPAD_LOCALMATRIX_HPP
#define LILYPAD_LOCALMATRIX_HPP

#include <vector>
#include <algorithm>
#include <iostream>
#include <lilypad/type_traits.hpp>

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
                : LocalMatrix(rows, cols, rows)
            {}

            int rows() const { return rows_; }
            int cols() const { return cols_; }
            int ld() const { return ld_; }
            int size() const { return data_.size(); }
            const T* ptr() const { return &data_[0]; }
            T* ptr() { return const_cast<T*>( static_cast<const LocalMatrix*>(this)->ptr() ); }

            void erase_lower_diag()
            {
                for (int i=0; i<cols_; ++i)
                    for (int j=i+1; j<ld_; ++j)
                        data_[i*ld_ + j] = 0.;
            }

            void dump() const
            {
                for (int i=0; i<rows_; ++i)
                {
                    for (int j=0; j<cols_; ++j)
                        std::cout << data_[j*ld_+i] << ' ';
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }

            void set_Zeros()
            {
                for (int i=0; i<cols_; ++i)
                for (int j=0; j<rows_; ++j)
                    data_[i*ld_+j] = 0.;
            }

            void set_Eye()
            {
                set_Zeros();
                for (int i=0; i<std::min(rows_, cols_); ++i)
                    data_[i*ld_+i] = 1.;
            }

            // for s,d,c,z
            template <typename std::enable_if<is_blas_implemented_type<T>::value, std::nullptr_t>::type = nullptr>
            LocalMatrix& operator-(const LocalMatrix& rhs)
            {
                // TODO: size check
                for (int i=0; i<cols_; ++i)
                for (int j=0; j<rows_; ++j)
                    data_[i*ld_+j] -= rhs.data_[i*ld_+j];

                return *this;
            }
    };
}

#endif // LILYPAD_LOCALMATRIX_HPP
