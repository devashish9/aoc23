#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
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

vector<string> create_nodes(vector<string> lines) {
  vector<string> s_nodes;
  for (auto &line: lines) {
    auto n = get_strings(line);
    map<char, string> n_map;
    n_map['L'] = n[2].substr(1, 3);
    n_map['R'] = n[3].substr(0, 3);
    nodes[n[0]] = n_map;
    if (n[0][2] == 'A') {
      s_nodes.push_back(n[0]);
    }
  }
  return s_nodes;
}

vector<int> traverse_graph(vector<string> s_nodes, vector<char> directions) {
  int steps = 0;
  int dir_size = directions.size();
  char cur_dir;
  vector<int> t_to_z = {0, 0, 0, 0, 0, 0};
  int zs = 0;
  while (true) {
    cur_dir = directions[steps % dir_size];
    string cur_node;
    steps += 1;
    for (int i = 0; i < s_nodes.size(); i++) {
      cur_node = nodes[s_nodes[i]].at(cur_dir);
      if (cur_node[2] == 'Z') {
        t_to_z[i] = steps / dir_size;
        zs += 1;
      }
      s_nodes[i] = cur_node;
    }
    if (zs == s_nodes.size()) {
      break;
    } 
  }
  return t_to_z;
}


int main() {
  vector<string> lines = readlines("data.txt");
  int i = 0;
  while (lines[i] != "") {
    i++;
  }

  vector<char> directions = get_directions(vector<string>(lines.begin(), lines.begin() + i));
  auto starting_nodes = create_nodes(vector<string>(lines.begin() + i + 1, lines.end()));
  auto res = traverse_graph(starting_nodes, directions);
  long product = 1;
  for(auto &s : res) {
    product *= s;
  }
  cout << product * directions.size() << endl;
}
