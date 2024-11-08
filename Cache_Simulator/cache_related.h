#pragma once

#include <bitset>
using namespace std;

struct CacheStatastics{
  unsigned int hits;
  unsigned int misses;

  int Accesses(){
    return hits+misses;
  }

  float hitRate(){
    return hits/Accesses();
  }

  void Reset(){
    hits=0;
    misses=0;
  }

};


bitset<64> readData(int n, unsigned int address){

  //check hit or miss


  // if hit 
    //read from cache


  // if miss
   // get the block from memory  
   //place it in cache
   // read from cache

}


void WriteData(int n,unsigned int  address, bitset<64> value){

  //check hit or miss 

  //if hit 
    //write it in cache

  //miss 
  // get the block from memory  
 //place it in cache check replacement policy && with allocate
  //write it in cache
  //write through write back 

}


