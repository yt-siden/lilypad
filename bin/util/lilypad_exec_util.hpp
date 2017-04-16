#ifndef LILYPAD_EXEC_UTIL_HPP
#define LILYPAD_EXEC_UTIL_HPP

#include <string>
#include <sstream>

namespace lilypad {
    // struct Args - command argument
    struct Args {
        int nprow; // the number of process per row
        int npcol; // the number of process per column
        int N;     // global row dimension
        int L;     // block size
    };

    // functions
    void show_info();
    Args parse_arguments(int& argc, char**& argv);
    void show_arguments(const Args& arg);
}

// template functions
template <typename T>
T convert_from_string(std::string str)
{
    std::stringstream ss(str);
    T ret;
    ss >> ret;
    return ret;
}

#endif // LILYPAD_EXEC_UTIL_HPP
