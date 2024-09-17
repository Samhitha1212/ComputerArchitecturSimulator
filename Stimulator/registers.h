#pragma once
#include<bitset>

using namespace std;

class RegisterFileClass {
  private:
  bitset<64> reg[32];
  public:
  RegisterFileClass(){
    for (int i=0; i<32 ;i++){
      reg[i]=0;
    }
  }
  bitset<64> readReg(int n) const {
    return reg[n];
  }
  void writeReg(int n, bitset<64> value){
    if(n > 0 && n <32){
      reg[n]=value;
    }
  }

};

