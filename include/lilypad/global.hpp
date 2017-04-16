#ifndef LILYPAD_GLOBAL_HPP
#define LILYPAD_GLOBAL_HPP

#include <mpi.h>

#include "lilypad/communicator.hpp"

namespace lilypad {
    // TODO: make this Singleton
    class Global {
        private:
            int mpi_provided_;
            Communicator comm_;
        public:
            Global(int& argc, char**& argv)
            {
                MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &mpi_provided_);
                comm_ = Communicator(MPI_COMM_WORLD);
                if (mpi_provided_ == MPI_THREAD_SINGLE)
                    if (comm_.rank() == 0)
                        std::cerr << "MPI_THREAD_SINGLE is provided; 1 thread per 1 process" << std::endl;
            }
            ~Global()
            {
                MPI_Finalize();
            }

            int provided() const { return mpi_provided_; }
            int rank() const { return comm_.rank(); }
            int size() const { return comm_.size(); }
    };
}

#endif // LILYPAD_GLOBAL_HPP
