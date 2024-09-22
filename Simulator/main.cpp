#include "globalvars.h"
#include "loadfile.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
  string input;

  // do{
    // getline(cin, input);

    // if(input =="load input.s"){
    //     loadfile("input.s");
    // }



  // }while(input != "exit");

  
  loadfile("input.s");
  Memory.WriteData( 8,0x10000,12653 );
  RegisterFile.printRegs();
  Memory.printMemory();
   


  cout<<"Exiting the stimulator"<<endl;
  return 0;
}