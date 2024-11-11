#pragma once
#include "memory.h"
#include "registers.h"
#include "Execution.h"
#include "cache.h"
#include <map>
#include <vector>
#include <set>
#include <stack>
#include "cache_related.h"
#define N 100

extern string output_file;
extern RegisterFileClass RegisterFile;
extern MemoryClass Memory;
extern CacheInterface* cache;
extern vector<string> arg[N]; // vector array to store the given assembly instructions arguments
extern map<string, int> Labels;
extern map<int, int> LineNumber;
extern int instructions; //total number of instructions
extern unsigned int PC;
extern unsigned int Timer;
extern unsigned int currentInstruction;
extern set<int> breakpoints;
extern std::vector<StackDetails> functionStack;
extern bool IsFileloaded;
extern bool IsRuntimeErr;
extern bool IsCacheEnabled;
extern CacheStatastics cacheStatastics;

