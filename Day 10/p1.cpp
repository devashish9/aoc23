#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../utils/utils.hpp"
#include <iterator>
#include <cassert>
#include <stack>
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
};

bool target_found(transition t, vector<vector<char>> graph) {
  pair<int, int> n = {t.move.first.first + t.move.second.first, t.move.first.second + t.move.second.second};
  return graph[n.first][n.second] == 'S';
}

bool valid_transition(transition t, vector<vector<char>> graph) {
  pair<int, int> n = {t.move.first.first + t.move.second.first, t.move.first.second + t.move.second.second};
  auto character = graph[n.first][n.second];
  auto n_transition = make_pair(t.move.second.first *-1, t.move.second.second *-1);
  if (character == '.') {
    return false;
  }
  return transitions[character].first == n_transition || transitions[character].second == n_transition;
}

transition next_transition(transition t, vector<vector<char>> graph) {
  pair<int, int> n = {t.move.first.first + t.move.second.first, t.move.first.second + t.move.second.second};
  auto character = graph[n.first][n.second];
  auto n_transition = make_pair(t.move.second.first *-1, t.move.second.second *-1);

  if (transitions[character].first == n_transition) {
    return {make_pair(n, transitions[character].second), t.steps + 1};
  }
  else return {make_pair(n, transitions[character].first), t.steps + 1};
}

int dfs(pair<int, int> start, vector<vector<char>> graph) {
  stack<transition> s;
  pair<int, int> neighbors[] = {
    {0, 1}, 
    {1, 0}, 
    {0, -1}, 
    {-1, 0}
  };

  for (auto &p: neighbors) {
    s.push({{start, p}, 0});
  }

  while (!s.empty()) {
    auto cur_node = s.top();
    s.pop();

    if (target_found(cur_node, graph)) {
      return cur_node.steps + 1;
    }

    if (valid_transition(cur_node, graph)) {
      auto new_node = next_transition(cur_node, graph);
      s.push(new_node);
    }
  }
  return -1;
}


int main() {
  vector<string> lines = readlines("data.txt");
  auto graph_info = load_graph(lines);
  assert(graph_info.second.first >= 0 && graph_info.second.second >= 0);

  auto result = dfs(graph_info.second, graph_info.first);
  cout << result / 2 << endl;
}
