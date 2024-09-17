#include "operation_map.h"
// mapping an instruction to its format, opcode, funct3, funct7
map<string, InstructionDetails> Details = {

    {"add", {'R', bitset<7>("0110011"), 0, 0}},
    {"sub", {'R', bitset<7>("0110011"), 0, 32}},
    {"xor", {'R', bitset<7>("0110011"), 4, 0}},
    {"or", {'R', bitset<7>("0110011"), 6, 0}},
    {"and", {'R', bitset<7>("0110011"), 7, 0}},
    {"sll", {'R', bitset<7>("0110011"), 1, 0}},
    {"srl", {'R', bitset<7>("0110011"), 5, 0}},
    {"sra", {'R', bitset<7>("0110011"), 5, 32}},
    {"slt", {'R', bitset<7>("0110011"), 2, 0}},
    {"sltu", {'R', bitset<7>("0110011"), 3, 0}},

    {"addi", {'I', bitset<7>("0010011"), 0, -1}},
    {"xori", {'I', bitset<7>("0010011"), 4, -1}},
    {"ori", {'I', bitset<7>("0010011"), 6, -1}},
    {"andi", {'I', bitset<7>("0010011"), 7, -1}},
    {"slli", {'I', bitset<7>("0010011"), 1, 0}},
    {"srli", {'I', bitset<7>("0010011"), 5, 0}},
    {"srai", {'I', bitset<7>("0010011"), 5, 16}},
    {"slti", {'I', bitset<7>("0010011"), 2, -1}},
    {"sltui", {'I', bitset<7>("0010011"), 3, -1}},

    {"lb", {'I', bitset<7>("0000011"), 0, -1}},
    {"lh", {'I', bitset<7>("0000011"), 1, -1}},
    {"lw", {'I', bitset<7>("0000011"), 2, -1}},
    {"ld", {'I', bitset<7>("0000011"), 3, -1}},
    {"lbu", {'I', bitset<7>("0000011"), 4, -1}},
    {"lhu", {'I', bitset<7>("0000011"), 5, -1}},
    {"lwu", {'I', bitset<7>("0000011"), 6, -1}},

    {"sb", {'S', bitset<7>("0100011"), 0, -1}},
    {"sh", {'S', bitset<7>("0100011"), 1, -1}},
    {"sw", {'S', bitset<7>("0100011"), 2, -1}},
    {"sd", {'S', bitset<7>("0100011"), 3, -1}},

    {"beq", {'B', bitset<7>("1100011"), 0, -1}},
    {"bne", {'B', bitset<7>("1100011"), 1, -1}},
    {"blt", {'B', bitset<7>("1100011"), 4, -1}},
    {"bge", {'B', bitset<7>("1100011"), 5, -1}},
    {"bltu", {'B', bitset<7>("1100011"), 6, -1}},
    {"bgeu", {'B', bitset<7>("1100011"), 7, -1}},

    {"jal", {'J', bitset<7>("1101111"), -1, -1}},
    {"jalr", {'I', bitset<7>("1100111"), 0, -1}},

    {"lui", {'U', bitset<7>("0110111"), -1, -1}},
    {"auipc", {'U', bitset<7>("0010111"), -1, -1}},

};

// Mapping a register and its nickname to int(e.g. x0 = 0)
map<string, int> regDetails = {

    {"x0", 0},   {"zero", 0},

    {"x1", 1},   {"ra", 1},

    {"x2", 2},   {"sp", 2},

    {"x3", 3},   {"gp", 3},

    {"x4", 4},   {"tp", 4},

    {"x5", 5},   {"t0", 5},

    {"x6", 6},   {"t1", 6},

    {"x7", 7},   {"t2", 7},

    {"x8", 8},   {"s0", 8},   {"fp", 8},

    {"x9", 9},   {"s1", 9},

    {"x10", 10}, {"a0", 10},

    {"x11", 11}, {"a1", 11},

    {"x12", 12}, {"a2", 12},

    {"x13", 13}, {"a3", 13},

    {"x14", 14}, {"a4", 14},

    {"x15", 15}, {"a5", 15},

    {"x16", 16}, {"a6", 16},

    {"x17", 17}, {"a7", 17},

    {"x18", 18}, {"s2", 18},

    {"x19", 19}, {"s3", 19},

    {"x20", 20}, {"s4", 20},

    {"x21", 21}, {"s5", 21},

    {"x22", 22}, {"s6", 22},

    {"x23", 23}, {"s7", 23},

    {"x24", 24}, {"s8", 24},

    {"x25", 25}, {"s9", 25},

    {"x26", 26}, {"s10", 26},

    {"x27", 27}, {"s11", 27},

    {"x28", 28}, {"t3", 28},

    {"x29", 29}, {"t4", 29},

    {"x30", 30}, {"t5", 30},

    {"x31", 31}, {"t6", 31},

};

// Mapping a binary to its corresponding hexdigit
map<string, char> hexDigit = {

    {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
    {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
    {"1000", '8'}, {"1001", '9'}, {"1010", 'a'}, {"1011", 'b'},
    {"1100", 'c'}, {"1101", 'd'}, {"1110", 'e'}, {"1111", 'f'},

};

/*Checks whether it is valid register or not*/
bool IsValidRegeister(string s){
    auto it= regDetails.find(s);
    if(it != regDetails.end())
    return true;
    cout<<s<<" is not recognised"<<endl;
    return false;
}

/*Checks whether the given operation is valid or not
e.g. add is valid but did is not a valid operator*/
bool IsValidOperation(string s){
    auto it= Details.find(s);
    if(it != Details.end())
    return true;
    cout<<s<<" is not recognised"<<endl;
    return false;
}