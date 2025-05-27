#include <iostream>
#include "health.h"
#include "memory.h"
#include "addresses.h"

void ApplyHealthHack() {
    static bool lastValid = false;
    static uintptr_t lastAddr = 0;

    uintptr_t moduleBase = GetModuleBase(L"afop.exe");
    if (!moduleBase) return;

    uintptr_t base = moduleBase + GameAddresses::Base;
    uintptr_t healthAddr = ResolvePointerChain(base, GameAddresses::HEALTH_OFFSET);

    bool isValid = (healthAddr && !IsBadWritePtr((void*)healthAddr, sizeof(int)));

    if (isValid) {
        *(int*)healthAddr = 1000;
        if (!lastValid || lastAddr != healthAddr) {
            std::cout << "[+] Valid health address: 0x" << std::hex << healthAddr << "\n";
        }
    }
    else {
        if (lastValid || lastAddr != healthAddr) {
            std::cout << "[-] Invalid health address: 0x" << std::hex << healthAddr << "\n";
        }
    }

    lastValid = isValid;
    lastAddr = healthAddr;
}
