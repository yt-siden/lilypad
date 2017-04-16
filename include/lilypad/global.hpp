#ifndef LILYPAD_GLOBAL_HPP
#define LILYPAD_GLOBAL_HPP

#include <mpi.h>

namespace lilypad {
    // TODO: make this Singleton
    class Global {
        private:
            int mpi_provided_;
            int rank_;
            int size_;
        public:
            Global(int& argc, char**& argv)
            {
                MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &mpi_provided_);
                MPI_Comm_rank(MPI_COMM_WORLD, &rank_);
                MPI_Comm_size(MPI_COMM_WORLD, &size_);
                if (mpi_provided_ == MPI_THREAD_SINGLE)
                    if (rank_ == 0)
                        std::cerr << "MPI_THREAD_SINGLE is provided; 1 thread per 1 process" << std::endl;
            }
            ~Global()
            {
                MPI_Finalize();
            }

            int provided() const { return mpi_provided_; }
            int rank() const { return rank_; }
            int size() const { return size_; }
    };
}

#endif // LILYPAD_GLOBAL_HPP
