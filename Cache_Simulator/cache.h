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

class CacheInterface{
  public:
  ReplacementPolicy replacementPolicy;
  WritePolicy writePolicy;
  bool writeAllocate;
  unsigned int blocksize;
  unsigned int noOfEntries;
  unsigned int associativity;

  virtual Hitdetails HitOrMiss(unsigned int address,int n) const=0;
  virtual Block getBlock(unsigned int address, MemoryClass Memory,unsigned int Timer)const=0;
  virtual unsigned int AddEntry(unsigned int address ,MemoryClass Memory, unsigned int Timer )=0;
  virtual bitset<64> LoadDataFromCache(int n , unsigned int address ,unsigned int cache_index , unsigned char set_index ) const {return 0;};
  virtual bitset<64> LoadDataFromCache(int n , unsigned int address ,unsigned int block_index ) const{return 0;} ;



};

class Cache :public CacheInterface {

public:

  map<unsigned int, Set> cache;
  

public:
  Cache() {}

  Cache(int cacheSize, int associativity,int blocksize, ReplacementPolicy replacementPolicy, WritePolicy writePolicy,bool writeAllocate)
       {
       
        this->blocksize=blocksize;
        this->associativity=associativity;
        this->replacementPolicy=replacementPolicy;
        this->writePolicy=writePolicy;
        this->writeAllocate=writeAllocate;
        if(associativity !=0){
          noOfEntries=cacheSize /(blocksize * associativity);
        }
      }

  Hitdetails HitOrMiss(unsigned int address,int n)const override;
  Block getBlock(unsigned int address, MemoryClass Memory,unsigned int Timer)const override;
  unsigned int AddEntry(unsigned int address ,MemoryClass Memory, unsigned int Timer ) override;
  bitset<64> LoadDataFromCache(int n , unsigned int address ,unsigned int cache_index , unsigned char set_index )const override;
  unsigned char FindIndexForReplacement(unsigned int cache_index)const ;

};

class FullAssociativeCache: public CacheInterface{
  public:
  vector<Block> cache;

  FullAssociativeCache(){}
    FullAssociativeCache(int cacheSize, int associativity,int blocksize, ReplacementPolicy replacementPolicy, WritePolicy writePolicy,bool writeAllocate)
       {
        this->blocksize=blocksize;
        this->associativity=associativity;
        this->replacementPolicy=replacementPolicy;
        this->writePolicy=writePolicy;
        this->writeAllocate=writeAllocate;
        noOfEntries=cacheSize/(blocksize);
      }
    
    Hitdetails HitOrMiss(unsigned int address,int n)const override;
    Block getBlock(unsigned int address, MemoryClass Memory,unsigned int Timer)const override;
    unsigned int AddEntry(unsigned int address ,MemoryClass Memory, unsigned int Timer ) override;
    virtual bitset<64> LoadDataFromCache(int n , unsigned int address ,unsigned int block_index ) const override;
    unsigned int FindIndexForReplacement()const ;

  
};




