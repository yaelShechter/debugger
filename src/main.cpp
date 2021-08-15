#include <iostream>
#include <unistd.h>

#include "Debugger.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Program was not specified" << std::endl;
        return -1;
    }
    auto program_name = argv[1];
    auto pid = fork();
    if (pid < -1)
    {
        std::cerr << "Couldn't fork";
        exit(1);
    }
    else if (0 == pid)
    {

    }
    else
    {
        std::cout << "Starting debugging process " << pid << std::endl;
        Debugger debugger(program_name, pid);
        debugger.run();
    }
}
