#include "cache.h"
#include <random>
#include <time.h>
#include <iostream>
#include <fstream>


Hitdetails FullAssociativeCache:: HitOrMiss(unsigned int address,int n)const {
  // check whether it belongs to same block or not
  unsigned int reqaddress = address / blocksize;
  unsigned int reqaddress2 = (address+n-1) / blocksize;
  if(reqaddress2 != reqaddress){
    cout<<"Memory access to cache is not in same block"<<endl;
    return {false,false, 0, 0};
  }

  unsigned int tag = reqaddress;
  for( unsigned int i=0;i<cache.size();i++){
    if(cache[i].validBit && cache[i].tag==tag){
      return {true,true,i, 0}; //hit
    }
  }
  //miss
   return {false,true, 0, 0};

}
Block FullAssociativeCache::getBlock(unsigned int address, MemoryClass& Memory,unsigned int Timer)const {
    Block b(blocksize);
    b.tag=(address/blocksize);
    b.validBit=true;
    b.accessDetails.first_access=Timer;
    b.accessDetails.last_access=Timer;
    b.accessDetails.frequency=1;

    for( int i=0; i<blocksize;i++){
      b.blockdata[i]=Memory.ReadByte(address+i);
    }

    return b;

}
unsigned int FullAssociativeCache:: AddEntry(unsigned int address ,MemoryClass& Memory, unsigned int Timer ) {
  unsigned int tag=(address/blocksize);
  Block b=getBlock(tag*blocksize,Memory,Timer);

  unsigned int block_index;
  if(cache.size() < noOfEntries){
    block_index=cache.size();
    cache.push_back(b);
  }else{ //need to replace existing block
    block_index=FindIndexForReplacement();
    Block victim = cache[block_index];
    if(victim.dirtyBit){
      writeBlock(block_index, victim.tag*blocksize, Memory);
    }
    if( victim.validBit){
     delete [] victim.blockdata;
    }
    cache[block_index]=b;
  }

  return block_index;

}
bitset<64> FullAssociativeCache:: LoadDataFromCache(int n , unsigned int address ,unsigned int block_index )const {
   bitset<64> data=0;
   Block b=cache[block_index];
   int dataindex=address%blocksize;
   for(int i=0;i<n;i++){
      bitset<8> byte= b.blockdata[dataindex+i];
    for(int j=0 ; j<8;j++){
      data[i*8+j]= byte[j];
    }
   }
    return data;

}
void FullAssociativeCache:: writeDataToCache(int n, unsigned int address, bitset<64> value, unsigned int block_index){
  Block b = cache[block_index];
  for(int i =0; i<n; i++){
    for(int j=0; j<8; j++){
      b.blockdata[i+address%blocksize][j] = value[8*i+j];
    }
  }

  if(writePolicy == WritePolicy::WB){
    cache[block_index].dirtyBit = 1;
  }
}

void FullAssociativeCache::updateDetails(unsigned int block_index, unsigned int Timer){
  cache[block_index].accessDetails.frequency++;
  cache[block_index].accessDetails.last_access = Timer;
}

void FullAssociativeCache::writeBlock(unsigned int block_index, unsigned int start_address, MemoryClass& Memory){
  Block b = cache[block_index];
  for(int i=0; i<blocksize; i++){
    Memory.WriteByte(start_address+i, b.blockdata[i]);
  }
}

bool FullAssociativeCache::IsDirtyBlock(unsigned int cache_index, unsigned int set_index){
  bool dirty = cache[cache_index].dirtyBit;
  return dirty;
}

unsigned int FullAssociativeCache:: FindIndexForReplacement()const {

  unsigned int k=0;
    switch (replacementPolicy)
    {
    case ReplacementPolicy::RANDOM:
      srand(time(0));
      return rand()%noOfEntries;
      break;
    case ReplacementPolicy::LRU:
      
      for( int i=0; i<noOfEntries;i++){
        if(cache[k].accessDetails.last_access > cache[i].accessDetails.last_access){
          k=i;
        }
      }
      return k;
     
      break;
    case ReplacementPolicy::LFU:
    for( int i=0; i<noOfEntries;i++){
        if(cache[k].accessDetails.frequency > cache[i].accessDetails.frequency){
          k=i;
        }
      }
      return k;
     
      break;
    case ReplacementPolicy::FIFO:
      for( int i=0; i<noOfEntries;i++){
        if(cache[k].accessDetails.first_access > cache[i].accessDetails.first_access){
          k=i;
        }
      }
      return k;
     
      break;
    default:
      srand(time(0));
      return rand()%noOfEntries;
      break;
    }


}

FullAssociativeCache::~FullAssociativeCache(){
  for(auto block:cache){
    if(block.validBit){
       delete[] block.blockdata;
    }
  }
}

void FullAssociativeCache::InvalidateCacheEntries() {
   for(auto block:cache){
    if(block.validBit){
       delete[] block.blockdata;
    }
   }
    cache.clear();
}

bool FullAssociativeCache::dumpFile(string filename){
  fstream outputfile(filename, ios::trunc | ios::in | ios::out);
  if(outputfile.is_open()){
    for(auto block: cache){
      if(block.validBit){
        outputfile<<"Set: 0x00"<<", Tag: 0x"<<hex<<block.tag<<", "<<(block.dirtyBit?"Dirty":"Clean")<<endl;
      }
    }
    return true;
  }
  return false;
}
void FullAssociativeCache:: writeDirtyBlocks(MemoryClass& Memory) {
  for(int i=0; i<cache.size();i++){
      if(cache[i].dirtyBit){
        writeBlock( i, cache[i].tag*blocksize , Memory );
        cache[i].dirtyBit=false;
      }
   }
}

