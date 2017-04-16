#include <iostream>

#include "lilypad.hpp"

int main(int argc, char* argv[])
{
    std::cout << "lilypad version: " << lilypad::version     << std::endl;
    std::cout << "       git hash: " << lilypad::git_hash    << std::endl;
    std::cout << "    config date: " << lilypad::config_date << std::endl;
}
