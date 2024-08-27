#include <bitset>
#include <string>
#include "FMT.h"
#include "operation_map.h"
using namespace std;

void arrangeopcode(bitset<32> & Instruction ,bitset<7>  a){
  for (int i=6; i >= 0; i--){
    Instruction[i]=a[i];
  }
}
void arrangefunct3(bitset<32> & Instruction ,bitset<3>  a){
  for (int i=2, j=14 ; i >= 0; i--, j--){
    Instruction[j]=a[i];
  }
}
void arrangefunct7(bitset<32> & Instruction ,bitset<7>  a){
  for (int i=6, j=31 ; i >= 0; i--,j--){
    Instruction[j]=a[i];
  }
}

void arrangeregister(bitset<32> & Instruction ,bitset<5> a, int j){
  for (int i=4 ; i >= 0; i--,j--){
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

  arrangefunct7(Instruction, Details[op].funct7);
  arrangeregister(Instruction, regDetails[rs2], 24);
  arrangeregister(Instruction, regDetails[rs1], 19);
  arrangefunct3(Instruction, Details[op].funct3);
  arrangeregister(Instruction, regDetails[rd], 11);
  arrangeopcode(Instruction, Details[op].opcode);
  
}

void IType::EvaluateInstruction(){

  bitset<12> val = imm;

  for(int i=11, j=31; i >= 0; i--, j--){  //arranging imm in instruction
    Instruction[j] = val[i];
  }

  arrangeregister(Instruction, regDetails[rs1], 19);
  arrangefunct3(Instruction, Details[op].funct3);
  arrangeregister(Instruction, regDetails[rd], 12);
  arrangeopcode(Instruction, Details[op].opcode);

}

void SType::EvaluateInstruction(){

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

}

void BType::EvaluateInstruction(){

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

}

void UType::EvaluateInstruction(){

  bitset<20> val = imm;

/*Arranging imm in binary in Instruction in their  respective position*/
  for(int i=19, j=31; i>=0; i--, j-- ){
    Instruction[j] = val[i];
  }

  arrangeregister(Instruction, regDetails[rd], 11);
  arrangeopcode(Instruction, Details[op].opcode);

}

void JType::EvaluateInstruction(){

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

}