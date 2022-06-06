#include "../pch.h"

Scan::Scan(const char* moduleName)
{
	this->moduleAddress = reinterpret_cast<uintptr_t>(GetModuleHandleA(moduleName));
}

std::vector<int> Scan::ConvertPatternToByte(const char* pattern)
{
    auto bytes = std::vector<int>();

    auto patternStart = const_cast<char*>(pattern);
    auto patternEnd = const_cast<char*>(pattern) + strlen(pattern);

    for (auto currentByte = patternStart; currentByte < patternEnd; ++currentByte)
    {
        if (*currentByte == '?') // if it's null
        {
            ++currentByte;
            if (*currentByte == '?') ++currentByte;
            bytes.push_back(-1);
        }
        else bytes.push_back(strtoul(currentByte, &currentByte, 16));
    }
    return bytes;
}

Handle Scan::scan(const char* name, const char* pattern)
{
    auto dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(this->moduleAddress);
    auto ntHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<std::uint8_t*>(this->moduleAddress) + dosHeader->e_lfanew);

    auto size = ntHeader->OptionalHeader.SizeOfImage;
    auto patternBytes = this->ConvertPatternToByte(pattern);
    auto startModule = reinterpret_cast<std::uint8_t*>(this->moduleAddress);

    for (auto i = 0; i < size - patternBytes.size(); ++i)
    {
        bool found_byte_set = true;
        for (auto j = 0; j < patternBytes.size(); ++j)
        {
            if (startModule[i + j] != patternBytes.data()[j] && patternBytes.data()[j] != -1)
            {
                found_byte_set = false;
                break;
            }
        }
        if (found_byte_set) {
            globalvars::g_LogInstance->Write("[Memory] Found -> {}", name);
            return Handle(reinterpret_cast<std::uintptr_t>(&startModule[i]));
        }
    }
    globalvars::g_LogInstance->Write("[Memory] Failed to find -> {}", name);
    return Handle();
}