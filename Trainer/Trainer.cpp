#include <iostream>
#include "Proc.h"

int main()
{
    // defining the process and the offsets

    LPCWSTR processName = L"test.exe";
    DWORD relativeOffset = 0x00007000; // pointer offset
    std::vector<unsigned int> offsets = { 0x80 , 0x10 , 0x68, 0x0 , 0x2C , 0x1A4 , 0x4F0 }; // dynamic offsets (?)

    /////////////

    Proc* process = new Proc();

    
    DWORD procId = process->GetProcId(processName);

    while(procId == 0) {
        procId = process->GetProcId(processName);
        Sleep(100);// this means its waiting for the process to start
    }

    uintptr_t moduleBase = process->GetModuleBaseAddress(procId, processName);

    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

    uintptr_t dynamicPtrBaseAddr = moduleBase + relativeOffset;

    uintptr_t valueAddress = process->FindDMAAddy(hProcess, dynamicPtrBaseAddr, offsets);

    int value = 0;

    ReadProcessMemory(hProcess, (BYTE*)valueAddress, &value, sizeof(value), nullptr);

    std::cout << "Value: " << std::dec << value << std::endl;

    return 0;
}