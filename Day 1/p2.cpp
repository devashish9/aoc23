#include<iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

const vector<string> num_strs = {
  "0", 
  "1", 
  "2", 
  "3", 
  "4", 
  "5", 
  "6", 
  "7", 
  "8",
  "9"};

const vector<string> str_nums = {
  "one", 
  "two", 
  "three", 
  "four", 
  "five", 
  "six", 
  "seven", 
  "eight",
  "nine"};

const map<string, string> num_map = {
  {"one", "1"}, 
  {"two", "2"}, 
  {"three", "3"}, 
  {"four", "4"}, 
  {"five", "5"}, 
  {"six", "6"}, 
  {"seven", "7"}, 
  {"eight", "8"}, 
  {"nine", "9"}
};


int processLine(string line) {
  cout << line << '\n';
  map<int, string> found_nums; 

  for(int i = 0; i < num_strs.size(); i++) {
    int loc; 
    for (int j = 0; j < line.length(); j++) {
    if (line.find(num_strs[i], j) != string::npos) {
      loc = line.find(num_strs[i], j);
      found_nums.insert({loc + j, num_strs[i]});
      cout << loc << " : " << num_strs[i] << '\n';
    }
    }
  }

  for(int i = 0; i < str_nums.size(); i++) {
    int loc; 
    for (int j = 0; j < line.length(); j++) {
    if (line.find(str_nums[i], j) != string::npos) {
      loc = line.find(str_nums[i], j);
      // cout << str_nums[i];
      found_nums.insert({loc + j, num_map.at(str_nums[i])});
      cout << loc << " : " << num_map.at(str_nums[i]) << '\n';
    }
    }
  }

  string s = found_nums.begin()->second;
  string e = prev(found_nums.end())->second;
  string concatenated_string = s + e;
  
  return stoi(concatenated_string);
}


int main() {
  std::ifstream my_file;
  my_file.open("data.txt");
  vector <string> lines;
  string curLine;
  int res = 0;

  while(getline(my_file, curLine)) {
    lines.push_back(curLine);
  }

  for(int i = 0; i < lines.size(); i++) {
    curLine = lines[i]; 

    int line_res = processLine(curLine); 
    cout << line_res << '\n';
    res += line_res;
  }

  cout << res;
  return 0;
}