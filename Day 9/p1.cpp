#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../utils/utils.hpp"
#include <iterator>
using namespace std;


int extrapolate(vector<long> line) {
  vector<long> diff;
  bool non_zero = line[0] != 0;
  for(int i = 1; i < line.size(); i++) {
    auto cur_diff = line[i] - line[i-1];
    diff.push_back(cur_diff);
    if (line[i] != 0) {
      non_zero = true;
    }
  }


  if (!non_zero) {
    return line.back();
  }
  else {
    return line.back() + extrapolate(diff);
  }
}



int main() {
  vector<string> lines = readlines("data.txt");
  int res = 0;
  for (auto& line: lines) {
    auto cur = extrapolate(get_longs(line));
    res += cur;
  }
  cout << res << endl;
  return res;
}



