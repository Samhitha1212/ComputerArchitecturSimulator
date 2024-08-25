#include <fstream>
#include <iostream>
#include <map>
#include <string>
#define N 50

using namespace std;

int main() {

  ifstream inputfile("input.txt");
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
    cout << Labels.size() << endl;
    for (auto it = Labels.begin(); it != Labels.end(); it++) {
      cout << it->first << " :" << it->second << endl;
    }
    for (int j = 0; j < instructions; j++) {
      cout << "Instruction" << j << endl;
      for (int i = 0; i < 4; i++) {
        cout << arg[j][i] << endl;
      }
    }

  } else {
    cout << "File not opened" << endl;
  }

  return 0;
}
