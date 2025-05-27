#include "memory.h"
#include <Windows.h>
#include <iostream>
#include <vector>


uintptr_t GetModuleBase(const wchar_t* moduleName) {
    static uintptr_t cachedBase = 0;
    if (!cachedBase) {
        cachedBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(moduleName));
        if (!cachedBase) {
            std::wcerr << L"[-] Failed to get module base for: " << moduleName << L"\n";
        }
    }
    return cachedBase;
}

uintptr_t ResolvePointerChain(uintptr_t base, const std::vector<uintptr_t>& offsets) {
    for (size_t i = 0; i < offsets.size(); ++i) {
        if (!IsValidReadPtr(base)) {
            std::wcerr << L"[-] Invalid pointer at level " << i << L"\n";
            return 0;
        }
        base = *reinterpret_cast<uintptr_t*>(base);
        base += offsets[i];
    }
    return base;
}

bool IsValidReadPtr(uintptr_t address, size_t size) {
    return !IsBadReadPtr(reinterpret_cast<void*>(address), size);
}

bool IsValidWritePtr(uintptr_t address, size_t size) {
    return !IsBadWritePtr(reinterpret_cast<void*>(address), size);
}
