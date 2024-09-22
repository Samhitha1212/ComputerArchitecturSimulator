#pragma once

#include <bitset>
#include <iostream>
#include <map>
#include <string>
using namespace std;

/*struct to store the format, opcode, funct3, funct7 of the given instruction*/

struct InstructionDetails {
  char FMT;         // format
  bitset<7> opcode; // opcode
  bitset<3> funct3; // funct3
  bitset<7> funct7; // funct7
};

extern map<string, InstructionDetails> Details;
extern map<string, int> regDetails;
extern map<string, char> hexDigit;
bool IsValidRegeister(string s);
bool IsValidOperation(string s);

