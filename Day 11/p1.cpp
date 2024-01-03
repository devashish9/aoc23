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



vector<vector<char>> expand_space(vector<vector<char>> space) {
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

  int expanded_rows = count(rows.begin(), rows.end(), true);
  int expanded_cols = count(cols.begin(), cols.end(), true);
  vector<vector<char>> expanded = {};

  int e_is = 0;
  for (int i = 0; i < space.size() + expanded_rows; i++) {
    int e_js = 0;
    if (rows[i-e_is]) {
        expanded.push_back(vector<char>(space[0].size() + expanded_cols, '.'));
        expanded.push_back(vector<char>(space[0].size() + expanded_cols, '.'));
        i+= 1;
        e_is++;
        continue;
    }
    else {
      expanded.push_back({});
    }
    for (int j = 0; j < space[0].size() + expanded_cols; j++) {
      if (cols[j-e_js]) {
        expanded[i].push_back('.');
        j++;
        e_js++;
      }
      expanded[i].push_back(space[i-e_is][j-e_js]);
    }
  }

  return expanded;
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

long calculate_dist(vector<pair<int, int>> coords) {
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
  vector<vector<char>> expanded_space = expand_space(updated_lines);
  vector<pair<int, int>> coords = find_coords(expanded_space);
  long dist = calculate_dist(coords);
  cout << dist << endl;
}