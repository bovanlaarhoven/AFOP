#pragma once
#include <Windows.h>
#include <vector>


namespace GameAddresses {
    constexpr uintptr_t Base = 0x09FCBF70;

    const std::vector<uintptr_t> Y = {
     0x838, 0xD8, 0xC0, 0x2B8, 0xB8, 0xEB4
    };

    const std::vector<uintptr_t> X = {
        0x838, 0xD8, 0xC0, 0x2B8, 0xB8, 0xEB0
    };

    const std::vector<uintptr_t> Z = {
        0x838, 0xD8, 0xC0, 0x2B8, 0xB8, 0xEB8
    };

    const std::vector<uintptr_t> PlayerOffset = {
        0x838, 0xC8, 0x8, 0x0, 0x8, 0x708
    };

    inline std::vector<uintptr_t> MakeOffsetChain(uintptr_t lastOffset) {
        std::vector<uintptr_t> offsets = PlayerOffset;
        offsets.push_back(lastOffset);
        return offsets;
    }

    const std::vector<uintptr_t> HEALTH_OFFSET = MakeOffsetChain(0x68);
	const std::vector<uintptr_t> ENERGY_OFFSET = MakeOffsetChain(0x78);

}