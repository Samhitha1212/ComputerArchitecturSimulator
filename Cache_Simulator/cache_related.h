#pragma once
#include<iostream>
#include <bitset>
#include <iomanip>
using namespace std;

struct CacheStatastics{
  unsigned int hits;
  unsigned int misses;

  int Accesses(){
    return hits+misses;
  }

  float hitRate(){
    float hitrate;
    if(Accesses()){
      hitrate=float(hits)/Accesses();
    }else{
      hitrate=-1;
    }
   
    return hitrate;
  }

  void Reset(){
    hits=0;
    misses=0;
  }

  void Print(){
    std::cout.precision(2);
    std::cout<<"D-cache statistics: Accesses="<<dec<<Accesses()<<dec<<", Hit="<<dec<<hits<<dec<<", Miss="<<dec<<misses;
    if(Accesses()){
     cout<<", Hit Rate="<<hitRate();
    }
    cout<<endl;
  }

};


bitset<64> ReadData(int n, unsigned int address);
void WriteData(int n,unsigned int  address, bitset<64> value);

bool configDetails(string filename);
void addrAccess(string filename, bool access, unsigned int address, unsigned  int set, bool IsHit, unsigned int tag, bool IsDirty);

