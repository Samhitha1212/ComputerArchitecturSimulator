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
    float hitrate=float(hits)/Accesses();
    return hitrate;
  }

  void Reset(){
    hits=0;
    misses=0;
  }

  void Print(){
    std::cout.precision(4);
    std::cout<<"D-cache statistics: Accesses="<<Accesses()<<", Hit="<<hits<<", Miss="<<misses<<", Hit Rate="<<hitRate()<<endl;
  }

};


bitset<64> ReadData(int n, unsigned int address);
void WriteData(int n,unsigned int  address, bitset<64> value);

