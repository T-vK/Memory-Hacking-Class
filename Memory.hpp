#pragma once
#include "Memory.hpp"
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <iostream>
#include <psapi.h>
#pragma comment(lib, "psapi")

class Memory
{
public:
    int GetProcessId(const char* processName);
    long GetModuleBase(HANDLE processHandle, std::string &sModuleName);
    BOOL SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);
    BOOL GetDebugPrivileges(void);
    int ReadInt(HANDLE processHandle, long address);
    int GetPointerAddress(HANDLE processHandle, long startAddress, int offsets[], int offsetCount);
    int ReadPointerInt(HANDLE processHandle, long startAddress, int offsets[], int offsetCount);
    float ReadFloat(HANDLE processHandle, long address);
    float ReadPointerFloat(HANDLE processHandle, long startAddress, int offsets[], int offsetCount);
    char* ReadText(HANDLE processHandle, long address);
    char* ReadPointerText(HANDLE processHandle, long startAddress, int offsets[], int offsetCount);
};
