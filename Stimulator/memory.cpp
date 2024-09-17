#include "memory.h"



void textSection:: writeInstruction(string s) {
    if (mem.size() -top <= 4) {
      mem.resize(top + 4 * N, 0);
    }
    int j = 0;
    for (int i = 0; i < 4; i++, top++) {
      string s1;
      for (int k = 0; k < 2; j++, k++) {
        s1 += s[j];
      }
      int n = stoi(s1, 0, 16);
      mem[top] = n;
    }
  };

  bitset<32> textSection:: readInstruction(unsigned int pc){
    bitset<32> a=0;
    if(pc >= mem.size()){
      return a;
    }else{
      int k = 0;
      for (int i = 0; i < 4; i++, pc++) {
        for (int j = 0; j < 8; j++, k++) {
          a[k] = mem[pc][j];
        }
      }
    }
    return a;
  }

   // address is index
  void textSection:: writedata(int n, unsigned int address, bitset<64> value) {
    if (mem.size() -top <= n) {
      mem.resize(top + 4 * N, 0);
    }
    while(address+n-1 >= mem.size() ){
      mem.resize(address+n-1,0);
    }
    if(top<address+n){
      top=address;
    }
    int k = 0;
    for (int i = 0; i < n; i++, address++) {
      for (int j = 0; j < 8; j++, k++) {
        mem[address][j] = value[k];
      }
    }
  }

    bitset<64> textSection::readData(int n, unsigned int address) {
    bitset<64> a = 0;
    if(address >= mem.size()){
      return a;
    }else{
      int k = 0;
      for (int i = 0; i < n; i++, address++) {
        for (int j = 0; j < 8; j++, k++) {
          a[k] = mem[address][j];
        }
      }
    }
    return a;
  }

  // address is index
  void dataSection::writedata(int n, unsigned int address, bitset<64> value) {
    if (mem.size() -top <= n) {
      mem.resize(top + 4 * N, 0);
    }
    while(address+n-1 >= mem.size() ){
      mem.resize(address+n-1,0);
    }
    if(top<address+n){
      top=address;
    }
    int k = 0;
    for (int i = 0; i < n; i++, address++) {
      for (int j = 0; j < 8; j++, k++) {
        mem[address][j] = value[k];
      }
    }
  }

  void dataSection:: writedata(int n, unsigned int address, long int value) {
    bitset<64> a = value;
    writedata(n, address, a);
  }

    bitset<64> dataSection:: readData(int n, unsigned int address) {
    bitset<64> a = 0;
    if(address >= mem.size()){
      return a;
    }else{
      int k = 0;
      for (int i = 0; i < n; i++, address++) {
        for (int j = 0; j < 8; j++, k++) {
          a[k] = mem[address][j];
        }
      }
    }
    return a;
  }

   //adress is index
    void stackSection:: writedata(int n, unsigned int address, bitset<64> value) {
    if ( mem.size() -top <= n ) {
      mem.resize(top + 4 * N, 0);
    }
    while(address >= mem.size() ){
      mem.resize(address+1,0);
    }
    if(top<address+1){
      top=address+1;
    }
    int k = 0;
    for (int i = 0; i < n; i++, address--) {
      for (int j = 0; j < 8; j++, k++) {
        mem[address][j] = value[k];
      }
    }
  }

bitset<64>stackSection:: readData(int n ,unsigned int address){
     bitset<64> a = 0;
    if(address >= mem.size()){
      return a;
    }else{
      int k = 0;
      for (int i = 0; i < n; i++, address--) {
        for (int j = 0; j < 8; j++, k++) {
          a[k] = mem[address][j];
        }
      }
    }
    return a;
  }

    // bitset<64> Memory:: ReadData(int n, unsigned int address){
    //   if( address >=0 && address < 0x10000){
    //     return textSection.readData(n,address);
    //   }else if( address >= 0x10000 ){

    //   }else if( address <= 0x50000){

    //   }
    // };