#pragma once


class Breakpoint {
public:
    Breakpoint(pid_t pid, std::intptr_t address);

    void enable();
    void disable();

    bool is_enabled() const;
    std::intptr_t get_address() const;


private:
    pid_t _pid;
    std::intptr_t _address;
    bool _enabled;
    uint8_t _saved_data;
};


