#include<iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include "../utils/utils.hpp"
using namespace std;


#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <iterator>
#include "../utils/utils.hpp"
#include <math.h>
using namespace std;


long parse_num_vector(vector<string> lines) {
  string result_string; 

  for (auto &line: lines) {
    auto res = get_strings(line);
    for (auto &str: res) {
      try {
        stol(str);
        result_string.append(str);
      }
      catch (invalid_argument e) {
        //ignore
      }
    }
  }
  cout << result_string << endl;
  return stol(result_string);
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

  long time = parse_num_vector(vector<string>(input.begin(), input.begin() + line));
  long record = parse_num_vector(vector<string>(input.begin() + line, input.end()));

  cout << time << " " << record << endl;

  auto res = calculate_possibilities(time, record);

  cout << res << endl;

  return 0;
}