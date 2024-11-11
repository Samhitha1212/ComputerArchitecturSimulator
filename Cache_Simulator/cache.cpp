#include "cache.h"
#include <random>
#include <time.h>
#include <iostream>

using namespace std;

Hitdetails Cache::HitOrMiss(unsigned int address,int n)const{
   // check whether it belongs to same block or not
  unsigned int reqaddress = address / blocksize;
  unsigned int reqaddress2 = (address+n-1) / blocksize;
  if(reqaddress2 != reqaddress){
    cout<<"Memory access to cache is not in same block"<<endl;
    return {false,false};
  }
  unsigned int index = reqaddress % noOfEntries;
  unsigned int tag = reqaddress / noOfEntries;

  if(cache.find(index) == cache.end()){
     return {false,true,index,0};
  }else{
    //if associativity ==0
    for (unsigned int i=0; i<associativity; i++){
      Block b=cache.at(index).set[i];
      if(b.validBit && b.tag==tag){
        //hit
        return {true,true,index,i};
      }
    }
    //miss
    return {false,true,index,0};

  }

}

  Block Cache:: getBlock(unsigned int address, MemoryClass Memory,unsigned int Timer) const{
    Block b(blocksize);
    b.tag=(address/blocksize)/noOfEntries;
    b.validBit=true;
    b.accessDetails.first_access=Timer;
    b.accessDetails.last_access=Timer;
    b.accessDetails.frequency=1;

    for( int i=0; i<blocksize;i++){
      b.blockdata[i]=Memory.ReadByte(address+i);
    }

    return b;
  }

  unsigned int Cache::AddEntry(unsigned int address ,MemoryClass Memory, unsigned int Timer ){ //miss
   // index=address<<offset % no_of_entries
   unsigned int reqaddress=(address/blocksize);
   unsigned int index= reqaddress%noOfEntries;
   if(cache.find(index) == cache.end()){ //if set not exist
    //creating a new Set
    Set set(associativity);
    cache[index]=set;
   }
   // get block from Memory
   Block b = getBlock(reqaddress*blocksize,Memory,Timer);
  unsigned int set_index = FindIndexForReplacement(index);
  Block victim = cache[index].set[set_index];
  if(victim.dirtyBit){
    writeBlock(index, set_index, reqaddress*blocksize, Memory);
  }
  if( victim.validBit){
     delete [] victim.blockdata;
  }
 
  *(cache[index].set + set_index)=b;
  return set_index;

  }

  bitset<64> Cache::LoadDataFromCache(int n , unsigned int address ,unsigned int cache_index , unsigned char set_index )const{
   //read n bytres from the block
   bitset<64> data=0;
   Block b=cache.at(cache_index).set[set_index];
   int dataindex=address%blocksize;
   for(int i=0;i<n;i++){
      bitset<8> byte= b.blockdata[dataindex+i];
    for(int j=0 ; j<8;j++){
      data[i]= byte[j];
    }
   }
    return data;
  }

  unsigned int Cache::FindIndexForReplacement(unsigned int cache_index)const{
    Set s=cache.at(cache_index);
    if(associativity==0){
        return 0;
    }

    for( int i=0; i<associativity;i++){
      if(!s.set[i].validBit){
        return i;
      }
    }
    unsigned int k=0;
    switch (replacementPolicy){
    case ReplacementPolicy::RANDOM:
      srand(time(0));
      return rand()%associativity;
      break;
    case ReplacementPolicy::LRU:
      
      for( int i=0; i<associativity;i++){
        if(s.set[k].accessDetails.last_access > s.set[i].accessDetails.last_access){
          k=i;
        }
      }
      return k;
     
      break;
    case ReplacementPolicy::LFU:
    for( int i=0; i<associativity;i++){
        if(s.set[k].accessDetails.frequency > s.set[i].accessDetails.frequency){
          k=i;
        }
      }
      return k;
     
      break;
    case ReplacementPolicy::FIFO:
      for( int i=0; i<associativity;i++){
        if(s.set[k].accessDetails.first_access > s.set[i].accessDetails.first_access){
          k=i;
        }
      }
      return k;
     
      break;
    default:
      srand(time(0));
      return rand()%associativity;
      break;
    }

  }

  void Cache::writeDataToCache(int n, unsigned int address, bitset<64> value, unsigned int cache_index, unsigned int set_index){
   Block b=cache[cache_index].set[set_index];
    for(int i =0; i<n; i++){
      for(int j=0; j<8; j++){
        b.blockdata[i+address%blocksize][j] = value[j];
      }
    }

    if(writePolicy == WritePolicy::WB){
      cache[cache_index].set[set_index].dirtyBit = 1;
    }
  }

  void Cache::updateDetails(unsigned int cache_index, unsigned int set_index, unsigned int Timer){
    cache[cache_index].set[set_index].accessDetails.last_access=Timer;
    cache[cache_index].set[set_index].accessDetails.frequency++;
  }

  void Cache::writeBlock(unsigned int cache_index,  unsigned int set_index, unsigned int start_address, MemoryClass Memory){
    Block b = cache[cache_index].set[set_index];
    for(int i=0; i<blocksize; i++){
      Memory.WriteByte(start_address, b.blockdata[i]);
    }
  }


Cache::~Cache(){

  for( auto it: cache){
    for( int i=0;i<associativity;i++){
      if( it.second.set[i].validBit){
        delete [] it.second.set[i].blockdata;
      }
    }
    delete [] it.second.set;
  }

}

void Cache::InvalidateCacheEntries() {
   for( auto it: cache){
    for( int i=0;i<associativity;i++){
      if( it.second.set[i].validBit){
        delete [] it.second.set[i].blockdata;
      }
    }
    delete [] it.second.set;
  }

  cache.clear();

}

void Cache:: writeDirtyBlocks(MemoryClass Memory) {
  for( auto it: cache){
    for( int i=0;i<associativity;i++){
      if(it.second.set[i].dirtyBit){
        writeBlock(it.first,i,(it.second.set[i].tag*noOfEntries+it.first)*blocksize,Memory);
      }
    }
  }
}

unsigned int CacheInterface::CacheSize(){
    if(associativity){
      return noOfEntries*associativity*blocksize;
    }else{
      return noOfEntries*blocksize;
    }

}

 void CacheInterface::PrintCacheConfig(){

  cout<<"Cache Size: "<<dec<<CacheSize()<<endl;
  cout<<"Block Size: "<<dec<<blocksize<<endl;
  cout<<"Associativity Size: "<<dec<<associativity<<endl;
  cout<<"Replacement Policy: "<<getReplacementPolicy[replacementPolicy]<<endl;
  cout<<"Write Back Policy: "<<getWritePolicy[writePolicy]<<endl;  

 }