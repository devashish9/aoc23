#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../utils/utils.hpp"
#include <iterator>
#include <cassert>
#include <stack>
#include <set>
using namespace std;

map<char, pair<pair<int, int>, pair<int, int>>> transitions = {
    {'|', {{-1, 0}, {1, 0}}},
    {'-', {{0, 1}, {0, -1}}},
    {'L', {{-1, 0}, {0, 1}}},
    {'J', {{-1, 0}, {0, -1}}},
    {'7', {{1, 0}, {0, -1}}},
    {'F', {{1, 0}, {0, 1}}},
};

typedef pair<vector<vector<char>>, pair<int, int>> graph_info;

graph_info load_graph(vector<string> lines) {
  pair<int, int> start = make_pair(-1, -1);
  vector<vector<char>> graph = {};
  for(int i = 0; i < lines.size(); i++) {
    int j = lines[i].find('S');
    if (j != std::string::npos) {
      start = make_pair(i, j);
    }
    auto ch_line = lines[i].c_str();
    vector<char> ch_line_vec(ch_line, ch_line + strlen(ch_line));
    graph.push_back(ch_line_vec);
  }

  return make_pair(graph, start);
}

struct transition {
  pair<pair<int, int>, pair<int, int>> move;
  int steps;
  set<pair<int, int>> path;
};

bool target_found(transition t, vector<vector<char>> graph) {
  pair<int, int> n = {t.move.first.first + t.move.second.first, t.move.first.second + t.move.second.second};
  return n.first >= 0 && n.first < graph.size() && n.second >= 0 && n.second < graph[0].size() && graph[n.first][n.second] == 'S';
}

bool valid_transition(transition t, vector<vector<char>> graph) {
  pair<int, int> n = {t.move.first.first + t.move.second.first, t.move.first.second + t.move.second.second};
  if (n.first >= 0 && n.first < graph.size() && n.second >= 0 && n.second < graph[0].size()) {
    auto character = graph[n.first][n.second];
    auto n_transition = make_pair(t.move.second.first *-1, t.move.second.second *-1);
    if (character == '.') {
      return false;
    }
    return transitions[character].first == n_transition || transitions[character].second == n_transition;
  }
  else {
    return false;
  }
}

transition next_transition(transition t, vector<vector<char>> graph) {
  pair<int, int> n = {t.move.first.first + t.move.second.first, t.move.first.second + t.move.second.second};
  auto character = graph[n.first][n.second];
  auto n_transition = make_pair(t.move.second.first *-1, t.move.second.second *-1);
  t.path.insert(n);

  if (transitions[character].first == n_transition) {
    return {make_pair(n, transitions[character].second), t.steps + 1, t.path};
  }
  else return {make_pair(n, transitions[character].first), t.steps + 1, t.path};
}

set<pair<int, int>> dfs(pair<int, int> start, vector<vector<char>> graph) {
  stack<transition> s;
  pair<int, int> neighbors[] = {
    {0, 1}, 
    {1, 0}, 
    {0, -1}, 
    {-1, 0}
  }; 

  for (auto &p: neighbors) {
    s.push({{start, p}, 0, {start}});
  }

  while (!s.empty()) {
    auto cur_node = s.top();
    s.pop();

    if (target_found(cur_node, graph)) {
      return cur_node.path; 
    }

    if (valid_transition(cur_node, graph)) {
      auto new_node = next_transition(cur_node, graph);
      s.push(new_node);
    }
  }
  return {};
}

bool is_n_facing(char c) {
  return c == 'L' || c == 'J' || c == '|';
}

int count_tiles(set<pair<int, int>> path, vector<vector<char>> graph) {
  int total_tiles = 0;
  for (int i = 0; i < graph.size(); i++) {
    bool inside = false;
    int row_count = 0;
    for (int j = 0; j < graph[0].size(); j++) {
      if (path.find(make_pair(i, j)) != path.end()) {
        if (is_n_facing(graph[i][j])) {
          inside = !inside;
        }
      }
      else {
        if (inside) {
          row_count++;
        }
      }
    }
    total_tiles += row_count;
  }
  return total_tiles;
}


int main() {
  vector<string> lines = readlines("data.txt");
  auto graph_info = load_graph(lines);
  assert(graph_info.second.first >= 0 && graph_info.second.second >= 0);
  cout << "Graph loaded" << endl;
  auto path = dfs(graph_info.second, graph_info.first);
  cout << "Path found" << endl;
  auto total_tiles = count_tiles(path, graph_info.first);
  cout << total_tiles << endl;
}