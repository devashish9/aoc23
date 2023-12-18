#include<iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include "../utils/utils.hpp"
using namespace std;

int main() {
  auto test = readlines("test.txt");
  cout << test[0] << endl;
  return 0;
}