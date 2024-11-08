#include "memory.h"
#include "registers.h"
#include "Execution.h"
#include <map>
#include <stack>
#include <vector>
#include <set>
#define N 100
MemoryClass Memory;
RegisterFileClass RegisterFile;
vector<string>
    arg[N]; // vector array to store the given assembly instructions arguments
map<string,int> Labels;
map<int, int> LineNumber;
int instructions=0;
unsigned int PC;
unsigned int currentInstruction;
set<int> breakpoints;
std::vector<StackDetails> functionStack;
bool IsFileloaded = false;
bool IsRuntimeErr=false;


