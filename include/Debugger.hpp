#pragma once

#include <vector>

class Debugger {
public:
    Debugger (std::string program_name, pid_t pid);

    void run() const;

private:
    static std::vector<std::string> split(const std::string& s, char delimiter);
    static bool is_prefix(const std::string& command, const std::string& prefix_of);

private:
    void handle_command(const std::string& line) const;
    void continue_execution() const;

private:
    std::string _program_name;
    pid_t _pid;
};
