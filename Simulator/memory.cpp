#include "memory.h"
#include <iostream>

void textSectionClass::writeInstruction(string s) {
  if (mem.size() - top <= 4) {
    mem.resize(top + 4 * S, 0);
  }
  int j = 6;
  for (int i = 0; i < 4; i++, top++) {
    string s1;
    for (int k = 0; k < 2; j++, k++) {
      s1 += s[j];
    }
    j -= 4;
    int n = stoi(s1, 0, 16);
    mem[top] = n;
  }
};

bitset<32> textSectionClass::readInstruction(unsigned int pc) {
  bitset<32> a = 0;
  if (pc >= mem.size()) {
    return a;
  } else {
    int k = 0;
    for (int i = 0; i < 4; i++, pc++) {
      for (int j = 0; j < 8; j++, k++) {
        a[k] = mem[pc][j];
      }
    }
  }
  return a;
}

// address is index
void textSectionClass::writeData(int n, unsigned int address,
                                 bitset<64> value) {
  if (mem.size() - top <= n) {
    mem.resize(top + 4 * S, 0);
  }
  while (address + n - 1 >= mem.size()) {
    mem.resize(address + n - 1, 0);
  }
  if (top < address + n) {
    top = address + n;
  }
  int k = 0;
  for (int i = 0; i < n; i++, address++) {
    for (int j = 0; j < 8; j++, k++) {
      mem[address][j] = value[k];
    }
  }
}

bitset<64> textSectionClass::readData(int n, unsigned int address) {
  bitset<64> a = 0;
  if (address >= mem.size()) {
    return a;
  } else {
    int k = 0;
    for (int i = 0; i < n; i++, address++) {
      for (int j = 0; j < 8; j++, k++) {
        a[k] = mem[address][j];
      }
    }
  }
  return a;
}

// address is index
void dataSectionClass::writeData(int n, unsigned int address,
                                 bitset<64> value) {
  if (mem.size() - top <= n) {
    mem.resize(top + 4 * S, 0);
  }
  while (address + n - 1 >= mem.size()) {
    mem.resize(address + n - 1, 0);
  }
  if (top < address + n) {
    top = address + n;
  }
  int k = 0;
  for (int i = 0; i < n; i++, address++) {
    for (int j = 0; j < 8; j++, k++) {
      mem[address][j] = value[k];
    }
  }
}

void dataSectionClass::writeData(int n, long int value) {
  bitset<64> a = value;
  writeData(n, top, a);
}

bitset<64> dataSectionClass::readData(int n, unsigned int address) {
  bitset<64> a = 0;
  if (address >= mem.size()) {
    return a;
  } else {
    int k = 0;
    for (int i = 0; i < n; i++, address++) {
      for (int j = 0; j < 8; j++, k++) {
        a[k] = mem[address][j];
      }
    }
  }
  return a;
}

// adress is index
void stackSectionClass::writeData(int n, unsigned int address,
                                  bitset<64> value) {
  if (mem.size() - top <= n) {
    mem.resize(top + 4 * S, 0);
  }
  while (address >= mem.size()) {
    mem.resize(address + 1, 0);
  }
  if (top < address + 1) {
    top = address + 1;
  }
  int k = 0;
  for (int i = 0; i < n; i++, address--) {
    for (int j = 0; j < 8; j++, k++) {
      mem[address][j] = value[k];
    }
  }
}

bitset<64> stackSectionClass::readData(int n, unsigned int address) {
  bitset<64> a = 0;
  if (address >= mem.size()) {
    return a;
  } else {
    int k = 0;
    for (int i = 0; i < n; i++, address--) {
      for (int j = 0; j < 8; j++, k++) {
        a[k] = mem[address][j];
      }
    }
  }
  return a;
}

void textSectionClass::printMemmory() const {
  for (int i = 0; i < top; i++) {
    std::cout << "Memory[0x" << hex << i << "] = 0x" << hex << mem[i].to_ulong()
              << endl;
  }

  cout << "From 0x" << hex << top << " to 0x10000 contains 0x00" << endl;
}

void textSectionClass::printMemmory(int n, unsigned int address) const {
  if (address >= mem.size()) {
    for (int i = 0; i < n; i++) {
      std::cout << "Memory[0x" << hex << address + i << "] = 0x" << hex << 0
                << endl;
    }
  } else if (address + n > mem.size()) {
    int r = address + n - mem.size();
    int i = 0;
    for (; i < n - r; i++) {
      std::cout << "Memory[0x" << hex << address + i << "] = 0x" << hex
                << mem[i + address].to_ulong() << endl;
    }
    for (; i < n; i++) {
      std::cout << "Memory[0x" << hex << address + i << "] = 0x" << hex << 0
                << endl;
    }
  } else {
    for (int i = 0; i < n; i++) {
      std::cout << "Memory[0x" << hex << address + i << "] = 0x" << hex
                << mem[i + address].to_ulong() << endl;
    }
  }
}

void dataSectionClass::printMemmory(unsigned int start_address) const {
  for (int i = 0; i < top; i++) {
    std::cout << "Memory[0x" << hex << i + start_address << "] = 0x" << hex
              << mem[i].to_ulong() << endl;
  }

  cout << "From 0x" << hex << top + start_address << " to 0x" << hex
       << (0x10000 + start_address) << " contains 0x00" << endl;
}

void dataSectionClass::printMemmory(unsigned int start_address, int n,
                                    unsigned int address) const {

  if (address >= mem.size()) {
    for (int i = 0; i < n; i++) {
      std::cout << "Memory[0x" << hex << address + i + start_address << "] = 0x"
                << hex << 0 << endl;
    }
  } else if (address + n > mem.size()) {
    int r = address + n - mem.size();
    int i = 0;
    for (; i < n - r; i++) {
      std::cout << "Memory[0x" << hex << address + i + start_address << "] = 0x"
                << hex << mem[i + address].to_ulong() << endl;
    }
    for (; i < n; i++) {
      std::cout << "Memory[0x" << hex << address + i + start_address << "] = 0x"
                << hex << 0 << endl;
    }
  } else {
    for (int i = 0; i < n; i++) {
      std::cout << "Memory[0x" << hex << address + i + start_address << "] = 0x"
                << hex << mem[i + address].to_ulong() << endl;
    }
  }
}

void stackSectionClass::printMemmory() const {

  cout << "From 0x" << hex << 0x40000 << " to 0x" << hex << (0x50000 - top - 1)
       << " contains 0x00" << endl;
  for (int i = top-1; i >= 0;  i--) {
    std::cout << "Memory[0x" << hex << (0x50000 - i - 1) << "] = 0x" << hex
              << mem[i].to_ulong() << endl;
  }
}

void stackSectionClass::printMemmory(int n, unsigned int address) const {

  if (address - n + 1 >= mem.size()) {
    for (int i = 0; i < n; i++) {
      std::cout << "Memory[0x" << hex << (0x50000 - address + i - 1) << "] = 0x"
                << hex << 0 << endl;
    }
  } else if (address >= mem.size()) {
    int r = address - mem.size() + 1;
    int i = 0;
    for (; i < r; i++) {
      std::cout << "Memory[0x" << hex << (0x50000 - address + i - 1) << "] = 0x"
                << hex << 0 << endl;
    }
    for (; i < n; i++) {
      std::cout << "Memory[0x" << hex << (0x50000 - address + i - 1) << "] = 0x"
                << hex << mem[address - i].to_ulong() << endl;
    }
  } else {
    for (int i = 0; i < n; i++) {
      std::cout << "Memory[0x" << hex << (0x50000 - address + i - 1) << "] = 0x"
                << hex << mem[address - i].to_ulong() << endl;
    }
  }
}