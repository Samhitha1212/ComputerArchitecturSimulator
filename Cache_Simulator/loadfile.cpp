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
#include "math.h"
using namespace std;

bool loadfile( string filename){
  bool error = false;
  ifstream inputfile(filename);                                  //input file
  fstream outputfile("output.hex", ios::trunc | ios::in | ios::out);         //output file
  string s;
  int linenumber=1;                          //variable to keep the counter of linenumber
  if (inputfile.is_open()) {


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
              cout<<"ERROR:At line Number "<<dec<<linenumber<<" label: "<<a<<" already exists"<<endl;
              error = true;
            }
            Labels[a] = instructions;
            arg[instructions].pop_back();

          } else if (s[i] != ' ' && s[i] != ',' && s[i] != '\t') {
            do {
              temp += s[i];
              i++;

            } while (i < s.length() && s[i] != ' ' && s[i] != ',' &&
                     s[i] != ';' && s[i] != ':'  && s[i] != '\t');

            if (s[i] == ':') {
              if(IsValidLabel(temp,false)){
              cout<<"ERROR:At line Number "<<dec<<linenumber<<" label: "<<temp<<" already exists"<<endl;
              error = true;
            }
              Labels[temp] = instructions;
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
          for(int i=0; i<s.length(); i++){
            if(s[i] == ';') {
              break;
            }else if(s[i] != ' ' && s[i] != ',') {
            do{
              temp += s[i];
              i++;

            }while (i < s.length() && s[i] != ' ' && s[i] != ',' &&
                     s[i] != ';' );
            int nb=0;
            if(temp == ".dword"){
              nb = 8;
            }else if( temp ==".word"){
              nb = 4;
            }else if( temp ==".half"){
              nb = 2;
            }else if( temp ==".byte"){
              nb = 1;
            }else{
              if(IsValidImmediate(temp,false)){
                cout<<"Error: At line number "<<dec<<linenumber<<" Invalid format for .data segment "<<endl;
                cout<<"Missing key word like .dword , .word , .half , .byte"<<endl;
              }else{
                cout<<"Error: At line number "<<dec<<linenumber<<" Invalid format for .data segment "<<endl;
                cout<<temp<<" is not a valid key word in .data section"<<endl;
              }
              error=true;
              break;
            }
            temp="";
            while( i<s.length()){
              if(s[i] != ' ' && s[i] != ',') {
                do{
                  temp += s[i];
                  i++;

                }while (i < s.length() && s[i] != ' ' && s[i] != ',' && s[i] != ';' );
                if(temp != ""){
                  if(IsValidImmediate(temp,true)){
                  try{
                    unsigned long long int num ;
                   long int num2;
                   bool IsInrange=true;
                    if (temp[0] == '0' && temp[1] == 'x' ) {
                      num= stoull(temp, 0, 16);
                      if(nb!= 8){
                         unsigned long int t= pow(2,nb*8);
                         if(num > t-1){
                             IsInrange=false;
                         }
                      }
                    } else if ( temp[0]=='-' && temp[1] == '0' && temp[2] == 'x') {
                      num2= stoll(temp, 0, 16);
                      num=num2;
                      if(nb!= 8){
                         unsigned long int t= pow(2,nb*8-1);
                         if(num < -t){
                             IsInrange=false;
                         }
                      }

                    } else if(temp[0]=='-'){
                      num2= stoll(temp);
                      num=num2;
                      if(nb!= 8){
                         unsigned long int t= pow(2,nb*8-1);
                         if(num < -t){
                             IsInrange=false;
                         }
                      }
                    }else{
                      num= stoull(temp);
                      if(nb!= 8){
                         unsigned long int t= pow(2,nb*8);
                         if(num > t-1){
                             IsInrange=false;
                         }
                      }
                    }
                  if(IsInrange){
                     Memory.writeData(nb,num);
                  }else{
                  error=true;
                  cout<<"Error: At line number "<<dec<<linenumber<<" :The immediate "<<temp<<" does not fit in "<<dec<<nb<<" bytes."<<endl;
                  break;
                  }

                  }catch(const std::out_of_range& e){
                    error=true;
                    cout<<"Error: At line number "<<dec<<linenumber<<" :The immediate "<<temp<<" does not fit in "<<dec<<nb<<" bytes."<<endl;
                    break;
                  }
                   
                  }else{
                    error=true;
                    cout<<"Error: At line number :"<<dec<<linenumber<<" Invalid Immediate format"<<endl;
                    break;
                  }
                 temp="";
                }
               

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
      if(it->second < instructions){
        break;
      }else{
        cout<<"ERROR:At line number: "<<dec<<LineNumber[it->second]<<" label: "<<it->first<<" does not map to any instruction"<<endl;
        error = true;
      }
    }

    for (int j = 0; j < instructions; j++) {

      if (!IsValidOperation(arg[j][0])) {
        cout << "ERROR:Invalid Operation at LineNumber: "<<dec<<LineNumber[j] << endl;
        error = true;
        continue; // break??
      } else if (!(IsValidRegeister(arg[j][1]))) {
        cout << "ERROR:Invalid Register at LineNumber: "<<dec<<LineNumber[j] << endl;
        error = true;
        continue;
      } else {
        if (Details[arg[j][0]].FMT == 'R') {
          if(!IsValidNoOfArguments(arg[j][0],4,arg[j].size(),LineNumber[j])){
            error = true;
            continue;
          }
          if(!(IsValidRegeister(arg[j][2]) && IsValidRegeister(arg[j][3]))) {
            cout << "ERROR:Invalid Register at LineNumber: "<<dec<<LineNumber[j]<< endl;
            error = true;
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
              error = true;
              continue;
            }
            if (!IsValidImmediate(arg[j][3],true)) {
              cout << "ERROR:Invalid Immediate Value at LineNumber: "<<dec<<LineNumber[j] << endl;
              error = true;
              continue;
            }
            int n = convertToInt(arg[j][3]);
            if (!(IsValidRegeister(arg[j][2]))) {
              cout << "ERROR:Invalid Register at LineNumber: "<<dec<<LineNumber[j]<< endl;
              error = true;
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
            cout<<"ERROR:Invalid Immediate at LineNumber: "<<dec<<LineNumber[j]<< endl;
            cout<<"Immediate value : "<<n<<" doesnot fits in "<<k<<" bits "<<endl;
            error = true;
          }else{
             Memory.textSectionstart.writeInstruction(I.gethexInstruction());
             outputfile<<I.gethexInstruction()<<endl;
          }
            

          } else if (Details[arg[j][0]].opcode == bitset<7>("0000011") ||
                     Details[arg[j][0]].opcode == bitset<7>("1100111")) {
              if(!IsValidNoOfArguments(arg[j][0],3,arg[j].size(),LineNumber[j])){
                error = true;
                continue;
              }
              if(!IsvalidIandR(arg[j][2],LineNumber[j])){
                error = true;
                continue;
              }
              string num = seperateImmediate(arg[j][2]);
              arg[j].push_back(num);
              if (!IsValidImmediate(num ,true)) {
                cout << "ERROR:Invalid Immediate Value at LineNumber: "<<dec<<LineNumber[j] << endl;
                error = true;
                continue;
              }
              int n = convertToInt(num);
              if (!(IsValidRegeister(arg[j][2]))) {
                cout << "ERROR:Invalid Register at LineNumber: "<<dec<<LineNumber[j]<< endl;
                error = true;
                continue;
             }
            IType I(arg[j][0], arg[j][1], arg[j][2], n);
            I.EvaluateInstruction();
            string t=I.gethexInstruction();
            int k=12;
            if(t ==""){
              cout<<"ERROR:Invalid Immediate at LineNumber: "<<dec<<LineNumber[j]<< endl;
              cout<<"Immediate value : "<<n<<" doesnot fits in "<<k<<" bits "<<endl;
              error = true;
            }else{
              Memory.textSectionstart.writeInstruction(I.gethexInstruction());
              outputfile<<I.gethexInstruction()<<endl;
            }
          }
        }

        else if (Details[arg[j][0]].FMT == 'S') {
          if(!IsValidNoOfArguments(arg[j][0],3,arg[j].size(),LineNumber[j])){
            error = true;
            continue;
          }
          if(!IsvalidIandR(arg[j][2],LineNumber[j])){
            error = true;
            continue;
          }
          string num = seperateImmediate(arg[j][2]);
          arg[j].push_back(num);
          if (!IsValidImmediate(num,true)) {
            cout << "ERROR:Invalid Immediate Value at LineNumber: "<<dec<<LineNumber[j]<< endl;
            error = true;
            continue;
          }
          int n = convertToInt(num);
          if (!(IsValidRegeister(arg[j][2]))) {
            cout << "ERROR:Invalid Register at LineNumber: "<<dec<<LineNumber[j]<< endl;
            error = true;
            continue;
          }
          SType I(arg[j][0], arg[j][1], arg[j][2], n);
          I.EvaluateInstruction();
          string t=I.gethexInstruction();
            int k=12;
          if(t ==""){
            cout<<"ERROR:Invalid Immediate at LineNumber: "<<dec<<LineNumber[j]<< endl;
            cout<<"Immediate value : "<<n<<" doesnot fits in "<<k<<" bits "<<endl;
            error = true;
          }else{
             Memory.textSectionstart.writeInstruction(I.gethexInstruction());
             outputfile<<I.gethexInstruction()<<endl;
          }

        }

        else if (Details[arg[j][0]].FMT == 'B') {
          if(!IsValidNoOfArguments(arg[j][0],4,arg[j].size(),LineNumber[j])){
            error = true;
            continue;
          }
          int n;
          if(IsValidLabel(arg[j][3],false)){
            n = Labels[arg[j][3]]-j;
            n *= 4;
          }else if(IsValidImmediate(arg[j][3],false)){
            n=convertToInt(arg[j][3]);
          }else{
            cout << "ERROR:Invalid Label or Immediate as 4th argument at LineNumber: "<<dec<<LineNumber[j]<< endl;
            cout<<arg[j][3]<<" is not recognised"<<endl;
            error = true;
            continue;
          }
                
          if (!(IsValidRegeister(arg[j][2]))) {
            cout << "ERROR:Invalid Register at LineNumber: "<<dec<<LineNumber[j]<< endl;
            error = true;
            continue;
          }

          BType I(arg[j][0], arg[j][1], arg[j][2], n);
          I.EvaluateInstruction();
          string t=I.gethexInstruction();
          if(t ==""){
            cout<<"ERROR:Invalid Immediate at LineNumber: "<<dec<<LineNumber[j]<< endl;
            cout<<"Immediate value : "<<n<<" doesnot fits in 13 bits or not even"<<endl;
            error = true;
          }else{
            Memory.textSectionstart.writeInstruction(I.gethexInstruction());
            outputfile<<I.gethexInstruction()<<endl;
          } 
        }

        else if (Details[arg[j][0]].FMT == 'U') {
          if(!IsValidNoOfArguments(arg[j][0],3,arg[j].size(),LineNumber[j])){
            error = true;
            continue;
          }
          if (!IsValidImmediate(arg[j][2],true)) {
            cout << "ERROR:Invalid Immediate Value at LineNumber: "<<dec<<LineNumber[j]<< endl;
            error = true;
            continue;
          }
          int n = convertToInt(arg[j][2]);

          UType I(arg[j][0], arg[j][1], n);
          I.EvaluateInstruction();
          string t=I.gethexInstruction();
            int k=20;
          if(t ==""){
            cout<<"ERROR:Invalid Immediate at LineNumber: "<<dec<<LineNumber[j]<< endl;
            cout<<"Immediate value : "<<n<<" doesnot fits in "<<k<<" bits "<<endl;
            error = true;
          }else{
             Memory.textSectionstart.writeInstruction(I.gethexInstruction());
             outputfile<<I.gethexInstruction()<<endl;
          }

        }

        else if (Details[arg[j][0]].FMT == 'J') {
          if(!IsValidNoOfArguments(arg[j][0],3,arg[j].size(),LineNumber[j])){
            error = true;
            continue;
          }
          int n;
          if(IsValidLabel(arg[j][2],false)){
            n = Labels[arg[j][2]]-j;
            n *= 4;
          }else if(IsValidImmediate(arg[j][2],false)){
            n=convertToInt(arg[j][2]);
          }else{
            cout << "ERROR:Invalid Label or Immediate as 4th argument at LineNumber: "<<dec<<LineNumber[j]<< endl;
            cout<<arg[j][2]<<" is not recognised"<<endl;
            error = true;
            continue;
          }

          JType I(arg[j][0], arg[j][1], n);
          I.EvaluateInstruction();
          string t=I.gethexInstruction();
          int k=21;
          if(t ==""){
            cout<<"ERROR:Invalid Immediate at LineNumber: "<<dec<<LineNumber[j]<< endl;
            cout<<"Immediate value : "<<n<<" either doesnot fits in "<<k<<" bits or not even"<<endl;
            error = true;
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
  return error;
}