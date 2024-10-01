#include "globalvars.h"
#include "loadfile.h"
#include "Execution.h"
#include "operation_map.h"
#include "ErrorHandling.h"
#include "breakpoints.h"
#include <iostream>
#include <string>
#include<regex>

using namespace std;

int main(){
  string input;
  int instructions;

  do{
    getline(cin, input);
    regex load("load\\s+(.*)");
    smatch match;
    regex breakpoint("break\\s+[0-9]+");
    regex delBreakpoint("del\\s+break\\s+[0-9]+");
    regex memory(R"(mem\s*(0x[0-9A-Fa-f]+|\d+)\s*(\d+))");
    if(regex_match(input, match, load)){
      loadfile(match[2]);
    }
    else if(regex_match(input, match, breakpoint)){
      addBreakPoint(stoi(match[2]));
    }
    else if(regex_match(input, match, delBreakpoint)){
      deleteBreakPoint(stoi(match[2]));
    }
    else if(input == "run"){
      for(int i = 0; i < instructions; i++){
        ExecuteInstruction(i);
      }
    }
    else if(input == "step"){}
    else if(regex_match(input, match, memory)){
      Memory.printMemory(stoi(match[2]), convertToInt(match[1]));
    }
    else if(input == "regs"){
      RegisterFile.printRegs();
    }
    else if(input == "show-stack"){}

  }while(input != "exit");

  
  loadfile("input.s");
  Memory.WriteData( 8,0x10000,12653 );

  Memory.printMemory();
   


  cout<<"Exiting the stimulator"<<endl;
  return 0;
}