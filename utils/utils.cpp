#include <string>
#include <fstream>
#include <vector>
#include <functional>
#include <cstring>
using namespace std;

std::vector<std::string> readlines(std::string loc) {
  std::ifstream my_file;
  my_file.open("test.txt");
  vector <string> lines;
  string curLine;

  while(getline(my_file, curLine)) {
    lines.push_back(curLine);
  }

  return lines;
}

template <typename T>
std::vector<T> get_ts(std::string line, std::function<T(char*)> f) {
  string delim = " ";
  const char* c_delim = delim.c_str(); 
  char* c_line = new char[line.length() + 1];
  strcpy(c_line, line.c_str());
  vector<T> lots;

  char* token;
  while ((token = strsep(&c_line, c_delim)) != nullptr) {
    try {

    lots.push_back(f(token));
    }
    catch (invalid_argument e) {
      //ignore
    }
  }

  return lots;
}

std::vector<char> get_chars(std::string line) {
  std::function<char(char*)> func = [](char *c) -> char {
    return *c;
  };
  return get_ts(line, func);
}

std::vector<long> get_longs(std::string line) {
  std::function<long(char*)> func = [](char *c) -> long {
    return stol(string(c));
  };
  return get_ts(line, func);
}

std::vector<string> get_strings(std::string line) {
  std::function<string(char*)> func = [](char *c) -> string {
    return string(c);
  };
  return get_ts(line, func);
}

std::vector<int> get_nums(std::string line) {
  std::function<int(char*)> func = [](char *c) -> int {
    return std::stoi(string(c));
  };
  return get_ts(line, func);
}

