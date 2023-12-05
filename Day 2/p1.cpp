#include<iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

bool check_amt(string color, int num) {
  if (color == "red") {
    return num <= 12;
  }
  else if (color == "green") {
    return num <= 13;
  }
  else {
    return num <= 14;
  }
}

bool valid_set(string g_set) {
  int cur_delim = 0;
  int next_delim;
  string cur_color; 

  while ((next_delim = g_set.find(",", cur_delim)) != string::npos) {
    cur_color = g_set.substr(cur_delim, next_delim - cur_delim);
    int split = cur_color.find(" ");
    string color = cur_color.substr(split+1);
    int amt = stoi(cur_color.substr(0, split+1));
    if (!check_amt(color, amt)) {
      return false;
    }
    cur_delim = next_delim +2;
  }
  cur_color = g_set.substr(cur_delim);
  int split = cur_color.find(" ");
  string color = cur_color.substr(split+1);
  int amt = stoi(cur_color.substr(0, split+1));
  if (!check_amt(color, amt)) {
    return false;
  }
  return true;
}

bool valid_game(string curLine) {
  int game_info_pos = curLine.find(":");
  curLine.erase(0, game_info_pos + 2);
  int cur_delim = 0;
  int next_delim;
  string cur_set;

  while ((next_delim = curLine.find(";", cur_delim)) != string::npos) {
    cur_set = curLine.substr(cur_delim, next_delim - cur_delim);
    cur_delim = next_delim + 2;
    if (!valid_set(cur_set)) {
      return false;
    }
  }
  cur_set = curLine.substr(cur_delim);
  if (!valid_set(cur_set)) {
    return false;
  }
  return true;
}

int main() {
  std::ifstream my_file;
  my_file.open("data.txt");
  vector <string> lines;
  string curLine;
  int res = 0;
  int i = 1;

  while(getline(my_file, curLine)) {
    if (valid_game(curLine)) {
      res += i;
    }
    i += 1;
  }

  cout << res;
  return 0;
}