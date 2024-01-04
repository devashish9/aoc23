#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "../utils/utils.hpp"
using namespace std;

vector<vector<char>> lines_to_chars(vector<string> lines) {
  vector<vector<char>> ch_lines;
  transform(lines.begin(), lines.end(), back_inserter(ch_lines), [](string l) {
    auto c_line = l.c_str();
    return vector<char>(c_line, c_line + strlen(c_line));
  });
  return ch_lines;
}

pair<vector<int>, vector<int>> expand_space(vector<vector<char>> space) {
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

  vector<int> true_rows;
  vector<int> true_cols;
  for (int i = 0; i < rows.size(); i++) {
    if (rows[i]) {
      true_rows.push_back(i);
    }
  }
  for (int j = 0; j < cols.size(); j++) {
    if (cols[j]) {
      true_cols.push_back(j);
    }
  }
  return make_pair(true_rows, true_cols);
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

long calculate_dist(vector<pair<int, int>> coords, pair<vector<int>, vector<int>> empties) {
  long res = 0;
  for (int i = 0; i < coords.size(); i++) {
    int x1 = coords[i].first;
    int y1 = coords[i].second;
    for (int j = i; j < coords.size(); j++) {
      long dist = 0;
      int x2 = coords[j].first;
      int y2 = coords[j].second;

      int rows = 0;
      for (auto row:empties.first) {
        if ((row > x1 && row < x2) || (row < x1 && row > x2)) {
          dist += 1000000;
          rows += 1;
        }
      }

      int cols = 0;
      for (auto col:empties.second) {
        if ((col > y1 && col < y2) || (col < y1 && col > y2)) {
          dist += 1000000;
          cols += 1;
        }
      }

      res += abs(x1 - x2) + abs(y1 - y2) + dist - rows - cols;
    }
  }
  return res;
}


int main() {
  vector<string> lines = readlines("data.txt");
  vector<vector<char>> updated_lines = lines_to_chars(lines);
  pair<vector<int>, vector<int>> expanded_space = expand_space(updated_lines);
  vector<pair<int, int>> coords = find_coords(updated_lines);
  long dist = calculate_dist(coords, expanded_space);
  cout << dist << endl;
}