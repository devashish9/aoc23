#include<iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

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
      if (inter == 0) {
        inter = 1;
      }
      else {
        inter = inter * 2;
      }
    }
  }
  return inter;
}

int compute_scratch(string line) {
  int split_pos = line.find("|");
  // line.
  string wins = line.substr(0, split_pos);
  string nums = line.substr(split_pos+2);

  vector<int> lows = extract_wins(wins);
  vector<int> lons = get_nums(nums);

  int res = compute_intersection(lows, lons);
  return res;
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