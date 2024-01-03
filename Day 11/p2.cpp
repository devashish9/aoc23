#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "../utils/utils.hpp"
// #include <iterator>
// #include <cassert>
// #include <stack>
using namespace std;

vector<vector<char>> lines_to_chars(vector<string> lines) {
  vector<vector<char>> ch_lines;
  transform(lines.begin(), lines.end(), back_inserter(ch_lines), [](string l) {
    auto c_line = l.c_str();
    return vector<char>(c_line, c_line + strlen(c_line));
  });
  return ch_lines;
}



pair<vector<bool>, vector<bool>> expand_space(vector<vector<char>> space) {
  vector<bool> cols(space[0].size(), true);
  vector<bool> rows(space.size(), true);

  for (int i = 0; i < space.size(); i++) {
    for (int j = 0; j < space[0].size(); j++) {
      if (space[i][j] == '#') {
        cols[j] = false;
        rows[i] = false;
      }
    }
  }

  return make_pair(rows, cols);
}

vector<pair<int, int>> find_coords(vector<vector<char>> space) {
  vector<pair<int, int>> coordinates;
  for (int i = 0; i < space.size(); i++) {
    for (int j = 0; j < space[0].size(); j++) {
      if (space[i][j] == '#') {
        coordinates.push_back(make_pair(i, j));
      }
    }
  }
  return coordinates;
}

long calculate_dist(vector<pair<int, int>> coords, pair<vector<bool>, vector<bool>> empties) {
  long res = 0;
  for (int i = 0; i < coords.size(); i++) {
    int x1 = coords[i].first;
    int y1 = coords[i].second;
    for (int j = i; j < coords.size(); j++) {
      int x2 = coords[j].first;
      int y2 = coords[j].second;
      res += abs(x1 - x2) + abs(y1 - y2);
    }
  }
  return res;
}


int main() {
  vector<string> lines = readlines("data.txt");
  vector<vector<char>> updated_lines = lines_to_chars(lines);
  pair<vector<bool>, vector<bool>> expanded_space = expand_space(updated_lines);
  vector<pair<int, int>> coords = find_coords(updated_lines);
  long dist = calculate_dist(coords, expanded_space);
  cout << dist << endl;
}