#include "breakpoints.h"
#include <iostream>

void addBreakPoint( int lineN){
    for( auto it = LineNumber.begin(); it != LineNumber.end(); it++){
      if(it->second == lineN){
        breakpoints.insert(it->first);
         std::cout<<"Breakpoint set at line "<<lineN<<endl;
        return;
      }
    }
    int lg=lineN;
    for( auto it = LineNumber.begin(); it != LineNumber.end(); it++){
      if(it->second > lineN){
        lg=it->second<lg?it->second:lg;
      }
    }
     for( auto it = LineNumber.begin(); it != LineNumber.end(); it++){
      if(it->second == lg){
        breakpoints.insert(it->first);
        std::cout<<"No Instruction at line number" <<lineN<<" So Breakpoint is setted at next nearest instruction at line number"<<lg<<endl;
        return;
      }
    }

}
void deleteBreakPoint(int lineN){
    for( auto it = LineNumber.begin(); it != LineNumber.end(); it++){
      if(it->second == lineN){
        if( breakpoints.find(it->first) != breakpoints.end()){
          breakpoints.erase(it->first);
          std::cout<<"Breakpoint deleted at line number "<<lineN<<endl;
        }else{
          std::cout<<"No Breakpoint to delete at line number "<<lineN<<endl;
        }
        return;
      }
    }
}
bool IsbreakPoint(int instr){
  if( breakpoints.find(instr) != breakpoints.end()){
    return true;
  }
  return false;
}