#include "FMT.h"
#include "operation_map.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#define N 50

using namespace std;

extern map<string, InstructionDetails> Details;
map<string, int> Labels;

int convertToInt(string s) {
  if (s[0] == '0' && s[1] == 'x') {
    return stoi(s, 0, 16);
  } else {
    return stoi(s);
  }
}

string seperateImmediate(string &s) {
  string num = "";
  int k = 0;
  for (; k < s.length(); k++) {
    if (s[k] != '(') {
      num += s[k];
    } else {
      break;
    }
  }

  k++;
  string rs1 = "";
  for (; k < s.length(); k++) {
    if (s[k] != ')') {
      rs1 += s[k];
    } else {
      break;
    }
  }
  s = rs1;
  return num;
}

bool IsValidImmediate(string s) { return true; }

bool IsValidLabel(string s) {
  auto it = Labels.find(s);
  if (it != Labels.end())
    return true;
  return false;
}

int main() {

  ifstream inputfile("input.s");
  string s;
  if (inputfile.is_open()) {

    int instructions = 0;

    string arg[N][4];

    while (inputfile.good()) {

      getline(inputfile, s);
      cout << s << endl;

      if (s != "") {

        int n = 0; // counts no of arguments
        for (int i = 0; i < s.length(); i++) {
          if (s[i] == '#') {
            break;
          } else if (s[i] == ':') {
            n--;
            Labels[arg[instructions][n]] = instructions;
            arg[instructions][n] = "";

          } else if (s[i] != ' ' && s[i] != ',') {
            do {
              arg[instructions][n] += s[i];
              i++;

            } while (i < s.length() && s[i] != ' ' && s[i] != ',' &&
                     s[i] != '#' && s[i] != ':');

            if (s[i] == ':') {
              Labels[arg[instructions][n]] = instructions;
              arg[instructions][n] = "";

            } else {
              n++;
            }
          }
        }

        // check the instruction is valid or not then

        if (n > 0) {
          cout << n << endl;
          instructions++;
        }
      }
    }

    cout << "No: of Labels" << Labels.size() << endl;
    for (auto it = Labels.begin(); it != Labels.end(); it++) {
      cout << it->first << " :" << it->second << endl;
    }

    for (int j = 0; j < instructions; j++) {

      cout << Details[arg[j][0]].FMT << endl;

      if (!IsValidOperation(arg[j][0])) {
        cout << "ERROR:Invalid Operation at Operation Number:" << j << endl;
        continue; // break??
      } else if (!(IsValidRegeister(arg[j][1]))) {
        cout << "ERROR:Invalid Register at Operation Number:" << j << endl;
        continue;
      } else {
        if (Details[arg[j][0]].FMT == 'R') {
          if (!(IsValidRegeister(arg[j][2]) && IsValidRegeister(arg[j][3]))) {
            cout << "ERROR:Invalid Register at Operation Number:" << j << endl;
            continue;
          }
          RType I(arg[j][0], arg[j][1], arg[j][2], arg[j][3]);

        }

        else if (Details[arg[j][0]].FMT == 'I') {

          if (Details[arg[j][0]].opcode == bitset<7>("0010011")) {

            if (!IsValidImmediate(arg[j][3])) {
              cout << "ERROR:Invalid Immediate Value at Operation Number:" << j
                   << endl;
              continue;
            }
            int n = convertToInt(arg[j][3]);

            IType I(arg[j][0], arg[j][1], arg[j][2], n);

          } else if (Details[arg[j][0]].opcode == bitset<7>("0000011") ||
                     Details[arg[j][0]].opcode == bitset<7>("1100111")) {
            string num = seperateImmediate(arg[j][2]);
            if (!IsValidImmediate(arg[j][3])) {
              cout << "ERROR:Invalid Immediate Value at Operation Number:" << j
                   << endl;
              continue;
            }
            int n = convertToInt(num);
            IType I(arg[j][0], arg[j][1], arg[j][2], n);
          }

          if (!(IsValidRegeister(arg[j][2]))) {
            cout << "ERROR:Invalid Register at Operation Number:" << j << endl;
            continue;
          }

        }

        else if (Details[arg[j][0]].FMT == 'S') {
          string num = seperateImmediate(arg[j][2]);
          if (!IsValidImmediate(arg[j][3])) {
            cout << "ERROR:Invalid Immediate Value at Operation Number:" << j
                 << endl;
            continue;
          }
          int n = convertToInt(num);
          if (!(IsValidRegeister(arg[j][2]))) {
            cout << "ERROR:Invalid Register at Operation Number:" << j << endl;
            continue;
          }
          SType I(arg[j][0], arg[j][1], arg[j][2], n);

        }

        else if (Details[arg[j][0]].FMT == 'B') {
          if (!IsValidLabel(arg[j][3])) {
            cout << "ERROR:Invalid Immediate Value at Operation Number:" << j
                 << endl;
            continue;
          }
          int n = Labels[arg[j][3]];
          n = j - n;
          n *= 4;
          if (!(IsValidRegeister(arg[j][2]))) {
            cout << "ERROR:Invalid Register at Operation Number:" << j << endl;
            continue;
          }

          BType I(arg[j][0], arg[j][1], arg[j][2], n);

        }

        else if (Details[arg[j][0]].FMT == 'U') {
          if (!IsValidImmediate(arg[j][2])) {
            cout << "ERROR:Invalid Immediate Value at Operation Number:" << j
                 << endl;
            continue;
          }
          int n = convertToInt(arg[j][2]);

          UType I(arg[j][0], arg[j][1], n);

        }

        else if (Details[arg[j][0]].FMT == 'J') {
          if (!IsValidLabel(arg[j][2])) {
            cout << "ERROR:Invalid Immediate Value at Operation Number:" << j
                 << endl;
            continue;
          }
          int n = Labels[arg[j][2]];
          n = j - n;
          n *= 4;

          JType I(arg[j][0], arg[j][1], n);
        }
      }

      // cout << "Instruction" << j << endl;
      // for (int i = 0; i < 4; i++) {
      //   cout << arg[j][i] << endl;
      // }
    }

  } else {
    cout << "File not opened" << endl;
  }

  return 0;
}
