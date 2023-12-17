#include<iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

map<int, int> cards_won = {};

vector<int> get_nums(string line) {
  string delim = " ";
  const char* c_delim = delim.c_str(); 
  char* c_line = new char[line.length() + 1];
  strcpy(c_line, line.c_str());
  vector<int> lons;

  char* token;
  while ((token = strsep(&c_line, c_delim)) != nullptr) {
    try {

    lons.push_back(stoi(string(token)));
    }
    catch (invalid_argument e) {
      //ignore
    }
  }

  return lons;
}

vector<int> extract_wins(string l) {
  vector<int> res = get_nums(l);
  return vector<int>(res.begin() + 1, res.end());
}

int compute_intersection(vector<int> lows, vector<int> lons) {
  int inter = 0;

  for (auto& obj: lows) {
    if (find(lons.begin(), lons.end(), obj) != lons.end()) {
      inter += 1;
    }
  }
  return inter;
}

int compute_scratch(string line) {
  int split_pos = line.find("|");
  string wins = line.substr(0, split_pos);
  string nums = line.substr(split_pos+2);

  vector<int> lows = get_nums(wins);
  int card = lows[0];
  lows.erase(lows.begin());
  vector<int> lons = get_nums(nums);

  int res = compute_intersection(lows, lons);

  if (cards_won.find(card) == cards_won.end()) {
    cards_won[card] = 0;
  }


  for (int i = card + 1; i <= card + res; i++) {
    cards_won[i] += 1 + cards_won[card];
  }
  return 1 + cards_won[card];
}

int main() {
  std::ifstream my_file;
  my_file.open("data.txt");
  vector <string> lines;
  string curLine;
  int res = 0;

  while(getline(my_file, curLine)) {
    res += compute_scratch(curLine);
  }

  cout << res << endl;
  return res;
}