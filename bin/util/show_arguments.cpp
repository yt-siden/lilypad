#include <iostream>

#include "lilypad_exec_util.hpp"

void lilypad::show_arguments(const lilypad::Args& arg)
{
    std::cout << "nprow: " << arg.nprow << std::endl;
    std::cout << "npcol: " << arg.npcol << std::endl;
    std::cout << "N: "     << arg.N     << std::endl;
    std::cout << "L: "     << arg.L     << std::endl;
}
