#include<regex>
#include <fstream>
#include <string>
#include "globalvars.h"
using namespace std;


bool configDetails(string filename){
  ifstream inputfile(filename);
  int counter = 0;
  int cacheSize;
  string s;
  regex lru("\\s*[Ll][Rr][Uu]\\s*");
  regex lfu("\\s*[Ll][Ff][Uu]\\s*");
  regex fifo("\\s*[Ff][Ii][Ff][Oo]\\s*");
  regex random("\\s*[Rr][Aa][Nn][Dd][Oo][Mm]\\s*");
  regex wt("\\s*[Ww][Tt]\\s*");
  regex wb("\\s*[Ww][Bb]\\s*");
  int cacheSize, blocksize, associativity;
  ReplacementPolicy replacementPolicy;
  WritePolicy writePolicy;
  bool writeAllocate;

  if(inputfile.is_open()){
    while(inputfile.good()){
      getline(inputfile, s);
      if(s != ""){
        switch (counter){
          case 0:
            cacheSize = stoi(s);
            break;
          case 1:
            blocksize = stoi(s);
            break;
          case 2:
            associativity = stoi(s);
          case 3:
            if(regex_match(s, lru)){
              replacementPolicy = ReplacementPolicy::LRU;
            }
            else if(regex_match(s, lfu)){
              replacementPolicy = ReplacementPolicy::LFU;
            }
            else if(regex_match(s, fifo)){
              replacementPolicy = ReplacementPolicy::FIFO;
            }
            else if(regex_match(s, random)){
              replacementPolicy = ReplacementPolicy::RANDOM;
            }
            break;
          case 4:
            if(regex_match(s, wt)){
              writePolicy = WritePolicy::WT;
              writeAllocate = 0;
            }
            else if(regex_match(s, wb)){
              writePolicy = WritePolicy::WB;
              writeAllocate = 1;
            }
            break;
          }
        counter++;
      }
    }
    if(associativity != 0){
      cache = new Cache(cacheSize, associativity, blocksize, replacementPolicy, writePolicy, writeAllocate);
    }
    else{
      cache = new FullAssociativeCache(cacheSize, associativity, blocksize, replacementPolicy, writePolicy, writeAllocate);      
    }
    return true;
  }
  return false;
}

//access 0 read access 1 write
void addrAccess(string filename, bool access, unsigned int address, unsigned  int set, bool IsHit, unsigned int tag, bool IsDirty){
  fstream outfile(filename, ios::app);
  if(outfile.is_open()){
    outfile<<(access?"W":"R")<<": Address: 0x"<<hex<<address<<", Set: 0x"<<hex<<set<<", "<<(IsHit?"Hit":"Miss")<<", Tag: 0x"<<tag<<hex<<", "<<(IsDirty?"Dirty":"Clean")<<endl;
  }
}
