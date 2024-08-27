#include <bitset>
#include <string>
using namespace std;

class Instruction {
private:
  bitset<7> opcode;

public:
  virtual void EvaluateInstruction() = 0;
  bitset<5> evaluateRegister(string);
  bitset<3> evaluatefunct3(string);
  bitset<7> evaluatefunct7(string);
  bitset<7> evaluateOpcode(string);
};

class RType : public Instruction {
private:
  string rs1, rs2, rd;
  string op;
  bitset<32> Instruction;
  string hexCode;

public:
  RType(string op, string rd, string rs1, string rs2)
      : op(op), rs1(rs1), rs2(rs2), rd(rd) {}
  void EvaluateInstruction();
};

class IType : public Instruction {
private:
  string rs1,  rd;
  int imm;
  string op;
  bitset<32> Instruction;

public:
  IType(string op, string rd, string rs1, int imm)
      : op(op), rs1(rs1), imm(imm), rd(rd) {}
  void EvaluateInstruction();
};

class SType : public Instruction {
private:
  string rs1, rs2;
  int imm;
  string op;
  bitset<32> Instruction;

public:
  SType(string op, string rs2, string rs1, int imm)
      : op(op), rs1(rs1), imm(imm), rs2(rs2) {}
  void EvaluateInstruction();
};

class BType : public Instruction {
private:
  string rs1, rs2;
  int imm;
  string op;
  bitset<32> Instruction;

public:
  BType(string op, string rs1, string rs2, int imm)
      : op(op), rs1(rs1), imm(imm), rs2(rs2) {}
  void EvaluateInstruction();
};

class UType : public Instruction {
private:
  string rd;
  int imm;
  string op;
  bitset<32> Instruction;

public:
  UType(string op, string rd, int imm) : op(op), rd(rd), imm(imm) {}
  void EvaluateInstruction();
};

class JType : public Instruction {
private:
  string rd;
  int imm;
  string op;
  bitset<32> Instruction;

public:
  JType(string op, string rd, int imm) : op(op), rd(rd), imm(imm) {}
  void EvaluateInstruction();
};
