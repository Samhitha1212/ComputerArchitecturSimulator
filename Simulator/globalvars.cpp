#include "memory.h"
#include "registers.h"
#include "StackDetails.h"
#include <map>
#include <stack>
#include <vector>
#include <set>
#define N 100
MemoryClass Memory;
RegisterFileClass RegisterFile;
vector<string>
    arg[N]; // vector array to store the given assembly instructions arguments
map<string, pair<int, int>> Labels;
map<int, int> LineNumber;
unsigned int PC;
unsigned int currentInstruction;
set<int> breakpoints;
std::stack<StackDetails> functionStack;

