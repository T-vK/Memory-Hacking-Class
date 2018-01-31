#include "Memory.hpp"
#include <iostream>

int main() {
    SetConsoleTitle("Memory Class Test");
    std::string TARGET_PROCESS_NAME = "notepad.exe";
    
    int FONT_SIZE_MODULE_OFFSET = 0x2349C; //notepad.exe+2349C
    
    Memory Memory;
    Memory.GetDebugPrivileges();
    DWORD processId = Memory.GetProcessId(TARGET_PROCESS_NAME.c_str());
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
    
    long baseAddress = Memory.GetModuleBase(processHandle, TARGET_PROCESS_NAME);
    std::cout << "Base address for module \"" << TARGET_PROCESS_NAME << "\" is " << baseAddress << " (in dec)..." << std::endl;
    
    long fontSizeAddress = baseAddress + FONT_SIZE_MODULE_OFFSET;
    
    std::cout << "Font Size Address: " << fontSizeAddress << std::endl;
   
    while(true) {
        int fontSize = Memory.ReadInt(processHandle, fontSizeAddress);
        std::cout << "Font Size: " << fontSize/10 << std::endl;
    Sleep(2000);
    }

    std::cin.get();
    return 0;
}
