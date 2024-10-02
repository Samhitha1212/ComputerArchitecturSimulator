#include "globalvars.h"
#include "loadfile.h"
#include "Execution.h"
#include "operation_map.h"
#include "ErrorHandling.h"
#include "breakpoints.h"
#include "StackDetails.h"
#include <iostream>
#include <string>
#include<regex>

using namespace std;

int main(){
  string input;

  do{
    getline(cin, input);
    regex load("load\\s+(.*)");
    smatch match;
    regex breakpoint("break\\s+[0-9]+");
    regex delBreakpoint("del\\s+break\\s+[0-9]+");
    regex memory(R"(mem\s*(0x[0-9A-Fa-f]+|\d+)\s*(\d+))");
    if(regex_match(input, match, load)){
      InitializeTotalData();
      loadfile(match[1]);
      if(loadfile(match[1])){
        cout<<"Error in the file "<<match[1]<<" : File not loaded"<<endl;
        InitializeTotalData();
      }
      else{
        IsFileloaded = true;
      }
      cout<<endl;
    }
    else if(regex_match(input, match, breakpoint)){
      if(IsFileloaded){
        string s;
        int i=0;
        for( ; i< input.length(); i++){
          if(input[i] != ' '){
            do{
              i++;
            }while(i<input.length() && input[i] != ' '  );
            i++;
            break;
          }
        }
        for( ; i< input.length(); i++){
          if(input[i]>='0' && input[i]<= '9'){
            do{
              s+=input[i];
              i++;
            }while(i<input.length() && input[i]>='0' && input[i]<= '9' );
            break;
          }
        }
      
        addBreakPoint(stoi(s));
      }else {
        cout<<"ERROR : No file loaded"<<endl;
      }
      cout<<endl;
    }
    else if(regex_match(input, match, delBreakpoint)){
      if(IsFileloaded){
        string s;
        int i=0;
        for( ; i< input.length(); i++){
          if(input[i] != ' '){
            do{
              i++;
            }while(i<input.length() && input[i] != ' '  );
            i++;
            break;
          }
        }
        for( ; i< input.length(); i++){
          if(input[i] != ' '){
            do{
              i++;
            }while(i<input.length() && input[i] != ' '  );
            i++;
            break;
          }
        }
        for( ; i< input.length(); i++){
          if(input[i]>='0' && input[i]<= '9'){
            do{
              s+=input[i];
              i++;
            }while(i<input.length() && input[i]>='0' && input[i]<= '9'  );
            break;
          }
        }
        deleteBreakPoint(stoi(s));
      }else{
        cout<<"ERROR : No file loaded"<<endl;
      }
      cout<<endl;
    }
    else if(input == "run"){
      if(IsFileloaded){
        if(currentInstruction<instructions){
          for(; !IsbreakPoint(currentInstruction) && currentInstruction < instructions ; ){
            ExecuteInstruction(currentInstruction);
          }
          if(currentInstruction >= instructions){
            cout<<"Execution Completed"<<endl;
            functionStack.clear();
          }else{
            cout<<"Execution stopped at Break point"<<endl;
          }
        }else{
          cout<<"Nothing to run"<<endl;
          cout<<"Execution Completed"<<endl;
        }
      }
      else{
        cout<<"ERROR : No file loaded"<<endl;
      }
      cout<<endl;
    }
    else if(input == "step"){
      if(IsFileloaded){
        if(currentInstruction<instructions){
          ExecuteInstruction(currentInstruction);
          if(currentInstruction>instructions){
            cout<<"Execution Completed"<<endl;
            functionStack.clear();
          }
        }else{
          cout<<"Nothing to step"<<endl;
          cout<<"Execution Completed"<<endl;
        }
      }
      else{
        cout<<"ERROR : No file loaded"<<endl;
      }
      cout<<endl;  
    }
    else if(regex_match(input, match, memory)){
      Memory.printMemory(stoi(match[2]), convertToInt(match[1]));
      cout<<endl;
    }else if(input=="show memory"){
      Memory.printMemory();
    }
    else if(input == "regs"){
      RegisterFile.printRegs();
    }else if(input == "show-stack"){
      showStack();
      cout<<endl;
    }else if(input == "show break points"){
      showBreakpoints();
    }
    else{
      cout<<"Invalid command"<<endl;
      cout<<endl;
    }

  }while(input != "exit");

  cout<<"Exiting the stimulator"<<endl;
  return 0;
}