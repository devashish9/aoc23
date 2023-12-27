#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../utils/utils.hpp"
#include <iterator>
using namespace std;


int extrapolate(vector<long> line) {
  copy(line.begin(), line.end(), std::ostream_iterator<long>(std::cout, " "));
  cout << endl;
  vector<long> diff;
  bool non_zero = line.back() != 0;
  for(int i = line.size() - 1; i > 0; i--) {
    auto cur_diff = line.at(i) - line.at(i - 1);
    diff.insert(diff.begin(), cur_diff);
    if (line.at(i) != 0) {
      non_zero = true;
    }
  }


  if (!non_zero) {
    cout << line.front() << endl;
    return line.front();
  }
  else {
    cout << line.front() << endl;
    return line.front() - extrapolate(diff);
  }
}



int main() {
  vector<string> lines = readlines("data.txt");
  int res = 0;
  for (auto& line: lines) {
    auto cur = extrapolate(get_longs(line));
    cout << cur << endl << endl;
    res += cur;
  }
  cout << res << endl;
  return res;
}