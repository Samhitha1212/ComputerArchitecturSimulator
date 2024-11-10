#include "cache.h"
#include <random>
#include <time.h>
#include <iostream>


Hitdetails FullAssociativeCache:: HitOrMiss(unsigned int address,int n)const {
  // check whether it belongs to same block or not
  unsigned int reqaddress = address / blocksize;
  unsigned int reqaddress2 = (address+n-1) / blocksize;
  if(reqaddress2 != reqaddress){
    cout<<"Memory access to cache is not in same block"<<endl;
    return {false,false};
  }

  unsigned int tag = reqaddress;
  for( unsigned int i=0;i<cache.size();i++){
    if(cache[i].validBit && cache[i].tag==tag){
      return {true,true,i}; //hit
    }
  }
  //miss
   return {false,true};

}
Block FullAssociativeCache::getBlock(unsigned int address, MemoryClass Memory,unsigned int Timer)const {
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
unsigned int FullAssociativeCache:: AddEntry(unsigned int address ,MemoryClass Memory, unsigned int Timer ) {
  unsigned int tag=(address/blocksize);
  Block b=getBlock(tag*blocksize,Memory,Timer);

  unsigned int block_index;
  if(cache.size() < noOfEntries){
    block_index=cache.size();
    cache.push_back(b);
  }else{ //need to replace existing block
    block_index=FindIndexForReplacement();
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
      data[i]= byte[j];
    }
   }
    return data;

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

