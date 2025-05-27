#include <iostream>
#include "health.h"
#include "memory.h"
#include "addresses.h"

void ApplyEnergyHack() {
    static bool lastValid = false;
    static uintptr_t lastAddr = 0;

    uintptr_t moduleBase = GetModuleBase(L"afop.exe");
    if (!moduleBase) return;

    uintptr_t base = moduleBase + GameAddresses::Base;
    uintptr_t energyAddr = ResolvePointerChain(base, GameAddresses::ENERGY_OFFSET);

    bool isValid = (energyAddr && !IsBadWritePtr((void*)energyAddr, sizeof(int)));

    if (isValid) {
        *(int*)energyAddr = 200;
        if (!lastValid || lastAddr != energyAddr) {
            std::cout << "[+] Valid energy address: 0x" << std::hex << energyAddr << "\n";
        }
    }
    else {
        if (lastValid || lastAddr != energyAddr) {
            std::cout << "[-] Invalid energy address: 0x" << std::hex << energyAddr << "\n";
        }
    }

    lastValid = isValid;
    lastAddr = energyAddr;
}
