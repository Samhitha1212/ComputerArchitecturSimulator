#pragma once

#include <bitset>
#include <string>
#include <fstream>
using namespace std;

class InstructionInterface {     
protected:
  bitset<32> Instruction;
  string hexCode;

public:
  virtual void EvaluateInstruction() = 0;
  void printhexInstruction();
  string gethexInstruction();
  void arrangeopcode(bitset<32> & Instruction ,bitset<7>  a);
  void arrangefunct3(bitset<32> & Instruction ,bitset<3>  a);
  void arrangefunct7(bitset<32> & Instruction ,bitset<7>  a);
  void arrangefunct6(bitset<32> & Instruction ,bitset<7>  a);
  void arrangeregister(bitset<32> & Instruction ,bitset<5> a, int j);
  void Evaluatehexcode(string & hexcode, bitset<32> & Instruction);
};

class RType : public InstructionInterface {
private:
  string rs1, rs2, rd;
  string op;               // Here op means operation (e.g. add)

public:
  RType(string op, string rd, string rs1, string rs2)
      : op(op), rs1(rs1), rs2(rs2), rd(rd) {}
  void EvaluateInstruction();
};

class IType : public InstructionInterface {
private:
  string rs1,  rd;
  int imm;
  string op;

public:
  IType(string op, string rd, string rs1, int imm)
      : op(op), rs1(rs1), imm(imm), rd(rd) {}
  void EvaluateInstruction();
};

class SType : public InstructionInterface {
private:
  string rs1, rs2;
  int imm;
  string op;

public:
  SType(string op, string rs2, string rs1, int imm)
      : op(op), rs1(rs1), imm(imm), rs2(rs2) {}
  void EvaluateInstruction();
};

class BType : public InstructionInterface {
private:
  string rs1, rs2;
  int imm;
  string op;

public:
  BType(string op, string rs1, string rs2, int imm)
      : op(op), rs1(rs1), imm(imm), rs2(rs2) {}
  void EvaluateInstruction();
};

class UType : public InstructionInterface {
private:
  string rd;
  int imm;
  string op;

public:
  UType(string op, string rd, int imm) : op(op), rd(rd), imm(imm) {}
  void EvaluateInstruction();
};

class JType : public InstructionInterface {
private:
  string rd;
  int imm;
  string op;

public:
  JType(string op, string rd, int imm) : op(op), rd(rd), imm(imm) {}
  void EvaluateInstruction();
};