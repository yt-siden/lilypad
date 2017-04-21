#ifndef LILYPAD_COMMUNICATOR_HPP
#define LILYPAD_COMMUNICATOR_HPP

#include <mpi.h>
#include <complex>
#include "lilypad/localmatrix.hpp"

using cmplx_z = std::complex<double>;

namespace lilypad {
    class Communicator {
        private:
            MPI_Comm comm_;
            int rank_;
            int size_;
        public:
            Communicator() {}
            explicit Communicator(MPI_Comm comm)
                : comm_(comm)
            {
                MPI_Comm_rank(comm, &rank_);
                MPI_Comm_size(comm, &size_);
            }

            void barrier() const { MPI_Barrier(comm_); }
            int rank() const { return rank_; }
            int size() const { return size_; }
            bool is_root() const { return rank_ == 0; }
            MPI_Comm comm() const { return comm_; }

            void Allreduce_sum(LocalMatrix<cmplx_z>& A)
            {
                MPI_Allreduce(MPI_IN_PLACE, A.ptr(), A.ld()*A.cols(), MPI_DOUBLE_COMPLEX, MPI_SUM, comm_);
            }

            void Allreduce_sum(double& a) const
            {
                MPI_Allreduce(MPI_IN_PLACE, &a, 1, MPI_DOUBLE, MPI_SUM, comm_);
            }

            void Barrier() const
            {
                MPI_Barrier(comm_);
            }
    };
}

#endif // LILYPAD_COMMUNICATOR_HPP
