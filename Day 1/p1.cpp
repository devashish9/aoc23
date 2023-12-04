#include<iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main() {
  std::ifstream my_file;
  my_file.open("data.txt");
  vector <string> lines;
  string curLine;

  while(getline(my_file, curLine)) {
    lines.push_back(curLine);
  }

  int res = 0;

  for(int i = 0; i < lines.size(); i++) {
    curLine = lines[i]; 
    char lineArr[curLine.length() + 1];
    strcpy(lineArr, curLine.c_str());

    int front = 0;
    int back = sizeof(lineArr) - 2;
    while(!((0 <= (lineArr[front] - '0')) && ((lineArr[front] - '0') <= 9))) {
      front++;
    }

    while(!((0 <= (lineArr[back] - '0')) && ((lineArr[back] - '0') <= 9))) {
      back--;
    }

    int numRes = stoi(string(1, lineArr[front])+lineArr[back]);
    res += numRes;
  }
  cout << res << "\n";
  return 0;
}
