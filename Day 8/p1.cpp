#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../utils/utils.hpp"
using namespace std;


map<string, map<char, string>> nodes;


vector<char> get_directions(vector<string> lines) {
  vector<char> res;
  for (auto &line: lines) {
    const char *c_dir = line.c_str();

    for (const char *p = c_dir; *p != '\0'; ++p) {
      res.push_back(*p);
    }
  }
  return res;
}

void create_nodes(vector<string> lines) {
  for (auto &line: lines) {
    auto n = get_strings(line);
    map<char, string> n_map;
    n_map['L'] = n[2].substr(1, 3);
    n_map['R'] = n[3].substr(0, 3);
    nodes[n[0]] = n_map;
  }
}

int traverse_graph(vector<char> directions) {
  int steps = 0;
  int dir_size = directions.size();
  string cur_node = "AAA";
  while (cur_node != "ZZZ") {
    char cur_dir = directions[steps % dir_size];
    cur_node = nodes[cur_node].at(cur_dir);
    steps += 1;
  }
  return steps;
}


int main() {
  vector<string> lines = readlines("data.txt");
  int i = 0;
  while (lines[i] != "") {
    i++;
  }

  vector<char> directions = get_directions(vector<string>(lines.begin(), lines.begin() + i));
  create_nodes(vector<string>(lines.begin() + i + 1, lines.end()));
  auto res = traverse_graph(directions);
  cout << res << endl;
}