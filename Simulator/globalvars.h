#pragma once
#include "memory.h"
#include "registers.h"
#include "StackDetails.h"
#include <map>
#include <vector>
#include <set>
#include <stack>
#define N 100
extern RegisterFileClass RegisterFile;
extern MemoryClass Memory;
extern vector<string>
    arg[N]; // vector array to store the given assembly instructions arguments
extern map<string, int> Labels;
extern map<int, int> LineNumber;
extern int instructions; //total number of instructions
extern unsigned int PC;
extern unsigned int currentInstruction;
extern set<int> breakpoints;
extern std::vector<StackDetails> functionStack;
extern bool IsFileloaded;

