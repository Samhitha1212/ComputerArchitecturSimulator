#include "globalvars.h"
#include "loadfile.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
  string input;

  do{
    getline(cin, input);

    if(input =="load input.s"){
        loadfile("input.s");
    }



  }while(input != "exit");

  cout<<"Exiting the stimulator"<<endl;
  return 0;
}