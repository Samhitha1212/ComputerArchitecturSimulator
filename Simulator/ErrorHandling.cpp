#include "ErrorHandling.h"
#include "globalvars.h"
using namespace std;

long int convertToInt(string s) {
  if (s[0] == '0' && s[1] == 'x' || s[0]=='-' && s[1] == '0' && s[2] == 'x') {
    return stol(s, 0, 16);
  } else {
    return stol(s);
  }
}

/*To separate imm value from a given argument like 205(x4)*/
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

/*Checks whether the given instruction is in valid I or R format*/
bool IsvalidIandR(string s,int linenumber){
  bool f=false;
  bool e=false;
  int k=0;
  for( ; k<s.length();k++){
    if(s[k] == '('){
      f=true;
      break;
    }
  }
  if(!f){
    k=0;
  }
  for( ; k<s.length();k++){
    if(s[k] == ')'){
      e=true;
      break;
    }
  }
  if(e && f){
    return true;
  }else if( !e && !f){
    cout<<"ERROR:At line Number: "<<dec<<linenumber<<" Invalid argument "<<s<<" (no paranthesis) "<<endl;
    return false;
  }else {
    cout<<"ERROR:At line Number: "<<dec<<linenumber<<" Invalid argument "<<s<<" (missing paranthesis) "<<endl;
    return false;
  }
}

/*Checks whether the given imm is a valid imm value for the instruction
e.g. -12 or abc34 or 672597 are valid imm but 34,567 is not a valid imm*/
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
    int i=0;
    if(s[0] == '-' || s[0] == '+'){
      i++;
    }
    for(; i < s.length(); i++){
      
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

/*Checks whether the number arguments given in instructions
matches the actual number of instruction that should be present*/
bool IsValidNoOfArguments(string operation,int required , int actual,int linenumber){
  if(required == actual)
  return true;
  cout<<"ERROR:At linenumber: "<<dec<<linenumber<<" the "<<operation<<" expects "<<dec<<required<<" arguments but you gave "<<dec<<actual<<" arguments"<<endl;
  return false;
}

bool IsValidLabel(string s, bool flag) {
  auto it = Labels.find(s);
  if (it != Labels.end())
    return true;
  if(flag)
  cout<<s<<" is not recognised."<<endl;
  return false;
}