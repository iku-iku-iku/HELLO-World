#pragma once
#include <cstdio>

#define LOG(Msg) core::Log(Msg);

namespace core
{
    inline void Log(const char* msg) { printf("%s\n", msg); }
} // namespace Core
