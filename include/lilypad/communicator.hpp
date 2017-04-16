#ifndef LILYPAD_COMMUNICATOR_HPP
#define LILYPAD_COMMUNICATOR_HPP

#include <mpi.h>

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
    };
}

#endif // LILYPAD_COMMUNICATOR_HPP