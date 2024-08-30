#include "FMT.h"
#include "operation_map.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#define N 200

using namespace std;

extern map<string, InstructionDetails> Details;
map<string, int> Labels;
map<int,int>LineNumber;

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

bool IsValidImmediate(string s, bool flag){

  if(s[0] == '0' && s[1] == 'x'){
    for(int i=2; i<s.length(); i++){
      if( (s[i] >= '0' && s[i] <= '9' ) || (s[i] >= 'a' && s[i] <= 'f' ) || (s[i] >= 'A' && s[i] <= 'F')){

      }
      else{
        if(flag)
        cout<<s<<" is not recognised"<<endl;
        return false;
      }  
    }
  }
  else{
    for(int i = 0; i < s.length(); i++){
      if(s[i] >= '0' && s[i] <= '9'){}
      else{
        if(flag)
        cout<<s<<" is not recognised"<<endl;
        return false;
      }
    }
  }
  
  return true;
}

bool IsValidLabel(string s, bool flag) {
  auto it = Labels.find(s);
  if (it != Labels.end())
    return true;
  if(flag)
  cout<<s<<" is not recognised."<<endl;
  return false;
}

bool IsValidNoOfArguments(string operation,int required , int actual,int linenumber){
  if(required == actual)
  return true;
  cout<<"At linenumber: "<<linenumber<<" the "<<operation<<" expects "<<required<<" arguments but you gave "<<actual<<" arguments"<<endl;
  return false;
}
int main() {

  ifstream inputfile("Rtestcases.s");
  fstream outputfile("output.hex");
  string s;
  int linenumber=1;
  if (inputfile.is_open()) {

    int instructions = 0;

   vector <string >arg[N];

    while (inputfile.good()) {

      getline(inputfile, s);
      

      if (s != "") {
        string temp="";
        for (int i = 0; i < s.length(); i++) {
          if (s[i] == '#') {
            break;
          } else if (s[i] == ':') {
            string a=arg[instructions].back();
            Labels[a] = instructions;
            arg[instructions].pop_back();

          } else if (s[i] != ' ' && s[i] != ',') {
            do {
              temp += s[i];
              i++;

            } while (i < s.length() && s[i] != ' ' && s[i] != ',' &&
                     s[i] != '#' && s[i] != ':');

            if (s[i] == ':') {
              Labels[temp] = instructions;
              temp="";

            } else {
              arg[instructions].push_back(temp);
              temp="";
            }
          }
        }

        // check the instruction is valid or not then

        if (arg[instructions].size() > 0) {
          LineNumber[instructions]=linenumber;
          instructions++;
        }
      }
      linenumber++;
    }

    // cout << "No: of Labels" << Labels.size() << endl;
    // for (auto it = Labels.begin(); it != Labels.end(); it++) {
    //   cout << it->first << " :" << it->second << endl;
    // }

    for (int j = 0; j < instructions; j++) {

      

      if (!IsValidOperation(arg[j][0])) {
        cout << "ERROR:Invalid Operation at Operation Number:" << j<<" LineNumber: "<<LineNumber[j] << endl;
        continue; // break??
      } else if (!(IsValidRegeister(arg[j][1]))) {
        cout << "ERROR:Invalid Register at Operation Number:" << j <<" LineNumber: "<<LineNumber[j] << endl;
        continue;
      } else {
        if (Details[arg[j][0]].FMT == 'R') {
          if(!IsValidNoOfArguments(arg[j][0],4,arg[j].size(),LineNumber[j])){
            continue;
          }
          if (!(IsValidRegeister(arg[j][2]) && IsValidRegeister(arg[j][3]))) {
            cout << "ERROR:Invalid Register at Operation Number:" << j <<" LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }
          RType I(arg[j][0], arg[j][1], arg[j][2], arg[j][3]);
          I.EvaluateInstruction();
          outputfile<<I.gethexInstruction()<<endl;

        }

        else if (Details[arg[j][0]].FMT == 'I') {

          if (Details[arg[j][0]].opcode == bitset<7>("0010011")) {
            if(!IsValidNoOfArguments(arg[j][0],4,arg[j].size(),LineNumber[j])){
            continue;
            }
            if (!IsValidImmediate(arg[j][3],true)) {
              cout << "ERROR:Invalid Immediate Value at Operation Number:" << j
                  <<" LineNumber: "<<LineNumber[j] << endl;
              continue;
            }
            int n = convertToInt(arg[j][3]);
              if (!(IsValidRegeister(arg[j][2]))) {
            cout << "ERROR:Invalid Register at Operation Number:" << j <<" LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }
            IType I(arg[j][0], arg[j][1], arg[j][2], n);
            I.EvaluateInstruction();
            outputfile<<I.gethexInstruction()<<endl;

          } else if (Details[arg[j][0]].opcode == bitset<7>("0000011") ||
                     Details[arg[j][0]].opcode == bitset<7>("1100111")) {
             if(!IsValidNoOfArguments(arg[j][0],3,arg[j].size(),LineNumber[j])){
              continue;
             }
            string num = seperateImmediate(arg[j][2]);
            if (!IsValidImmediate(num ,true)) {
              cout << "ERROR:Invalid Immediate Value at Operation Number:" << j
                  <<" LineNumber: "<<LineNumber[j] << endl;
              continue;
            }
            int n = convertToInt(num);
              if (!(IsValidRegeister(arg[j][2]))) {
            cout << "ERROR:Invalid Register at Operation Number:" << j <<" LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }
            IType I(arg[j][0], arg[j][1], arg[j][2], n);
            I.EvaluateInstruction();
            outputfile<<I.gethexInstruction()<<endl;
          }

        }

        else if (Details[arg[j][0]].FMT == 'S') {
           if(!IsValidNoOfArguments(arg[j][0],3,arg[j].size(),LineNumber[j])){
              continue;
             }
          string num = seperateImmediate(arg[j][2]);
          if (!IsValidImmediate(num,true)) {
            cout << "ERROR:Invalid Immediate Value at Operation Number:" << j
                 <<" LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }
          int n = convertToInt(num);
          if (!(IsValidRegeister(arg[j][2]))) {
            cout << "ERROR:Invalid Register at Operation Number:" << j <<" LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }
          SType I(arg[j][0], arg[j][1], arg[j][2], n);
          I.EvaluateInstruction();
          outputfile<<I.gethexInstruction()<<endl;

        }

        else if (Details[arg[j][0]].FMT == 'B') {
           if(!IsValidNoOfArguments(arg[j][0],4,arg[j].size(),LineNumber[j])){
              continue;
             }
          int n;
          if(IsValidLabel(arg[j][3],false)){
            n = Labels[arg[j][3]]-j;
            n *= 4;
          }else if(IsValidImmediate(arg[j][3],false)){
            n=convertToInt(arg[j][3]);
          }else{
            cout << "ERROR:Invalid Label or Immediate as 4th argument at Operation Number:" << j
                 <<" LineNumber: "<<LineNumber[j]<< endl;
            cout<<arg[j][3]<<" is not recognised"<<endl;
            continue;
          }
          
          
          if (!(IsValidRegeister(arg[j][2]))) {
            cout << "ERROR:Invalid Register at Operation Number:" << j <<" LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }

          BType I(arg[j][0], arg[j][1], arg[j][2], n);
          I.EvaluateInstruction();
          outputfile<<I.gethexInstruction()<<endl;

        }

        else if (Details[arg[j][0]].FMT == 'U') {
           if(!IsValidNoOfArguments(arg[j][0],3,arg[j].size(),LineNumber[j])){
              continue;
             }
          if (!IsValidImmediate(arg[j][2],true)) {
            cout << "ERROR:Invalid Immediate Value at Operation Number:" << j
                 <<" LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }
          int n = convertToInt(arg[j][2]);

          UType I(arg[j][0], arg[j][1], n);
          I.EvaluateInstruction();
          outputfile<<I.gethexInstruction()<<endl;

        }

        else if (Details[arg[j][0]].FMT == 'J') {
           if(!IsValidNoOfArguments(arg[j][0],3,arg[j].size(),LineNumber[j])){
              continue;
             }
           int n;
          if(IsValidLabel(arg[j][2],false)){
            n = Labels[arg[j][2]]-j;
            n *= 4;
          }else if(IsValidImmediate(arg[j][2],false)){
            n=convertToInt(arg[j][2]);
          }else{
            cout << "ERROR:Invalid Label or Immediate as 4th argument at Operation Number:" << j
                 <<" LineNumber: "<<LineNumber[j]<< endl;
            cout<<arg[j][2]<<" is not recognised"<<endl;
            continue;
          }

          JType I(arg[j][0], arg[j][1], n);
          I.EvaluateInstruction();
          outputfile<<I.gethexInstruction()<<endl;
        }

          
      }


    
    }

  } else {
    cout << "File not opened" << endl;
  }

  return 0;
}
