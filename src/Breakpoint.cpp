#include <cstdint>
#include <sys/types.h>
#include <sys/ptrace.h>

#include "Breakpoint.hpp"

Breakpoint::Breakpoint(pid_t pid, std::intptr_t address):
    _pid(pid),
    _address(address),
    _enabled(false),
    _saved_data()
{}


void Breakpoint::enable()
{
    auto data = ptrace(PTRACE_PEEKDATA, _pid, _address, nullptr);
    _saved_data = static_cast<uint8_t>(data & 0xff);
    uint64_t int3 = 0xcc;
    uint64_t data_with_int3 = ((data & ~0xff) | int3);
    ptrace(PTRACE_POKEDATA, _pid, _address, data_with_int3);

    _enabled = true;
}


void Breakpoint::disable()
{
    auto data_with_int3 = ptrace(PTRACE_PEEKDATA, _pid, _address, nullptr);
    uint64_t restored_data = ((data_with_int3 & ~0xff) | _saved_data);
    ptrace(PTRACE_POKEDATA, _pid, _address, restored_data);

    _enabled = false;
}

bool Breakpoint::is_enabled() const
{
    return _enabled;
}

std::intptr_t Breakpoint::get_address() const
{
    return _address;
}