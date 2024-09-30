#include "memory.h"
#include "FMT.h"
#include "operation_map.h"
#include "ErrorHandling.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "globalvars.h"

using namespace std;

void loadfile( string filename){
  ifstream inputfile("input.s");                                  //input file
  fstream outputfile("output.hex", ios::trunc | ios::in | ios::out);         //output file
  string s;
  int linenumber=1;                          //variable to keep the counter of linenumber
  if (inputfile.is_open()) {

    int instructions = 0;

    bool Isdatamode=false;
    while (inputfile.good()) {

      getline(inputfile, s);
      

      if (s != "") {
        if(s==".data"){
          Isdatamode=true;
        }else if(s==".text"){
          Isdatamode=false;
        }else if(!Isdatamode){
           string temp="";
        for (int i = 0; i < s.length(); i++) {
          if (s[i] == ';') {
            break;
          } else if (s[i] == ':') {
            string a=arg[instructions].back();
            if(IsValidLabel(a,false)){
              cout<<"ERROR:At line Number "<<linenumber<<" label: "<<a<<" already exists"<<endl;
            }
            Labels[a] = pair(instructions,linenumber);
            arg[instructions].pop_back();

          } else if (s[i] != ' ' && s[i] != ',') {
            do {
              temp += s[i];
              i++;

            } while (i < s.length() && s[i] != ' ' && s[i] != ',' &&
                     s[i] != ';' && s[i] != ':');

            if (s[i] == ':') {
              if(IsValidLabel(temp,false)){
              cout<<"ERROR:At line Number "<<linenumber<<" label: "<<temp<<" already exists"<<endl;;
            }
              Labels[temp] = pair(instructions,linenumber);
              temp="";

            } else if(s[i]==';'){
              i--;
              }
              else {
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
        }else {
          //find 1 st word
          
          string temp;
          for(int i=0; i<s.length();i++){
             if (s[i] == ';') {
            break;
          } else if(s[i] != ' ' && s[i] != ',') {
            do {
              temp += s[i];
              i++;

            } while (i < s.length() && s[i] != ' ' && s[i] != ',' &&
                     s[i] != ';' );
            int nb=0;
            if(temp == ".dword"){
              nb=8;
            }else if( temp ==".word"){
              nb=4;
            }else if( temp ==".half"){
              nb=2;
            }else if( temp ==".byte"){
              nb=2;
            }
            temp="";
            while( i<s.length()){
              if(s[i] != ' ' && s[i] != ',') {
            do {
              temp += s[i];
              i++;

            }while (i < s.length() && s[i] != ' ' && s[i] != ',' &&
            s[i] != ';' );
            long int num = convertToInt(temp);
            Memory.writeData(nb,num);
            temp="";

            if(s[i]==';'){
              i--;
              break;
            }
            }
             i++;
            }


          }
          }
        }
       
      }
      linenumber++;
    }

    for(auto it=Labels.end();it != Labels.begin();  ){
      it--;
      if(it->second.first < instructions){
        break;
      }else{
        cout<<"ERROR:At line number: "<<it->second.second<<" label: "<<it->first<<" does not map to any instruction"<<endl;
      }
    }

    for (int j = 0; j < instructions; j++) {

      if (!IsValidOperation(arg[j][0])) {
        cout << "ERROR:Invalid Operation at LineNumber: "<<LineNumber[j] << endl;
        continue; // break??
      } else if (!(IsValidRegeister(arg[j][1]))) {
        cout << "ERROR:Invalid Register at LineNumber: "<<LineNumber[j] << endl;
        continue;
      } else {
        if (Details[arg[j][0]].FMT == 'R') {
          if(!IsValidNoOfArguments(arg[j][0],4,arg[j].size(),LineNumber[j])){
            continue;
          }
          if (!(IsValidRegeister(arg[j][2]) && IsValidRegeister(arg[j][3]))) {
            cout << "ERROR:Invalid Register at LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }
          RType I(arg[j][0], arg[j][1], arg[j][2], arg[j][3]);
          I.EvaluateInstruction();
          Memory.textSectionstart.writeInstruction(I.gethexInstruction());
          outputfile<<I.gethexInstruction()<<endl;

        }

        else if (Details[arg[j][0]].FMT == 'I') {

          if (Details[arg[j][0]].opcode == bitset<7>("0010011")) {
            if(!IsValidNoOfArguments(arg[j][0],4,arg[j].size(),LineNumber[j])){
            continue;
            }
            if (!IsValidImmediate(arg[j][3],true)) {
              cout << "ERROR:Invalid Immediate Value at LineNumber: "<<LineNumber[j] << endl;
              continue;
            }
            int n = convertToInt(arg[j][3]);
              if (!(IsValidRegeister(arg[j][2]))) {
            cout << "ERROR:Invalid Register at LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }
            IType I(arg[j][0], arg[j][1], arg[j][2], n);
            I.EvaluateInstruction();
            string t=I.gethexInstruction();
            int k=12;
            if(arg[j][0] == "srai" ||arg[j][0] == "slli" ||arg[j][0] == "srli" ){
              k=6;
            }
          if(t ==""){
            cout<<"ERROR:Invalid Immediate at LineNumber: "<<LineNumber[j]<< endl;
            cout<<"Immediate value : "<<n<<" doesnot fits in "<<k<<" bits "<<endl;
          }else{
             Memory.textSectionstart.writeInstruction(I.gethexInstruction());
             outputfile<<I.gethexInstruction()<<endl;
          }
            

          } else if (Details[arg[j][0]].opcode == bitset<7>("0000011") ||
                     Details[arg[j][0]].opcode == bitset<7>("1100111")) {
             if(!IsValidNoOfArguments(arg[j][0],3,arg[j].size(),LineNumber[j])){
              continue;
             }
             if(!IsvalidIandR(arg[j][2],LineNumber[j])){
              continue;
             }
            string num = seperateImmediate(arg[j][2]);
            if (!IsValidImmediate(num ,true)) {
              cout << "ERROR:Invalid Immediate Value at LineNumber: "<<LineNumber[j] << endl;
              continue;
            }
            int n = convertToInt(num);
              if (!(IsValidRegeister(arg[j][2]))) {
            cout << "ERROR:Invalid Register at LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }
            IType I(arg[j][0], arg[j][1], arg[j][2], n);
            I.EvaluateInstruction();
            string t=I.gethexInstruction();
            int k=12;
          if(t ==""){
            cout<<"ERROR:Invalid Immediate at LineNumber: "<<LineNumber[j]<< endl;
            cout<<"Immediate value : "<<n<<" doesnot fits in "<<k<<" bits "<<endl;
          }else{
             Memory.textSectionstart.writeInstruction(I.gethexInstruction());
             outputfile<<I.gethexInstruction()<<endl;
          }
          }

        }

        else if (Details[arg[j][0]].FMT == 'S') {
           if(!IsValidNoOfArguments(arg[j][0],3,arg[j].size(),LineNumber[j])){
              continue;
             }
             if(!IsvalidIandR(arg[j][2],LineNumber[j])){
              continue;
             }
          string num = seperateImmediate(arg[j][2]);
          if (!IsValidImmediate(num,true)) {
            cout << "ERROR:Invalid Immediate Value at LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }
          int n = convertToInt(num);
          if (!(IsValidRegeister(arg[j][2]))) {
            cout << "ERROR:Invalid Register at LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }
          SType I(arg[j][0], arg[j][1], arg[j][2], n);
          I.EvaluateInstruction();
          string t=I.gethexInstruction();
            int k=12;
          if(t ==""){
            cout<<"ERROR:Invalid Immediate at LineNumber: "<<LineNumber[j]<< endl;
            cout<<"Immediate value : "<<n<<" doesnot fits in "<<k<<" bits "<<endl;
          }else{
             Memory.textSectionstart.writeInstruction(I.gethexInstruction());
             outputfile<<I.gethexInstruction()<<endl;
          }

        }

        else if (Details[arg[j][0]].FMT == 'B') {
           if(!IsValidNoOfArguments(arg[j][0],4,arg[j].size(),LineNumber[j])){
              continue;
             }
          int n;
          if(IsValidLabel(arg[j][3],false)){
            n = Labels[arg[j][3]].first-j;
            n *= 4;
          }else if(IsValidImmediate(arg[j][3],false)){
            n=convertToInt(arg[j][3]);
          }else{
            cout << "ERROR:Invalid Label or Immediate as 4th argument at LineNumber: "<<LineNumber[j]<< endl;
            cout<<arg[j][3]<<" is not recognised"<<endl;
            continue;
          }
          
          
          if (!(IsValidRegeister(arg[j][2]))) {
            cout << "ERROR:Invalid Register at LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }

          BType I(arg[j][0], arg[j][1], arg[j][2], n);
          I.EvaluateInstruction();
          string t=I.gethexInstruction();
          if(t ==""){
            cout<<"ERROR:Invalid Immediate at LineNumber: "<<LineNumber[j]<< endl;
            cout<<"Immediate value : "<<n<<" doesnot fits in 13 bits or not even"<<endl;
          }else{
             Memory.textSectionstart.writeInstruction(I.gethexInstruction());
             outputfile<<I.gethexInstruction()<<endl;
          }
         

        }

        else if (Details[arg[j][0]].FMT == 'U') {
           if(!IsValidNoOfArguments(arg[j][0],3,arg[j].size(),LineNumber[j])){
              continue;
             }
          if (!IsValidImmediate(arg[j][2],true)) {
            cout << "ERROR:Invalid Immediate Value at LineNumber: "<<LineNumber[j]<< endl;
            continue;
          }
          int n = convertToInt(arg[j][2]);

          UType I(arg[j][0], arg[j][1], n);
          I.EvaluateInstruction();
          string t=I.gethexInstruction();
            int k=20;
          if(t ==""){
            cout<<"ERROR:Invalid Immediate at LineNumber: "<<LineNumber[j]<< endl;
            cout<<"Immediate value : "<<n<<" doesnot fits in "<<k<<" bits "<<endl;
          }else{
             Memory.textSectionstart.writeInstruction(I.gethexInstruction());
             outputfile<<I.gethexInstruction()<<endl;
          }

        }

        else if (Details[arg[j][0]].FMT == 'J') {
           if(!IsValidNoOfArguments(arg[j][0],3,arg[j].size(),LineNumber[j])){
              continue;
             }
           int n;
          if(IsValidLabel(arg[j][2],false)){
            n = Labels[arg[j][2]].first-j;
            n *= 4;
          }else if(IsValidImmediate(arg[j][2],false)){
            n=convertToInt(arg[j][2]);
          }else{
            cout << "ERROR:Invalid Label or Immediate as 4th argument at LineNumber: "<<LineNumber[j]<< endl;
            cout<<arg[j][2]<<" is not recognised"<<endl;
            continue;
          }

          JType I(arg[j][0], arg[j][1], n);
          I.EvaluateInstruction();
          string t=I.gethexInstruction();
          int k=21;
          if(t ==""){
            cout<<"ERROR:Invalid Immediate at LineNumber: "<<LineNumber[j]<< endl;
            cout<<"Immediate value : "<<n<<" either doesnot fits in "<<k<<" bits or not even"<<endl;
          }else{
             Memory.textSectionstart.writeInstruction(I.gethexInstruction());
             outputfile<<I.gethexInstruction()<<endl;
          }
        } 
      }
    }

  } else {
    cout << "File not opened" << endl;
  }

  Memory.ReadData(4,0);

}