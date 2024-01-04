#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "../utils/utils.hpp"
using namespace std;


map<pair<vector<char>, vector<int>>, int> memo;

vector<int> get_spring_order(string line) {
  string delim = ",";
  const char* c_delim = delim.c_str(); 
  char* c_line = new char[line.length() + 1];
  strcpy(c_line, line.c_str());
  vector<int> lois;

  char* token;
  while ((token = strsep(&c_line, c_delim)) != nullptr) {
    try {

    lois.push_back(stoi(token));
    }
    catch (invalid_argument e) {
      //ignore
    }
  }

  return lois;
}

pair<vector<char>, vector<int>> split_input(string line) {
  int split = line.find(" ");
  string p = line.substr(0, split);
  const char *c_pattern = p.c_str();
  vector<char> pattern = vector<char>(c_pattern, c_pattern + strlen(c_pattern));
  vector<int> spring_order = get_spring_order(line.substr(split));

  return make_pair(pattern, spring_order);
}

int permute(pair<vector<char>, vector<int>> row_info) {
  if (memo.find(row_info) != memo.end()) {
    return memo.at(row_info);
  }
  vector<char> pattern = row_info.first;
  vector<int> nums = row_info.second;

  if (pattern.empty()) {
    if (nums.empty()) { 
      return 1;
    }
    else {
      return 0;
    }
  }

  if (nums.empty()) {
    if (std::find(pattern.begin(), pattern.end(), '#') != pattern.end()) {
      return 0;
    }
    else {
      return 1;}
  }

  int count = 0;

  if (pattern.at(0) == '?' || pattern.at(0) == '.') {
    count += permute(make_pair(vector<char>(pattern.begin() + 1, pattern.end()), nums));
  }

  if (pattern.at(0) == '?' || pattern.at(0) == '#') {
    if (nums.at(0) <= pattern.size() && find(pattern.begin(), pattern.begin() + nums.at(0), '.') == pattern.begin() + nums.at(0) && (pattern.size() == nums.at(0) || pattern.at(nums.at(0)) != '#')) {
      if (nums.at(0) == pattern.size()) {
        count += permute(make_pair(vector<char>(), vector<int>(nums.begin() + 1, nums.end())));
      }
      else {
        count += permute(make_pair(vector<char>(pattern.begin() + nums.at(0) + 1, pattern.end()), vector<int>(nums.begin() + 1, nums.end())));
      }
    }
  }

  memo[row_info] = count;
  return count;
}


int main() {
  vector<string> s_row = readlines("single_row.txt");
  vector<string> lines = readlines("data.txt");

  int count = 0;
  for (auto line: lines) {
    pair<vector<char>, vector<int>> info = split_input(line);
    auto res = permute(info);
    count += res;
  }

  cout << count << endl;
}