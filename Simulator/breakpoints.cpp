#include "Execution.h"
#include "globalvars.h"
#include <iostream>

void addBreakPoint( int lineN){
    for( auto it = LineNumber.begin(); it != LineNumber.end(); it++){
      if(it->second == lineN){
        breakpoints.insert(it->first);
         std::cout<<"Breakpoint set at line "<<dec<<lineN<<endl;
        return;
      }
    }
    int lg=lineN+1;
    for( auto it = LineNumber.begin(); it != LineNumber.end(); it++){
      if(it->second > lineN){
        lg=it->second<lg?it->second:lg;
      }
    }
     for( auto it = LineNumber.begin(); it != LineNumber.end(); it++){
      if(it->second == lg){
        breakpoints.insert(it->first);
        std::cout<<"No Instruction at line number " <<dec<<lineN<<" So Breakpoint is set at next nearest instruction at line number "<<lg<<endl;
        return;
      }
    }

    cout<<"No Instruction at line number " <<dec<<lineN<<endl;

}
void deleteBreakPoint(int lineN){
    for( auto it = LineNumber.begin(); it != LineNumber.end(); it++){
      if(it->second == lineN){
        if( breakpoints.find(it->first) != breakpoints.end()){
          breakpoints.erase(it->first);
          std::cout<<"Breakpoint deleted at line number "<<dec<<lineN<<endl;
        }else{
          std::cout<<"No Breakpoint to delete at line number "<<dec<<lineN<<endl;
        }
        return;
      }
    }
    std::cout<<"No Breakpoint to delete at line number "<<dec<<lineN<<endl;
}
bool IsbreakPoint(int instr){
  if( breakpoints.find(instr) != breakpoints.end()){
    return true;
  }
  return false;
}

void showBreakpoints(){
  if(breakpoints.size()){
  cout<<"Break points are located at line numbers:";
  bool c=false;
  for( auto i : breakpoints){
    if(!c){
      c=true;
    }else{
      cout<<", ";
    }
    cout<<dec<<LineNumber[i];
    
  }
  }else{
    cout<<"No break points"<<endl;
  }
  cout<<endl;
}