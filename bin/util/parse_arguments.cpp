#include <string>
#include <iostream>

#include "lilypad_exec_util.hpp"

// TODO: implement parser class
lilypad::Args lilypad::parse_arguments(int& argc, char**& argv)
{
    lilypad::Args arg;

    for (int i=1; i<argc; ++i)
    {
        if (std::string(argv[i]) == std::string("--nprow") && i+1 < argc)
        {
            arg.nprow = convert_from_string<int>(argv[i+1]);
            ++i;
        }
        else if (std::string(argv[i]) == std::string("--npcol") && i+1 < argc)
        {
            arg.npcol = convert_from_string<int>(argv[i+1]);
            ++i;
        }
        else if (std::string(argv[i]) == std::string("--N") && i+1 < argc)
        {
            arg.N = convert_from_string<int>(argv[i+1]);
            ++i;
        }
        else
        {
            std::cerr << "Argument '" << argv[i] << "' is invalid." << std::endl;
        }
    }
    return arg;
}
