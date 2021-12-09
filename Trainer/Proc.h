#pragma once
#include <vector>
#include <windows.h>
#include <tlhelp32.h>

class Proc
{

public:


	DWORD GetProcId(const wchar_t* procName);
	uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
	uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);

private:

};