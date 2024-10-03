#pragma once
#include <bitset>
#include <string>
#include <vector>
#define S 10

using namespace std;

class textSectionClass {
private:
  vector<bitset<8>> mem;
  

public:
  unsigned int top;
  textSectionClass() : top(0) { mem.assign(4 * S, 0); }
  void writeInstruction(string s);
  bitset<32> readInstruction(unsigned int pc);
  void writeData(int n, unsigned int address,
                 bitset<64> value); // address is index
  bitset<64> readData(int n, unsigned int address);
  void printMemmory()const;
  void printMemmory(int n , unsigned int address)const;
};

class dataSectionClass {
private:
  vector<bitset<8>> mem;
  unsigned int top;

public:
  dataSectionClass() : top(0) { mem.assign(4 * S, 0); }
  void writeData(int n, unsigned int address,
                 bitset<64> value); // address is index
  void writeData(int n, long int value);
  bitset<64> readData(int n, unsigned int address);
  void printMemmory(unsigned int start_address)const;
  void printMemmory(unsigned int start_address,int n , unsigned int address)const;
};

class stackSectionClass {
private:
  vector<bitset<8>> mem;
  unsigned int top;

public:
  stackSectionClass() : top(0) { mem.assign(4 * S, 0); }
  void writeData(int n, unsigned int address, bitset<64> value);
  bitset<64> readData(int n, unsigned int address);
  void printMemmory()const;
  void printMemmory(int n , unsigned int address)const;
};

class MemoryClass {
public:
  textSectionClass textSectionstart;
  dataSectionClass dataSectionstart;
  dataSectionClass dataSection2;
  dataSectionClass dataSection3;
  stackSectionClass stackSection;

public:
  MemoryClass(){

  };
  bitset<64> ReadData(int n, unsigned int address);
  void WriteData(int n, unsigned int address, bitset<64> value);
  void writeData(int n, long int value);
  void writeInstruction(string s);
  bitset<32> readInstruction(unsigned int pc);
  void printMemory()const;
  void printMemory( int n , unsigned int address);
};