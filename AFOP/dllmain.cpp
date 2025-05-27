#include <Windows.h>
#include <iostream>
#include "Health.h"
#include "Energy.h"

void SetupConsole() {
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);
    std::cout << "[+] DLL Injected\n";
}

DWORD WINAPI MainThread(HMODULE instance) {
    SetupConsole();

    while (!GetAsyncKeyState(VK_DELETE)) {
        ApplyHealthHack();
		ApplyEnergyHack();

        Sleep(100);
    }

    std::cout << "[*] Uninjecting...\n";
	FreeConsole();
	fclose(stdout);
    FreeLibraryAndExitThread(instance, 0);
    return FALSE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        HANDLE hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr);
        if (hThread != nullptr) {
            CloseHandle(hThread);
        }
        break;
    }
    return TRUE;
}
