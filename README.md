## C++ Memory Hacking Class
Very easy to use class to read and modify other processes memory on Windows.  
And the best thing is: it supports multi-level-pointers out of the box!

#### Building
The master branch has only been tested for Visual C++.
The gcc branch has only been tested for g++. (Use: `g++ -o Example2.exe Memory.cpp Example2.cpp -lpsapi -static`)

#### Test
I have included a simple test program `Example2.cpp`. It simply looks for a notepad.exe process and reads out the current font size.  
It has only been tested on a 64 bit Windows 10 so far.

#### Example usage

```C++
#include "Memory.hpp"
#include <iostream>

int main() {
    SetConsoleTitle("Memory Class Test");
    std::string TARGET_PROCESS_NAME = "League of Legends.exe";
    
    //////////////////////////////////////////////////////////////////////////////////
    /* Note: These pointers/offsets are probably outdated by the time you read this */
    
    int GAME_VERSION_MODULE_OFFSET = 0x2A1D738;
    
    int PLAYERS_MODULE_OFFSET = 0x1DAAED4;
        int HEALTH_OFFSET = 0x124;
        int MANA_OFFSET = 0x190;
        
    //////////////////////////////////////////////////////////////////////////////////
    
    Memory Memory;
    Memory.GetDebugPrivileges();
    const char* TARGET_PROCESS_NAME2 = TARGET_PROCESS_NAME.c_str();
    DWORD processId = Memory.GetProcessId(TARGET_PROCESS_NAME2);
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
    
    long baseAddress = Memory.GetModuleBase(processHandle, TARGET_PROCESS_NAME);
    std::cout << "Base address for module \"" << TARGET_PROCESS_NAME << "\" is " << baseAddress << " (in dec)..." << std::endl;
    
    long playersAddress =     baseAddress + PLAYERS_MODULE_OFFSET;
    long gameVersionAddress = baseAddress + GAME_VERSION_MODULE_OFFSET;
    
    int ptrOffset[] = {0x0}; //0x0 offset is for player one. 0x4 would be player 2 etc
    long playerOneAddress = Memory.ReadPointerInt(processHandle, playersAddress, ptrOffset, 1);
    
    float playerOneHealth = Memory.ReadFloat(processHandle, playerOneAddress + HEALTH_OFFSET);
    float playerOneMana =   Memory.ReadFloat(processHandle, playerOneAddress + MANA_OFFSET);
    
    std::string gameVersion = Memory.ReadText(processHandle, gameVersionAddress);
    
    std::cout << "Game version: " << gameVersion << std::endl;
    std::cout << "Player one has " << playerOneHealth << " health!" << std::endl;
    std::cout << "Player one has " << playerOneMana << " mana!" << std::endl;
    
    std::cin.get();
    return 0;
}
```
