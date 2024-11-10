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
      if(cache->associativity){
        cache->updateDetails(h.cache_index, h.set_index, Timer);
      }else{
        cache->updateDetails(h.cache_index, Timer);
      }
    }
   //now read data from appropriate block and send bitset<64>
    if(cache->associativity){
      return cache->LoadDataFromCache(n,address,h.cache_index,h.set_index);
      }else{
       return cache->LoadDataFromCache(n,address,h.cache_index);
    }
  }

  void WriteData(int n, unsigned int address, bitset<64> value){
    Hitdetails h = cache->HitOrMiss(address, n);
    unsigned int start_address= (address/cache->blocksize)*cache->blocksize;
    
    if(h.IsSingleblock){
      if(h.IsHit == false){
        if(cache->writeAllocate == false){
          Memory.WriteData(n, address, value);
          cacheStatastics.misses++;
          return ;
        }
        else{
          if(cache->associativity){
            h.set_index = cache->AddEntry(address,Memory,Timer);
          }else{
            h.cache_index = cache->AddEntry(address,Memory,Timer);
          } 
        }
        cacheStatastics.misses++;
      }else{
        cacheStatastics.hits++; 
        if(cache->associativity){
          cache->updateDetails(h.cache_index, h.set_index, Timer);
        }else{
          cache->updateDetails(h.cache_index, Timer);
        }
      }

      if(cache->associativity){
        cache->writeDataToCache(n, address, value, h.cache_index, h.set_index);
      }else{
        cache->writeDataToCache(n, address, value, h.cache_index);
      }
      

        if(cache->writePolicy == WritePolicy::WT){
          if(cache->associativity){
            cache->writeBlock(h.cache_index, h.set_index, start_address, Memory);
          }
          else{
            cache->writeBlock(h.cache_index,start_address, Memory);
          }
        }
    }
    else{
      Memory.WriteData(n, address, value);
    }
  }


