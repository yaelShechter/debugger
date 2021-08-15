#include <sstream>
#include <iostream>
#include <sys/wait.h>
#include <sys/ptrace.h>

#include "linenoise.h"
#include "Debugger.hpp"

Debugger::Debugger(std::string program_name, pid_t pid):
    _program_name(std::move(program_name)),
    _pid(pid)
{}


void Debugger::run() const
{
    int wait_status;
    auto options = 0;
    waitpid(_pid, &wait_status, options);

    char* line = nullptr;
    while ((line = linenoise("Debugger> ")) != nullptr)
    {
        handle_command(line);
        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }
}


std::vector<std::string> Debugger::split(const std::string &s, char delimiter)
{
    std::vector<std::string> output {};
    std::stringstream ss {s};
    std::string word;

    while (std::getline(ss, word, delimiter))
    {
        output.push_back(word);
    }
    return output;
}


bool Debugger::is_prefix(const std::string& command, const std::string& prefix_of)
{
    if (command.size() > prefix_of.size())
    {
        return false;
    }
    return std::equal(command.begin(), command.end(), prefix_of.begin());
}


void Debugger::handle_command(const std::string &line) const
{
    auto args = split(line, ' ');
    auto command = args[0];

    if (is_prefix(command, "continue"))
    {
        continue_execution();
    }
    else
    {
        std::cerr << "Unknown command";
    }
}


void Debugger::continue_execution() const
{
    ptrace(PTRACE_CONT, _pid, nullptr, nullptr);

    int wait_status;
    auto options = 0;
    waitpid(_pid, &wait_status, options);
}
