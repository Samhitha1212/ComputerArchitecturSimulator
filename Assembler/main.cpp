#include "FMT.h"
#include "operation_map.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#define N 50

using namespace std;

extern map<string, InstructionDetails> Details;

int convertToInt(string s){
  if(s[0]==0 && s[1]=='x'){
    //In hexadecimal for
    return 0;
  }else{
    return stoi(s);
  }
}

string seperateImmediate(string &s){
  string num="";
          int k=0;
          for (; k<s.length(); k++){
            if(s[k] != '('){
              num+=s[k];
            }else{
              break;
            }
          }
          
          k++;
          string rs1="";
          for(; k<s.length(); k++){
            if(s[k] != ')'){
              rs1+=s[k];
            }else{
              break;
            }
          }
          s=rs1;
          return num;

}
int main() {

  ifstream inputfile("input.s");
  string s;
  if (inputfile.is_open()) {

    int instructions = 0;
    map<string, int> Labels;
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

      if (Details[arg[j][0]].FMT == 'R') {
        RType I(arg[j][0], arg[j][1], arg[j][2], arg[j][3]);

      }

      else if (Details[arg[j][0]].FMT == 'I') {

        if(Details[arg[j][0]].opcode == bitset<7>("0010011")){
          int n = convertToInt(arg[j][3]);

          IType I(arg[j][0],arg[j][1],arg[j][2],n);

        }else if(Details[arg[j][0]].opcode == bitset<7>("0000011")){
         string num=seperateImmediate(arg[j][2]);
         int n=convertToInt(num);
          IType I(arg[j][0],arg[j][1],arg[j][2],n);
        }else if(Details[arg[j][0]].opcode == bitset<7>("1100111")){

        }

      }

      else if (Details[arg[j][0]].FMT == 'S') {
        string num=seperateImmediate(arg[j][2]);
         int n=convertToInt(num);
          SType I(arg[j][0],arg[j][1],arg[j][2],n);

      }

      else if (Details[arg[j][0]].FMT == 'B') {

        int n= Labels[arg[j][3]];
        n=j-n;
        n*=4;

        BType I(arg[j][0],arg[j][1], arg[j][1],n);

      }

      else if (Details[arg[j][0]].FMT == 'U') {

        int n=convertToInt(arg[j][2]);
        UType I(arg[j][0], arg[j][1],n);

      }

      else if (Details[arg[j][0]].FMT == 'J') {
        int n= Labels[arg[j][2]];
        n=j-n;
        n*=4;

        JType I(arg[j][0], arg[j][1],n);

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
