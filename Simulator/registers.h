#pragma once
#include<bitset>

using namespace std;

class RegisterFileClass{
  private:
  bitset<64> reg[32];
  public:
  RegisterFileClass();
  bitset<64> readReg(int n) const;
  void writeReg(int n, bitset<64> value);
  void printRegs()const;


};

