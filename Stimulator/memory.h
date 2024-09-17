#pragma once
#include <bitset>
#include <string>
#include <vector>
#define N 100

using namespace std;

class textSection {
private:
  vector<bitset<8>> mem;
  unsigned int top;

public:
  textSection() : top(0) { mem.assign(4 * N, 0); }
  void writeInstruction(string s);
  bitset<32> readInstruction(unsigned int pc);
  void writedata(int n, unsigned int address, bitset<64> value) ; // address is index
  bitset<64> readData(int n, unsigned int address);
  
};

class dataSection {
private:
  vector<bitset<8>> mem;
  unsigned int top;

public:
  dataSection() : top(0) { mem.assign(4 * N, 0); }
  void writedata(int n, unsigned int address, bitset<64> value) ; // address is index
  void writedata(int n, unsigned int address, long int value) ;
  bitset<64> readData(int n, unsigned int address);
};

class stackSection{
  private:
  vector<bitset<8>> mem;
  unsigned int top;
  public:
  stackSection(): top(0) { mem.assign(4 * N, 0); }
  void writedata(int n, unsigned int address, bitset<64> value) ;
  bitset<64> readData(int n , unsigned int address);

};

class MemoryClass {
  public:
  textSection textSection;
  dataSection dataSection;
  stackSection stackSection;
  public:
  MemoryClass(){

  };
  bitset<64> ReadData(int n, unsigned int address);
  bitset<64> WriteData(int n , unsigned int address, bitset<64> value);



};

