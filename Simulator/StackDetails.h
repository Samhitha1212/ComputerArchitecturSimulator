#pragma once
#include <string>
#include <bitset>
using namespace std;

struct StackDetails {
  string name;
  int line;
  bitset<64> ra;
};

void PushIntoStack(string label,int line, bitset<64> ra);
void PopfromStack(bitset<64>);
void showStack();