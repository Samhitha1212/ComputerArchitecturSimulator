#include <bitset>
#include <string>
#include <cmath>
#include "FMT.h"
#include "operation_map.h"
using namespace std;

/*it checks whether the given imm value is in the range of imm value of the given instruction or not*/
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
    if(imm <= t-2 && imm >= -t && imm%2 == 0){
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

/*This function arranges the opcode bits of an instruction in appropriate positions*/
void InstructionInterface:: arrangeopcode(bitset<32> & Instruction ,bitset<7>  a){
  for (int i=6; i >= 0; i--){
    Instruction[i]=a[i];
  }
}

/*This function arranges the funct3 bits of an instruction in appropriate positions*/
void InstructionInterface:: arrangefunct3(bitset<32> & Instruction ,bitset<3>  a){
  for (int i=2, j=14 ; i >= 0; i--, j--){
    Instruction[j]=a[i];
  }
}

/*This function arranges the funct7 bits of an instruction in appropriate positions*/
void InstructionInterface:: arrangefunct7(bitset<32> & Instruction ,bitset<7>  a){
  for (int i=6, j=31 ; i >= 0; i--,j--){
    Instruction[j]=a[i];
  }
}

/*This function arranges the funct6 bits of an instruction in appropriate positions*/
void InstructionInterface:: arrangefunct6(bitset<32> & Instruction ,bitset<7>  a){
  for (int i=5, j=31 ; i >= 0; i--,j--){
    Instruction[j]=a[i];
  }
}

/*It arranges the bits of respective register in binary code from position j*/
void InstructionInterface:: arrangeregister(bitset<32> & Instruction ,bitset<5> a, int j){
  for (int i=4 ; i >= 0; i--,j--){
    Instruction[j]=a[i];
  }
}

/*it given the hex code from the  given binary code*/
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

/*To print the hex code*/
void InstructionInterface::printhexInstruction(){
  cout<<hexCode;
}

/*returns hex code*/
string InstructionInterface::gethexInstruction(){
  return hexCode;
}

/*It evaluates the hex code from binary instruction formed by arranging opcode, rs2, rs1, funct3, rd, funct7 in their respective positions*/
void  RType::EvaluateInstruction(){

  arrangefunct7(Instruction, Details[op].funct7);
  arrangeregister(Instruction, regDetails[rs2], 24);
  arrangeregister(Instruction, regDetails[rs1], 19);
  arrangefunct3(Instruction, Details[op].funct3);
  arrangeregister(Instruction, regDetails[rd], 11);
  arrangeopcode(Instruction, Details[op].opcode);
  Evaluatehexcode(hexCode, Instruction);

}

/*It evaluates the hex code from binary instruction formed by arranging opcode, rs1, funct3, rd, imm in their respective positions*/
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
        // cout<<"Immediate value : "<<imm<<" doesnot fits in 6 bits"<<endl;
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
     
    }
  }
}

/*It evaluates the hex code from binary instruction formed by arranging opcode, rs2, rs1, funct3, imm in their respective positions*/
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
    
  }
}

/*It evaluates the hex code from binary instruction formed by arranging opcode, rs2, rs1, funct3, imm in their respective positions*/
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
    

  }

}

/*It evaluates the hex code from binary instruction formed by arranging opcode, rd, imm in their respective positions*/
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
    
  }
}

/*It evaluates the hex code from binary instruction formed by arranging opcode, rs2, rs1, funct3, rd, funct7 in their respective positions*/
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
    
  }
}