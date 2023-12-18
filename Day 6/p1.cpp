#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <iterator>
#include "../utils/utils.hpp"
#include <math.h>
using namespace std;


vector<long> parse_num_vector(vector<string> lines) {
  vector<long> lons;

  for (auto &line: lines) {
    auto res = get_nums(line);
    lons.insert(lons.end(), res.begin(), res.end());
  }
  return lons;
}

long calculate_possibilities(long time, long record) {
  long half = time / 2;

  while (half * (time - half) > record) {
    half -= 1;
  }

  return (time / 2 - half) * 2 - ((time + 1) % 2);
}


int main() {
  vector<string> input = readlines("data.txt");
  long line = 0;
  while (input[line].find("Distance", 0) == string::npos) {
    line += 1;
  }

  vector<long> times = parse_num_vector(vector<string>(input.begin(), input.begin() + line));
  vector<long> records = parse_num_vector(vector<string>(input.begin() + line, input.end()));

  long product = 1;

  for(long i = 0; i < times.size(); i++) {
    auto res = calculate_possibilities(times[i], records[i]);
    product *= res;
  }

  cout << product << endl;

  return 0;
}