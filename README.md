## C++ Memory Hacking Class
Very easy to use class to read and modify other processes memory.  
And the best thing is: it supports multi-level-pointers out of the box!

#### Example usage

```C++
#include "Memory.hpp"
using std::string;

int main() {
    SetConsoleTitle("Memory Class Test");
    char* TARGET_PROCESS_NAME = "League of Legends.exe";
    
    HANDLE processHandle;
    int baseAddress;
    
    //////////////////////////////////////////////////////////////////////////////////
    /* Note: These pointers/offsets are probably outdated by the time you read this */
    
    int GAME_VERSION_MODULE_OFFSET = 0x2A1D738;
    
    int PLAYERS_MODULE_OFFSET = 0x1DAAED4;
        int HEALTH_OFFSET = 0x124;
        int MANA_OFFSET = 0x190;
        
    //////////////////////////////////////////////////////////////////////////////////
    
    Memory Memory;
    Memory.GetDebugPrivileges();
    processId = Memory.GetProcessId(TARGET_PROCESS_NAME);
    processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
    
    baseAddress = Memory.GetModuleBase(processHandle, (string)TARGET_PROCESS_NAME);
    std::cout << "Base address for module \"" << TARGET_PROCESS_NAME << "\" is " << baseAddress << " (in dec)..."<< std::endl;
    
    int playersAddress =     baseAddress + PLAYERS_MODULE_OFFSET;
    int gameVersionAddress = baseAddress + GAME_VERSION_MODULE_OFFSET;
    
    int ptrOffset[] = {0x0}; //0x0 offset is for player one. 0x4 would be player 2 etc
    int playerOneAddress = Memory.ReadPointerInt(processHandle, playersAddress, ptrOffset, 1);
    
    float playerOneHealth = Memory.ReadFloat(processHandle, playerOneAddress + HEALTH_OFFSET);
    float playerOneMana =   Memory.ReadFloat(processHandle, playerOneAddress + MANA_OFFSET);
    
    string gameVersion = Memory.ReadText(processHandle, gameVersionAddress);
    
    std::cout << "Game version: " << gameVersionAddress << std::endl;
    std::cout << "Player one has " << playerOneHealth << " health!" std::endl;
    std::cout << "Player one has " << playerOneMana << " mana!" std::endl;
    
    cin.get();
    return 0;
}
```
