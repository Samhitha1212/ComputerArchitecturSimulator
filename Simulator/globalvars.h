#pragma once
#include "memory.h"
#include "registers.h"
#include "StackDetails.h"
#include <map>
#include <vector>
#include <stack>
#define N 100
extern RegisterFileClass RegisterFile;
extern MemoryClass Memory;
extern vector<string>
    arg[N]; // vector array to store the given assembly instructions arguments
extern map<string, pair<int, int>> Labels;
extern map<int, int> LineNumber;
extern unsigned int PC;
extern unsigned int currentInstruction;
extern vector<int> breakpoints;
extern std::stack<StackDetails> functionStack;

