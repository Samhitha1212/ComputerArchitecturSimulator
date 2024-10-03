#pragma once 
#include <string>
#include <bitset>
using namespace std;

bool loadfile(std::string filename);

void ExecuteInstruction(int);
void executeRType(int);
void executeIType(int);
void executeSType(int);
void executeBType(int);
void executeJType(int);
void executeUType(int);
void InitializeTotalData();

void addBreakPoint( int lineN);
void deleteBreakPoint(int lineN);
bool IsbreakPoint(int instr);
void showBreakpoints();

struct StackDetails {
  string name;
  int line;
  bitset<64> ra;
};

void PushIntoStack(string label,int line, bitset<64> ra);
void PopfromStack(bitset<64>ra);
void showStack();
