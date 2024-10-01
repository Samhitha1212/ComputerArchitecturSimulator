#pragma once
#include<vector>
#include<string>
#include "globalvars.h"
#include "registers.h"
#include "memory.h"
#include "operation_map.h"
#include "ErrorHandling.h"
using namespace std;

void executeRType(int n){
  if(arg[n][0] == "add"){
    long int t = static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) + static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][3]]).to_ulong());
    RegisterFile.writeReg(regDetails[arg[n][1]], t);
  }
  else if(arg[n][0] == "sub"){
    long int t = static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) - static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][3]]).to_ulong());
    RegisterFile.writeReg(regDetails[arg[n][1]], t);
  }
  else if(arg[n][0] == "and"){
    bitset<64> t =  RegisterFile.readReg(regDetails[arg[n][2]]) & RegisterFile.readReg(regDetails[arg[n][3]]);
    RegisterFile.writeReg(regDetails[arg[n][1]], t);
  }
  else if(arg[n][0] == "or"){
    bitset<64> t =  RegisterFile.readReg(regDetails[arg[n][2]]) | RegisterFile.readReg(regDetails[arg[n][3]]);
    RegisterFile.writeReg(regDetails[arg[n][1]], t);
  }
  else if(arg[n][0] == "xor"){
    bitset<64> t =  RegisterFile.readReg(regDetails[arg[n][2]]) ^= RegisterFile.readReg(regDetails[arg[n][3]]);
    RegisterFile.writeReg(regDetails[arg[n][1]], t);
  }
  else if(arg[n][0] == "sll"){
    bitset<6> b;
    for(int i = 5; i >= 0; i--){
      b[i] = RegisterFile.readReg(regDetails[arg[n][3]])[i];
    }
    bitset<64> t =  RegisterFile.readReg(regDetails[arg[n][2]]) <<= b.to_ulong();
    RegisterFile.writeReg(regDetails[arg[n][1]], t);
  }
  else if(arg[n][0] == "srl"){
    bitset<6> b;
    for(int i = 5; i >= 0; i--){
      b[i] = RegisterFile.readReg(regDetails[arg[n][3]])[i];
    }
    bitset<64> t =  RegisterFile.readReg(regDetails[arg[n][2]]) >>= b.to_ulong();
    RegisterFile.writeReg(regDetails[arg[n][1]], t);
  } 
  else if(arg[n][0] == "sra"){
    bitset<6> b = 0;
    for(int i = 5; i >= 0; i--){
      b[i] = RegisterFile.readReg(regDetails[arg[n][3]])[i];
    }

    if(RegisterFile.readReg(regDetails[arg[n][3]])[63] == 1){ 
      int d = b.to_ulong();
      bitset<64> r = 0;
      r[63] = RegisterFile.readReg(regDetails[arg[n][2]])[63];
      for(int i = 63; d > 0; i--, d--){
        r[i] = RegisterFile.readReg(regDetails[arg[n][2]])[i];
      }
      bitset<64> t =  (RegisterFile.readReg(regDetails[arg[n][2]]) >>= d) | r;
      RegisterFile.writeReg(regDetails[arg[n][1]], t);
    }
    else{
      bitset<64> t =  RegisterFile.readReg(regDetails[arg[n][2]]) >>= b.to_ulong();
      RegisterFile.writeReg(regDetails[arg[n][1]], t);
    }
  }
  else if(arg[n][0] == "slt"){
    if(static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) < static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][3]]).to_ulong())){
      bitset<64> b = 1;
      RegisterFile.writeReg(regDetails[arg[n][1]], b);
    }
    else{
      bitset<64> b = 0;
      RegisterFile.writeReg(regDetails[arg[n][1]], b);
    }
  }
  else if(arg[n][0] == "sltu"){
    if(RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong() < RegisterFile.readReg(regDetails[arg[n][3]]).to_ulong()){
      bitset<64> b = 1;
      RegisterFile.writeReg(regDetails[arg[n][1]], b);
    }
    else{
      bitset<64> b = 0;
      RegisterFile.writeReg(regDetails[arg[n][1]], b);
    }
  }
  PC = PC +4;
}

void executeIType(int n){
  if(arg[n][0] == "addi"){
    long int t = static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) + stol(arg[n][3]);
    RegisterFile.writeReg(regDetails[arg[n][1]], t);
  }
  else if(arg[n][0] == "andi"){
    bitset<64> t = stol(arg[n][3]);
    bitset<64> b = RegisterFile.readReg(regDetails[arg[n][2]]) & t;
    RegisterFile.writeReg(regDetails[arg[n][1]], b);
  }
  else if(arg[n][0] == "ori"){
    bitset<64> t = stol(arg[n][3]);
    bitset<64> b = RegisterFile.readReg(regDetails[arg[n][2]]) | t;
    RegisterFile.writeReg(regDetails[arg[n][1]], b);
  }
  else if(arg[n][0] == "xori"){
    bitset<64> t = stol(arg[n][3]);
    bitset<64> b = RegisterFile.readReg(regDetails[arg[n][2]]) ^= t;
    RegisterFile.writeReg(regDetails[arg[n][1]], b);
  }
  else if(arg[n][0] == "slli"){
    bitset<64> t = stol(arg[n][3]);
    bitset<64> b = RegisterFile.readReg(regDetails[arg[n][2]]) <<= t.to_ulong();
    RegisterFile.writeReg(regDetails[arg[n][1]], b);
  }
  else if(arg[n][0] == "srli"){
    bitset<64> t = stol(arg[n][3]);
    bitset<64> b = RegisterFile.readReg(regDetails[arg[n][2]]) <<= t.to_ulong();
    RegisterFile.writeReg(regDetails[arg[n][1]], b);
  }
  else if(arg[n][0] == "srai"){
    bitset<6> b = stol(arg[n][3]);

    if(RegisterFile.readReg(regDetails[arg[n][3]])[63] == 1){ 
      int d = b.to_ulong();
      bitset<64> r = 0;
      r[63] = RegisterFile.readReg(regDetails[arg[n][2]])[63];
      for(int i = 63; d > 0; i--, d--){
        r[i] = RegisterFile.readReg(regDetails[arg[n][2]])[i];
      }
      bitset<64> t =  (RegisterFile.readReg(regDetails[arg[n][2]]) >>= d) | r;
      RegisterFile.writeReg(regDetails[arg[n][1]], t);
    }
    else{
      bitset<64> t =  RegisterFile.readReg(regDetails[arg[n][2]]) >>= b.to_ulong();
      RegisterFile.writeReg(regDetails[arg[n][1]], t);
    }
  }
  else if(arg[n][0] == "slti"){
    if(static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) < stol(arg[n][3])){
      bitset<64> b = 1;
      RegisterFile.writeReg(regDetails[arg[n][1]], b);
    }
    else{
      bitset<64> b = 0;
      RegisterFile.writeReg(regDetails[arg[n][1]], b);
    }
  }
  else if(arg[n][0] == "sltiu"){
    if(static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) < stoul(arg[n][3])){
      bitset<64> b = 1;
      RegisterFile.writeReg(regDetails[arg[n][1]], b);
    }
    else{
      bitset<64> b = 0;
      RegisterFile.writeReg(regDetails[arg[n][1]], b);
    }
  }
  else if(arg[n][0] == "lbu"){
    long int k=static_cast<long int> (RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) + convertToInt(arg[n][3]);
    if( k >= 0 && k < 0x50000){
      bitset<64> value = Memory.ReadData(1, k);
      RegisterFile.writeReg(regDetails[arg[n][1]], value);
    }
   
  }
  else if(arg[n][0] == "lhu"){
     long int k=static_cast<long int> (RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) + convertToInt(arg[n][3]);
    if( k >= 0 && k < 0x50000){
      bitset<64> value = Memory.ReadData(2, k);
      RegisterFile.writeReg(regDetails[arg[n][1]], value);
    }
  }
  else if(arg[n][0] == "lwu"){
    long int k=static_cast<long int> (RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) + convertToInt(arg[n][3]);
    if( k >= 0 && k < 0x50000){
      bitset<64> value = Memory.ReadData(4, k);
      RegisterFile.writeReg(regDetails[arg[n][1]], value);
    }
  }
    else if(arg[n][0] == "lb"){
    long int k=static_cast<long int> (RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) + convertToInt(arg[n][3]);
    if( k >= 0 && k < 0x50000){
      bitset<64> value = Memory.ReadData(1, k);
      if(value[7]){
        for( int i = 8;i<64; i++){
          value[i]=1;
        }
      }
      RegisterFile.writeReg(regDetails[arg[n][1]], value);
    }
   
  }
  else if(arg[n][0] == "lh"){
     long int k=static_cast<long int> (RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) + convertToInt(arg[n][3]);
    if( k >= 0 && k < 0x50000){
      bitset<64> value = Memory.ReadData(2, k);
        if(value[15]){
        for( int i = 16;i<64; i++){
          value[i]=1;
        }
      }
      RegisterFile.writeReg(regDetails[arg[n][1]], value);
    }
  }
  else if(arg[n][0] == "lw"){
    long int k=static_cast<long int> (RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) + convertToInt(arg[n][3]);
    if( k >= 0 && k < 0x50000){
      bitset<64> value = Memory.ReadData(4, k);
        if(value[31]){
        for( int i = 32;i<64; i++){
          value[i]=1;
        }
      }
      RegisterFile.writeReg(regDetails[arg[n][1]], value);
    }
  }
  else if(arg[n][0] == "ld"){
     long int k=static_cast<long int> (RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) + convertToInt(arg[n][3]);
    if( k >= 0 && k < 0x50000){
      bitset<64> value = Memory.ReadData(8, k);
      RegisterFile.writeReg(regDetails[arg[n][1]], value);
    }
  }else if( arg[n][0]== "jalr"){
      int imm=0;
        if(IsValidImmediate(arg[n][3],false)){
            imm=convertToInt(arg[n][3]);
        }
      long int rs1= static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][2]] ).to_ulong());
      rs1+=imm;
          RegisterFile.writeReg( regDetails[arg[n][1]] ,PC+4);
          PC+=rs1;
          return ;
  }
  PC = PC +4;
}

void executeSType(int n){
  if(arg[n][0] == "sb"){
    bitset<64> value = RegisterFile.readReg(regDetails[arg[n][1]]);
    long int addr = static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) + convertToInt(arg[n][3]);
    if(addr >=0 && addr < 0x50000){
       Memory.WriteData(1, addr, value);
    }
   
  }
  else if(arg[n][0] == "sh"){
    bitset<64> value = RegisterFile.readReg(regDetails[arg[n][1]]);
    long int addr = static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) + convertToInt(arg[n][3]);
    if(addr >=0 && addr < 0x50000){
       Memory.WriteData(2, addr, value);
    }
  }
  else if(arg[n][0] == "sw"){
    bitset<64> value = RegisterFile.readReg(regDetails[arg[n][1]]);
    long int addr = static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) + convertToInt(arg[n][3]);
    if(addr >=0 && addr < 0x50000){
       Memory.WriteData(4, addr, value);
    }
  }
  else if(arg[n][0] == "sd"){
    bitset<64> value = RegisterFile.readReg(regDetails[arg[n][1]]);
    long int addr = static_cast<long int>(RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong()) + convertToInt(arg[n][3]);
    if(addr >=0 && addr < 0x50000){
       Memory.WriteData(8, addr, value);
    }
  }
  PC = PC + 4;
}

void executeBType(int n){
  if (arg[n][0] == "beq") {
    if (RegisterFile.readReg(regDetails[arg[n][1]]) ==
        RegisterFile.readReg(regDetails[arg[n][2]])) {
      PC += convertToInt(arg[n][3]);
    } else {
      PC += 4;
    }

  } else if (arg[n][0] == "bneq") {
    if (RegisterFile.readReg(regDetails[arg[n][1]]) !=
        RegisterFile.readReg(regDetails[arg[n][2]])) {
      PC += convertToInt(arg[n][3]);
    } else {
      PC += 4;
    }
  } else if (arg[n][0] == "blt") {
    if (static_cast<long int>(
            RegisterFile.readReg(regDetails[arg[n][1]]).to_ulong()) <
        static_cast<long int>(
            RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong())) {
      PC += convertToInt(arg[n][3]);
    } else {
      PC += 4;
    }

  } else if (arg[n][0] == "bge") {
    if (static_cast<long int>(
            RegisterFile.readReg(regDetails[arg[n][1]]).to_ulong()) >=
        static_cast<long int>(
            RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong())) {
      PC += convertToInt(arg[n][3]);
    } else {
      PC += 4;
    }
  } else if (arg[n][0] == "bltu") {
    if ((RegisterFile.readReg(regDetails[arg[n][1]]).to_ulong()) <
        (RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong())) {
      PC += convertToInt(arg[n][3]);
    } else {
      PC += 4;
    }

  } else if (arg[n][0] == "bgeu") {
    if ((RegisterFile.readReg(regDetails[arg[n][1]]).to_ulong()) >=
        (RegisterFile.readReg(regDetails[arg[n][2]]).to_ulong())) {
      PC += convertToInt(arg[n][3]);
    } else {
      PC += 4;
    }
  }
}

void executeJType(int n){
    if( arg[n][0] =="jal"){
    int imm=0;
          if(IsValidLabel(arg[n][2],false)){
            imm = Labels[arg[n][2]].first-n;
            imm *= 4;
          }else if(IsValidImmediate(arg[n][2],false)){
            imm=convertToInt(arg[n][2]);
          }

          RegisterFile.writeReg( regDetails[arg[n][1]] ,PC+4);
          PC+=imm;
  }
}

void executeUType(int n){
   if(arg[n][0] == "lui"){
    int imm= convertToInt( arg[n][2] );
    imm=imm<<12;
    RegisterFile.writeReg( regDetails[ arg[n][1]] , imm);

  }else if ( arg[n][0] == "auipc"){
    int imm= convertToInt( arg[n][2] );
    imm=imm<<12;
    RegisterFile.writeReg( regDetails[ arg[n][1]] , PC+imm);
  }
  PC+=4;
}

void ExecuteInstruction(int n){
  if(Details[arg[n][0]].FMT == 'R'){
    executeRType(n);
  } 
  else if(Details[arg[n][0]].FMT == 'I'){
    executeIType(n);
  }
  else if(Details[arg[n][0]].FMT == 'S'){
    executeSType(n);
  }
  else if(Details[arg[n][0]].FMT == 'B'){
    executeBType(n);
  }
  else if(Details[arg[n][0]].FMT == 'J'){
    executeJType(n);
  }
  else if(Details[arg[n][0]].FMT == 'U'){
    executeUType(n);
  }
}
