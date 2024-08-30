#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

string Roperations[] = {"add", "sub", "xor", "or", "and", "sll", "srl", "sra"}; //8
string I1operations[] = {"addi", "xori", "ori", "andi", "slli", "srli", "srai"};//7
string I2operations[] = {"lb", "lh", "lw", "ld", "lbu", "lhu", "lwu", "jalr"};//8
string Soperations[] = {"sb", "sh", "sw", "sd"};//4
string Boperations[] = {"beq", "bne", "blt", "bge", "bltu", "bgeu"};//6
string Uoperations[] = {"lui", "auipc"};//2
string Joperations[] = {"jal"};//1
string Registers[] = {
    "x0", "zero", "x1", "ra",  "x2",  "x3",  "gp",  "x4", "tp",
    "x5", "t0",   "x6", "t1",  "x7",  "t2",  "x8",  "s0",  "fp", "x9",
    "s1", "x10",  "a0", "x11", "a1",  "x12", "a2",  "x13", "a3", "x14",
    "a4", "x15",  "a5", "x16", "a6",  "x17", "a7",  "x18", "s2", "x19",
    "s3", "x20",  "s4", "x21", "s5",  "x22", "s6",  "x23", "s7", "x24",
    "s8", "x25",  "s9", "x26", "s10", "x27", "s11", "x28", "t3", "x29",
    "t4", "x30",  "t5", "x31", "t6"}; //64

int getrand (int a){
  return abs(rand()%a);
}

string GenerateRType(){
  return ( Roperations[getrand(8)] + " " + Registers[getrand(64)]+" "+Registers[getrand(64)]+" "+Registers[getrand(64)]);
}
string GenerateI1Type(){
  return ( I1operations[getrand(7)] + " " + Registers[getrand(64)]+" "+Registers[getrand(64)]+" "+to_string(rand()%5000));
}
string GenerateI2Type(){
  return ( I2operations[getrand(8)] + " " + Registers[getrand(64)]+" "+to_string(rand()%5000)+"("+Registers[getrand(64)]+")");
}
string GenerateSType(){
  return ( Soperations[getrand(4)] + " " + Registers[getrand(64)]+" "+to_string(rand()%5000)+"("+Registers[getrand(64)]+")");
}

string GenerateUType(){
  return ( Uoperations[getrand(2)] + " " + Registers[getrand(64)]+" "+to_string(rand()%1000000000));
}

int main() {

  srand(time(0));

  fstream file("Rtestcases.s");
  if(file.is_open()){
      for(int i=0; i<100 ; i++){
    file<<GenerateRType()<<endl;
  }
  }else{
    cout<<"file not open"<<endl;
  }

  return 0;
}