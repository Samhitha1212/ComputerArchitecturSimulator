#pragma once
#include<iostream>
#include<string>
using namespace std;

long int convertToInt(string s);
string seperateImmediate(string& s);
bool IsvalidIandR(string s, int linenumber);
bool IsValidImmediate(string s, bool flag);
bool IsValidNoOfArguments(string operation, int required, int actual, int linenumber);
bool IsValidLabel(string s, bool flag);