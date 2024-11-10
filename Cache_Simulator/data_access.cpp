#include "globalvars.h"
#include <bitset>
#include <iostream>
#include "cache_related.h"

using namespace std;



bitset<64> ReadData(int n, unsigned int address) {
    Hitdetails h = cache->HitOrMiss(address,n);
    if(!h.IsSingleblock){
      return Memory.ReadData(n,address);
    }
    if( !h.IsHit){  // miss 
    //Add block
      cacheStatastics.misses++;
      if(cache->associativity){
        h.set_index=cache->AddEntry(address,Memory,Timer);
      }else{
         h.cache_index=cache->AddEntry(address,Memory,Timer);
      }
    }else{
      cacheStatastics.hits++;
    }
   //now read data from appropriate block and send bitset<64>
    if(cache->associativity){
      return cache->LoadDataFromCache(n,address,h.cache_index,h.set_index);
      }else{
       return cache->LoadDataFromCache(n,address,h.cache_index);
    }

}