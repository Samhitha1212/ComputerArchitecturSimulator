#include "registers.h"
#include <iostream>

 RegisterFileClass:: RegisterFileClass(){
    for (int i=0; i<32 ;i++){
      reg[i] = 0;
    }
  }
  bitset<64> RegisterFileClass:: readReg(int n) const{
    return reg[n];
  }
  void RegisterFileClass:: writeReg(int n, bitset<64> value){
    if(n > 0 && n <32){
      reg[n] = value;
    }
  }

   void RegisterFileClass:: printRegs()const{
    cout<<"Registers:"<<endl;
    int i=0;
    for(; i<10;i++){
      cout<<"x"<<dec<<i;
      cout<<"  = 0x"<<hex<<reg[i].to_ulong()<<endl;
    }
     for(; i<32;i++){
      cout<<"x"<<dec<<i;
      cout<<" = 0x"<<hex<<reg[i].to_ulong()<<endl;
    }
    cout<<endl;

   }