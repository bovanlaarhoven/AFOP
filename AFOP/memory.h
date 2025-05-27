#pragma once
#include <vector>
#include <cstdint>

uintptr_t GetModuleBase(const wchar_t* moduleName);
uintptr_t ResolvePointerChain(uintptr_t base, const std::vector<uintptr_t>& offsets);
bool IsValidReadPtr(uintptr_t address, size_t size = sizeof(uintptr_t));
bool IsValidWritePtr(uintptr_t address, size_t size = sizeof(int));
