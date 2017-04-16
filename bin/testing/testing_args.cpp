#include <iostream>

#include "lilypad.hpp"
#include "lilypad_exec_util.hpp"

int main(int argc, char* argv[])
{
    lilypad::Global global(argc, argv);
    if (global.is_root())
        lilypad::show_info();

    lilypad::Args arg = lilypad::parse_arguments(argc, argv);
    if (global.is_root())
    {
        std::cout << "nprow: " << arg.nprow << std::endl;
        std::cout << "npcol: " << arg.npcol << std::endl;
        std::cout << "N: "     << arg.N     << std::endl;
    }
}
