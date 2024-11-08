#pragma once

#include <bitset>
#include <map>
#include <vector>
using namespace std;

enum class ReplacementPolicy { FIFO, LRU, RANDOM };
enum class WritePolicy { WT, WB };


struct AccessDetails{
  int frequency;
  int last_access;
  int first_access;

  AccessDetails(){
    frequency=0;
    first_access=-1;
    last_access=-1;
  }
};

struct Block {
  bitset<8> *blockdata;
  AccessDetails accessDetails;

  Block() {}
  Block(int blocksize) { blockdata = new bitset<8>[blocksize]; }
};

struct Set {
  Block *set;

  Set(){}
  Set(int associativity, int blocksize) {
    set = new Block[associativity];
    for (int i = 0; i < associativity; i++) {
      Block b(blocksize);
      set[i] = b;
    }
  }
};

class Cache {

private:
struct cacheData{
  Set set;
  bool validBit;
  bool dirtyBit;
  unsigned int tag;

  cacheData(int associativity, int blocksize){
    set=Set(associativity,  blocksize);
    dirtyBit=false;
    validBit=false;//true
  }

};
  map<unsigned int, cacheData> cache;
  ReplacementPolicy replacementPolicy;
  WritePolicy writePolicy;
  bool writeAllocate;
  unsigned int noOfEntries;
  int associativity;
  int blocksize;

public:
  Cache() {}

  Cache(int cacheSize, int associativity, int blocksize, ReplacementPolicy replacementPolicy, WritePolicy writePolicy,bool writeAllocate)
      : associativity(associativity), blocksize(blocksize),replacementPolicy(replacementPolicy),writePolicy(writePolicy),writeAllocate(writeAllocate){
        noOfEntries=cacheSize /(blocksize * associativity);
      }

  void AddEntry(unsigned int address  ){
   // index=address<<offset % no_of_entries
   // cache[index] =  Cachedata((associativity,blocksize));
   //

  }
};


bitset<64> ReadData(int n , unsigned int address){

  //hit or miss
  //k=address/blocksize
  //index=k%no_of_entries
  //tag=k/no_of_entries





  //hit

  //miss


}

