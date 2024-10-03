#include "Execution.h"
#include "globalvars.h"
#include <iostream>


void PushIntoStack(string label,int line,bitset<64> ra){
  StackDetails s;
  s.line=line;
  s.name=label;
  s.ra=ra;
  functionStack.push_back(s);
}

void PopfromStack(bitset<64>ra){
  if(functionStack.back().ra==ra){
    functionStack.pop_back();
  }
}

void showStack(){
  if(functionStack.size()){
    cout<<"Call Stack:"<<endl;
      for( auto x:functionStack){
    std::cout<<x.name<<":"<<dec<<x.line<<endl;
  }
  }else{
    if(IsFileloaded){
      cout<<"Empty Call Stack: Execution Complete"<<endl;
    }else{
      cout<<"Empty Call Stack: No file loaded"<<endl;
    } 
  }
}