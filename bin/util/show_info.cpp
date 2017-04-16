#include <iostream>

#include "lilypad_exec_util.hpp"
#include "lilypad/info.hpp"

void lilypad::show_info()
{
    std::cout << "lilypad version: " << lilypad::version     << std::endl;
    std::cout << "       git hash: " << lilypad::git_hash    << std::endl;
    std::cout << "    config date: " << lilypad::config_date << std::endl;
}
