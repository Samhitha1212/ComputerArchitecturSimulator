#include <bitset>
#include <string>
#include <cmath>
#include "FMT.h"
#include "operation_map.h"
using namespace std;

bool valid_imm(int imm, int n_bits, int even){
  int t = pow(2, n_bits-1);
  if(even == 0){
    if(imm <= t-1 && imm >= -t){
      return true;
    }
    else{
      return false;
    }
  }
  else if(even == 1){
    if(imm <= t-2 && imm >= -t){
      return true;
    }
    else{
       return false;
    }
  }
  else{
    if(imm >= 0 && imm <= pow(2, n_bits)){
      return true;
    }
    else{
      return false;
    }
  } 
} 


void InstructionInterface:: arrangeopcode(bitset<32> & Instruction ,bitset<7>  a){
  for (int i=6; i >= 0; i--){
    Instruction[i]=a[i];
  }
}

void InstructionInterface:: arrangefunct3(bitset<32> & Instruction ,bitset<3>  a){
  for (int i=2, j=14 ; i >= 0; i--, j--){
    Instruction[j]=a[i];
  }
}

void InstructionInterface:: arrangefunct7(bitset<32> & Instruction ,bitset<7>  a){
  for (int i=6, j=31 ; i >= 0; i--,j--){
    Instruction[j]=a[i];
  }
}
void InstructionInterface:: arrangefunct6(bitset<32> & Instruction ,bitset<7>  a){
  for (int i=5, j=31 ; i >= 0; i--,j--){
    Instruction[j]=a[i];
  }
}

void InstructionInterface:: arrangeregister(bitset<32> & Instruction ,bitset<5> a, int j){
  for (int i=4 ; i >= 0; i--,j--){
    Instruction[j]=a[i];
  }
}

void InstructionInterface:: Evaluatehexcode(string & hexcode, bitset<32> & Instruction){
  hexcode = "";
  int n = 31;
  for(int i=0 ; i<8; i++){
    string b = "";
    for(int j=0; j<4; j++, n--){
      b += Instruction[n]?'1':'0'; //returns 1 or 0 char
    }
    char c = hexDigit[b];
    hexcode+=c;
  }
}

void InstructionInterface::printhexInstruction(){
  cout<<hexCode;
}

string InstructionInterface::gethexInstruction(){
  return hexCode;
}

void  RType::EvaluateInstruction(){

  arrangefunct7(Instruction, Details[op].funct7);
  arrangeregister(Instruction, regDetails[rs2], 24);
  arrangeregister(Instruction, regDetails[rs1], 19);
  arrangefunct3(Instruction, Details[op].funct3);
  arrangeregister(Instruction, regDetails[rd], 11);
  arrangeopcode(Instruction, Details[op].opcode);
  Evaluatehexcode(hexCode, Instruction);

}

void IType::EvaluateInstruction(){

  if(op == "slli" || op== "srai" || op == "srli"){
    if(valid_imm(imm, 6, 3)){
      arrangefunct6(Instruction,Details[op].funct7);
      bitset<6> val = imm;

      for(int i=5,j=25;i>=0;i--,j--){
        Instruction[j]=val[i];
      }
      arrangeregister(Instruction, regDetails[rs1], 19);
      arrangefunct3(Instruction, Details[op].funct3);
      arrangeregister(Instruction, regDetails[rd], 11);
      arrangeopcode(Instruction, Details[op].opcode);
      Evaluatehexcode(hexCode, Instruction);
    }
    else{
        cout<<"Immediate value doesnot fits in 6 bits"<<endl;
    }

  }else{
    if(valid_imm(imm, 12, 0)){
      bitset<12> val = imm;

      for(int i=11, j=31; i >= 0; i--, j--){  //arranging imm in instruction
      Instruction[j] = val[i];
      }

      arrangeregister(Instruction, regDetails[rs1], 19);
      arrangefunct3(Instruction, Details[op].funct3);
      arrangeregister(Instruction, regDetails[rd], 11);
      arrangeopcode(Instruction, Details[op].opcode);
      Evaluatehexcode(hexCode, Instruction);
    }
    else{
      cout<<"Immediate value doesnot fit in 12 bits"<<endl;
    }
  }
}

void SType::EvaluateInstruction(){

  if(valid_imm(imm, 12, 0)){
    bitset<12> val = imm;

    /* Arranging imm in binary Instructon*/
    for(int i=11, j=31; i>4; i--, j--){
      Instruction[j] = val[i];
    }
    for(int i=4, j=11; i>=0; i--, j--){
      Instruction[j] = val[i];
    }

    arrangeregister(Instruction, regDetails[rs2], 24);
    arrangeregister(Instruction, regDetails[rs1], 19);
    arrangefunct3(Instruction, Details[op].funct3);
    arrangeopcode(Instruction, Details[op].opcode);
    Evaluatehexcode(hexCode, Instruction);
  }
  else{
    cout<<"Immediate value doesnot fit in 12 bits"<<endl;
  }
}

void BType::EvaluateInstruction(){

  if(valid_imm(imm, 13, 1)){
    bitset<13> val = imm;

    /*Arranging imm in binary in Instruction in their  respective position*/
    Instruction[31] = val[12];
    Instruction[7] = val[11];

    for(int i=10, j=30; i>=5; i--, j--){
      Instruction[j] = val[i];
    }
    for(int i=4, j=11; i>=1; i--, j--){
      Instruction[j] = val[i];
    }

    arrangeregister(Instruction, regDetails[rs2], 24);
    arrangeregister(Instruction, regDetails[rs1], 19);
    arrangefunct3(Instruction, Details[op].funct3);
    arrangeopcode(Instruction, Details[op].opcode);
    Evaluatehexcode(hexCode, Instruction);
  }else{
    cout<<"Immediate value doesnot fit in 13 bits"<<endl;

  }

}

void UType::EvaluateInstruction(){

  if(valid_imm(imm, 20, 0)){
    bitset<20> val = imm;

    /*Arranging imm in binary in Instruction in their  respective position*/
    for(int i=19, j=31; i>=0; i--, j-- ){
      Instruction[j] = val[i];
    }

    arrangeregister(Instruction, regDetails[rd], 11);
    arrangeopcode(Instruction, Details[op].opcode);
    Evaluatehexcode(hexCode, Instruction);
  }
  else{
    cout<<"Immediate value doesnot fit in 20 bits"<<endl;
  }
}

void JType::EvaluateInstruction(){

  if(valid_imm(imm, 21, 1)){
    bitset<21> val = imm;

  /*Arranging imm in binary in Instruction in their  respective position*/
    Instruction[31] = val[20];
    Instruction[20] = val[11];

    for(int i=10, j=30; i>=1; i--, j--){
      Instruction[j] = val[i];
    }
    for(int i=19; i>=12; i--){
      Instruction[i] = val[i];
    }

    arrangeregister(Instruction, regDetails[rd], 11);
    arrangeopcode(Instruction, Details[op].opcode);
    Evaluatehexcode(hexCode, Instruction);
  }
  else{
    cout<<"Immediate value doesn't fit in 21 bits"<<endl;
  }
}