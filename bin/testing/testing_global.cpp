#include <iostream>

#include "lilypad.hpp"

int main(int argc, char* argv[])
{
    lilypad::Global global(argc, argv);

    const int comm_size = global.size();
    const int comm_rank = global.rank();
    for (int i=0; i<comm_size; ++i)
    {
        if (comm_rank == i)
        {
            std::cout << i << '/' << comm_size << std::endl;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
}
