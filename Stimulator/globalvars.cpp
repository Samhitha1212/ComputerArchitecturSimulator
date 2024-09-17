#include "memory.h"
#include "registers.h"
#include <map>

MemoryClass Memory;
RegisterFileClass RegisterFile;
vector<string>
    arg[N]; // vector array to store the given assembly instructions arguments
map<string, pair<int, int>> Labels;
map<int, int> LineNumber;
unsigned int PC;
unsigned int currentInstruction;