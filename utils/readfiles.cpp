#include<iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

int main() {
  std::ifstream my_file;
  my_file.open("test.txt");
  vector <string> lines;
  string curLine;

  while(getline(my_file, curLine)) {
    lines.push_back(curLine);
  }

}