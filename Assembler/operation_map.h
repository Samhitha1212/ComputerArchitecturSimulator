#include <iostream>
#include <map>
#include <bitset>
#include <string>
using namespace std;

/*struct to store the format, opcode, funct3, funct7 of the given instruction*/

struct InstructionDetails{
  char FMT;                // format
  bitset<7> opcode;        // opcode
  bitset<3> funct3;        // funct3
  bitset<7> funct7;        // funct7
};

map<string, InstructionDetails> Details;  //mapping an instruction to its format, opcode, funct3, funct7
map<string, int> regDetails;              // Mapping a register and its nickname to int(e.g. x0 = 0)
map<string, char> hexDigit;               // Mapping a binary to its corresponding hexdigit

void DetailsInitialization(){

  Details["add"] = {'R', '0110011', 0, 0};
  Details["sub"] = {'R', '0110011', 0, 20};
  Details["xor"] = {'R', '0110011', 4, 0};
  Details["or"] = {'R', '0110011', 6, 0};
  Details["and"] = {'R', '0110011', 7, 0};
  Details["sll"] = {'R', '0110011', 1, 0};
  Details["srl"] = {'R', '0110011', 5, 0};
  Details["sra"] = {'R', '0110011', 5, 20};
  Details["slt"] = {'R', '0110011', 2, 0};
  Details["sltu"] = {'R', '0110011', 3, 0};

  Details["addi"] = {'I', '0010011', 0, NULL};
  Details["xori"] = {'I', '0010011', 4, NULL};
  Details["ori"] = {'I', '0010011', 6, NULL};
  Details["andi"] = {'I', '0010011', 7, NULL};
  Details["slli"] = {'I', '0010011', 1, NULL};
  Details["srli"] = {'I', '0010011', 5, NULL};
  Details["srai"] = {'I', '0010011', 5, NULL};
  Details["slti"] = {'I', '0010011', 2, NULL};
  Details["sltui"] = {'I', '0010011', 3, NULL};

  Details["lb"] = {'I', '0000011', 0, NULL};
  Details["lh"] = {'I', '0000011', 1, NULL};
  Details["lw"] = {'I', '0000011', 2, NULL};
  Details["ld"] = {'I', '0000011', 3, NULL};
  Details["lbu"] = {'I', '0000011', 4, NULL};
  Details["lhu"] = {'I', '0000011', 5, NULL};
  Details["lwu"] = {'I', '0000011', 6, NULL};

  Details["sb"] = {'S', '0100011', 0, NULL};
  Details["sh"] = {'S', '0100011', 1, NULL};
  Details["sw"] = {'S', '0100011', 2, NULL};
  Details["sd"] = {'S', '0100011', 3, NULL};

  Details["beq"] = {'B', '1100011', 0, NULL};
  Details["bne"] = {'B', '1100011', 1, NULL};
  Details["blt"] = {'B', '1100011', 4, NULL};
  Details["bge"] = {'B', '1100011', 5, NULL};
  Details["bltu"] = {'B', '1100011', 6, NULL};
  Details["bgeu"] = {'B', '1100011', 7, NULL};

  Details["jal"] = {'J', '1101111', NULL, NULL};
  Details["jalr"] = {'I', '1101111', 0, NULL};

  Details["lui"] = {'U', '0110111', NULL, NULL};
  Details["auipc"] = {'U', '0010111', NULL, NULL};

}

void RegisterInitialization(){

  regDetails["x0"] = 0;
  regDetails["zero"] = 0;

  regDetails["x1"] = 1;
  regDetails["ra"] = 1;

  regDetails["x2"] = 2;
  regDetails["sp"] = 2;

  regDetails["x3"] = 3;
  regDetails["gp"] = 3;

  regDetails["x4"] = 4;
  regDetails["tp"] = 4;

  regDetails["x5"] = 5;
  regDetails["t0"] = 5;

  regDetails["x6"] = 6;
  regDetails["t1"] = 6;

  regDetails["x7"] = 7;
  regDetails["t2"] = 7;

  regDetails["x8"] = 8;
  regDetails["s0"] = 8;
  regDetails["fp"] = 8;

  regDetails["x9"] = 9;
  regDetails["s1"] = 9;

  regDetails["x10"] = 10;
  regDetails["a0"] = 10;

  regDetails["x11"] = 11;
  regDetails["a1"] = 11;

  regDetails["x12"] = 12;
  regDetails["a2"] = 12;

  regDetails["x13"] = 13;
  regDetails["a3"] = 13;

  regDetails["x14"] = 14;
  regDetails["a4"] = 14;

  regDetails["x15"] = 15;
  regDetails["a5"] = 15;

  regDetails["x16"] = 16;
  regDetails["a6"] = 16;

  regDetails["x17"] = 17;
  regDetails["a7"] = 17;

  regDetails["x18"] = 18;
  regDetails["s2"] = 18;

  regDetails["x19"] = 19;
  regDetails["s3"] = 19;

  regDetails["x20"] = 20;
  regDetails["s4"] = 20;

  regDetails["x21"] = 21;
  regDetails["s5"] = 21;

  regDetails["x22"] = 22;
  regDetails["s6"] = 22;

  regDetails["x23"] = 23;
  regDetails["s7"] = 23;

  regDetails["x24"] = 24;
  regDetails["s8"] = 24;

  regDetails["x25"] = 25;
  regDetails["s9"] = 25;

  regDetails["x26"] = 26;
  regDetails["s10"] = 26;

  regDetails["x27"] = 27;
  regDetails["s11"] = 27;

  regDetails["x28"] = 28;
  regDetails["t3"] = 28;

  regDetails["x29"] = 29;
  regDetails["t4"] = 29;

  regDetails["x30"] = 30;
  regDetails["t5"] = 30;

  regDetails["x31"] = 31;
  regDetails["t6"] = 31;

}

void Hexadecimal(){

  hexDigit["0000"] = '0';
  hexDigit["0001"] = '1';
  hexDigit["0010"] = '2';
  hexDigit["0011"] = '3';
  hexDigit["0100"] = '4';
  hexDigit["0101"] = '5';
  hexDigit["0110"] = '6';
  hexDigit["0111"] = '7';
  hexDigit["1000"] = '8';
  hexDigit["1001"] = '9';
  hexDigit["1010"] = 'a';
  hexDigit["1011"] = 'b';
  hexDigit["1100"] = 'c';
  hexDigit["1101"] = 'd';
  hexDigit["1110"] = 'e';
  hexDigit["1111"] = 'f';

}

