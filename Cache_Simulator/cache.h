#pragma once
#include "memory.h"
#include <bitset>
#include <map>
#include <vector>
using namespace std;

enum class ReplacementPolicy { FIFO, LRU, RANDOM,LFU };
enum class WritePolicy { WT, WB };

struct Hitdetails{ 
    bool IsHit;
    bool IsSingleblock;
    unsigned int cache_index;
    unsigned char set_index;
};

struct AccessDetails{
  unsigned int frequency;
  unsigned int last_access;
  unsigned int first_access;
  AccessDetails():frequency(0),first_access(-1),last_access(-1){};
};

struct Block {
  bitset<8> *blockdata;
  AccessDetails accessDetails;
  bool validBit;
  bool dirtyBit;
  unsigned int tag;

  Block():dirtyBit(false),validBit(false) { };
  Block(int blocksize):dirtyBit(false),validBit(false) ,tag(0){
     blockdata = new bitset<8>[blocksize];
  }
};

struct Set {
  Block *set;
  Set(){}
  Set(int associativity) {
    set = new Block[associativity];
  }
};

class Cache {

public:

  map<unsigned int, Set> cache;
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


  Hitdetails HitOrMiss(unsigned int address , int n);
  Block getBlock(unsigned int address, MemoryClass Memory,unsigned int Timer);
  unsigned char AddEntry(unsigned int address ,MemoryClass Memory, unsigned int Timer );
  bitset<64> LoadDataFromCache(int n , unsigned int address ,unsigned int cache_index , unsigned char set_index );
  unsigned char FindIndexForReplacement(unsigned int cache_index);

};




