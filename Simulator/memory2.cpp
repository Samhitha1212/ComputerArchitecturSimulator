#include "memory.h"
#include <iostream>

void MemoryClass::writeInstruction(string s) {
  if(textSectionstart.top +4 <= 0x10000){
     textSectionstart.writeInstruction(s);
  }
 
}
bitset<32> MemoryClass::readInstruction(unsigned int pc) {
  if (pc >= 0 && pc < 0x10000) {
    return textSectionstart.readInstruction(pc);
  }
  return 0;
}

bitset<64> MemoryClass::ReadData(int n, unsigned int address) {
  if (address >= 0 && address < 0x10000) {
    if (address + n <= 0x10000) {
      return textSectionstart.readData(n, address);
    } else {
      int r = 0x10000 - address;
      bitset<64> a = textSectionstart.readData(n - r, address);
      bitset<64> b = dataSectionstart.readData(r, 0);
      int ia = 8 * (n - r);
      int ib = 0;
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < 8; j++, ia++, ib++) {
          a[ia] = b[ib];
        }
      }
      return a;
    }

  } else if (address >= 0x10000 && address < 0x20000) {
    if (address + n <= 0x20000) {
      return dataSectionstart.readData(n, address - 0x10000);
    } else {
      int r = 0x20000 - address;
      bitset<64> a = dataSectionstart.readData(n - r, address - 0x10000);
      bitset<64> b = dataSection2.readData(r, 0);
      int ia = 8 * (n - r);
      int ib = 0;
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < 8; j++, ia++, ib++) {
          a[ia] = b[ib];
        }
      }
      return a;
    }

  } else if (address >= 0x20000 && address < 0x30000) {
    if (address + n <= 0x30000) {
      return dataSection2.readData(n, address - 0x20000);
    } else {
      int r = 0x30000 - address;
      bitset<64> a = dataSection2.readData(n - r, address - 0x20000);
      bitset<64> b = dataSection3.readData(r, 0);
      int ia = 8 * (n - r);
      int ib = 0;
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < 8; j++, ia++, ib++) {
          a[ia] = b[ib];
        }
      }
      return a;
    }

  } else if (address >= 0x30000 && address < 0x40000) {
    if (address + n <= 0x40000) {
      return dataSection3.readData(n, address - 0x30000);
    } else {
      int r = 0x40000 - address;
      bitset<64> a = dataSection3.readData(n - r, address - 0x30000);
      bitset<64> b = stackSection.readData(r, 0x10000 - 1);
      int ia = 8 * (n - r);
      int ib = 0;
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < 8; j++, ia++, ib++) {
          a[ia] = b[ib];
        }
      }
      return a;
    }

  } else if (address >= 0x40000 && address < 0x50000) {
    if (address + n <= 0x50000) {
      return stackSection.readData(n, 0x50000 - address - 1);
    }
  }
  return 0;
}
void MemoryClass::WriteData(int n, unsigned int address, bitset<64> value) {
  if (address >= 0 && address < 0x10000) {
    if (address + n <= 0x10000) {
      textSectionstart.writeData(n, address, value);
    } else {
      int r = 0x10000 - address;
      bitset<64> a = 0;
      bitset<64> b = 0;
      int iv = 0;
      int ia = 0;
      int ib = 0;
      for (int i = 0; i < n - r; i++) {
        for (int j = 0; j < 8; j++, iv++, ia++) {
          a[ia] = value[iv];
        }
      }
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < 8; j++, iv++, ib++) {
          b[ia] = value[iv];
        }
      }
      textSectionstart.writeData(n - r, address, a);
      dataSectionstart.writeData(r, 0, b);
    }

  } else if (address >= 0x10000 && address < 0x20000) {
    if (address + n <= 0x20000) {
      dataSectionstart.writeData(n, address - 0x10000, value);
    } else {
      int r = 0x20000 - address;
      bitset<64> a = 0;
      bitset<64> b = 0;
      int iv = 0;
      int ia = 0;
      int ib = 0;
      for (int i = 0; i < n - r; i++) {
        for (int j = 0; j < 8; j++, iv++, ia++) {
          a[ia] = value[iv];
        }
      }
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < 8; j++, iv++, ib++) {
          b[ia] = value[iv];
        }
      }
      dataSectionstart.writeData(n - r, address - 0x10000, a);
      dataSection2.writeData(r, 0, b);
    }

  } else if (address >= 0x20000 && address < 0x30000) {
    if (address + n <= 0x30000) {
      dataSection2.writeData(n, address - 0x20000, value);
    } else {
      int r = 0x30000 - address;
      bitset<64> a = 0;
      bitset<64> b = 0;
      int iv = 0;
      int ia = 0;
      int ib = 0;
      for (int i = 0; i < n - r; i++) {
        for (int j = 0; j < 8; j++, iv++, ia++) {
          a[ia] = value[iv];
        }
      }
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < 8; j++, iv++, ib++) {
          b[ia] = value[iv];
        }
      }
      dataSection2.writeData(n - r, address - 0x20000, a);
      dataSection3.writeData(r, 0, b);
    }

  } else if (address >= 0x30000 && address < 0x40000) {
    if (address + n <= 0x40000) {
      dataSection3.writeData(n, address - 0x30000, value);
    } else {
      int r = 0x40000 - address;
      bitset<64> a = 0;
      bitset<64> b = 0;
      int iv = 0;
      int ia = 0;
      int ib = 0;
      for (int i = 0; i < n - r; i++) {
        for (int j = 0; j < 8; j++, iv++, ia++) {
          a[ia] = value[iv];
        }
      }
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < 8; j++, iv++, ib++) {
          b[ia] = value[iv];
        }
      }
      dataSection3.writeData(n - r, address - 0x30000, a);
      stackSection.writeData(r, 0x10000 - 1, b);
    }

  } else if (address >= 0x40000 && address < 0x50000) {
    if (address + n <= 0x50000) {
      stackSection.writeData(n, 0x50000 - address - 1, value);
    }
  }
}
void MemoryClass::writeData(int n, long int value) {
  dataSectionstart.writeData(n, value);
}

 void MemoryClass:: printMemory()const{
  textSectionstart.printMemmory();
  dataSectionstart.printMemmory(0x10000);
  dataSection2.printMemmory(0x20000);
  dataSection3.printMemmory(0x20000);
  stackSection.printMemmory();
  std::cout<<endl;

 }


void  MemoryClass::printMemory( int n , unsigned int address){
 if (address >= 0 && address < 0x10000) {
    if (address + n <= 0x10000) {
       textSectionstart.printMemmory(n, address);
    } else {
      int r = 0x10000 - address;
      textSectionstart.printMemmory(n - r, address);
      dataSectionstart.printMemmory(0x10000,r, 0);
     
    }

  } else if (address >= 0x10000 && address < 0x20000) {
    if (address + n <= 0x20000) {
      dataSectionstart.printMemmory(0x10000,n, address-0x10000);
    } else {
      int r = 0x20000 - address;
      dataSectionstart.printMemmory(0x10000,n-r, address-0x10000);
      dataSection2.printMemmory(0x20000,r, 0);
    }

  } else if (address >= 0x20000 && address < 0x30000) {
    if (address + n <= 0x30000) {
         dataSection2.printMemmory(0x20000,n, address-0x20000);
    } else {
      int r = 0x30000 - address;
      dataSection2.printMemmory(0x20000,n-r, address-0x20000);
      dataSection3.printMemmory(0x30000,r, 0);

    }

  } else if (address >= 0x30000 && address < 0x40000) {
    if (address + n <= 0x40000) {
       dataSection3.printMemmory(0x30000,n, address-0x30000);
    } else {
      int r = 0x40000 - address;
      dataSection3.printMemmory(0x30000,n-r, address-0x30000);
      stackSection.printMemmory(r, 0x10000-1);
   
    }

  } else if (address >= 0x40000 && address < 0x50000) {
    if (address + n <= 0x50000) {
      stackSection.printMemmory(n, 0x50000-1-address);
    }
  }
}