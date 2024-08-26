#include <bitset>
#include <string>
#include "FMT.h"
using namespace std;

void arrangeopcode(bitset<32> & Instruction ,bitset<7>  a){
  for (int i=0,j=25 ; i <7; i++,j++){
    Instruction[j]=a[i];
  }
}
void arrangefunct3(bitset<32> & Instruction ,bitset<3>  a){
  for (int i=0,j=17 ; i <3; i++,j++){
    Instruction[j]=a[i];
  }
}
void arrangefunct7(bitset<32> & Instruction ,bitset<7>  a){
  for (int i=0,j=0 ; i <7; i++,j++){
    Instruction[j]=a[i];
  }
}
void arrangefunct6(bitset<32> & Instruction ,bitset<7>  a){
  for (int i=1,j=0 ; i <6; i++,j++){
    Instruction[j]=a[i];
  }
}

void arrangeregister(bitset<32> & Instruction ,bitset<5> a, int j){
  for (int i=0 ; i <5; i++,j++){
    Instruction[j]=a[i];
  }
}
char gethex(string);
void Evaluatehexcode(string & hexcode, bitset<32> & Instruction){
  hexcode="";
  int n=0;
  for(int i=0 ; i<8; i++){
    string b="";
    for(int j=0; j<4;j++,n++){
      b+=char(Instruction[n]); //returns 1 or 0 char
    }
    b="rs2";
    char c= gethex(b);
    hexcode+=c;
  }

}

void  RType::EvaluateInstruction(){

}