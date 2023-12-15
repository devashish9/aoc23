#include<iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

void map_nums(int r, map<int, map<int, map<string, int>>> &m, vector<char> &curLine) {
  m[r] = map<int, map<string, int>>();  
  int w_start = 0;
  int w_end = 0;

  while (w_end < curLine.size()) {
    int s_num = curLine[w_start] - '0';
    if (0 <= s_num && 9 >= s_num) {
      int e_num = curLine[w_end] - '0';
      if (0 <= e_num && 9 >=e_num) {
        w_end += 1;
      }
      if (0 > e_num || 9 < e_num || w_end >= curLine.size()) {
        for (int j=w_start; j < w_end; j++) {
          string num_str = "";
          for (int k = w_start; k < w_end; k++) {
            num_str += curLine[k];
          }
          m[r][j] = {{"start", w_start}, {"end", w_end - 1}, {"num", stoi(num_str)}};
        }
        w_end += 1;
        w_start = w_end;
      }
    }
    else {
      w_end += 1;
      w_start = w_end;
    }
  }
}

void remove_num(map<int, map<int, map<string, int>>> &m, int r, int c, int start, int end) {
  for (int i=start; i <= end; i++) {
    m[r].erase(i);
  }
}

int check_neighbor(map<int, map<int, map<string, int>>> &m, int r, int c) {
  if (m[r].find(c) != m[r].end()) {
    map<string, int> f_dict = m[r].at(c);
    return f_dict["num"];
  }
  return 0;
}

bool check_pre_exist(vector<vector<int>> prods, int row, int col) {
  for (auto& pos: prods) {
    if (pos[0] == row and pos[1] == col) {
      return true;
    }
  }
  return false;
}

int run_instance(map<int, map<int, map<string, int>>> &m, int r, int c, int w, int h) {
  int neighbors[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
  int ns = 0;
  vector<vector<int>> products = {};

  for(int n=0; n < size(neighbors); n++) {
    int n_r = r + neighbors[n][0]; 
    int n_c = c + neighbors[n][1];

    if (n_r >= 0 && n_r < h && n_c >= 0 && n_c < w) {
      int num = check_neighbor(m, n_r, n_c);
      if (num > 0 && !check_pre_exist(products, n_r, m[n_r][n_c]["start"])) {
        vector<int> pos = {n_r, m[n_r][n_c]["start"]};
        products.push_back(pos);
      }
    }
  }

  if (products.size() == 2) {
    int res = 1;
    for (auto& pos: products) {
      res *= m[pos[0]][pos[1]]["num"];
      map<string, int> f_dict = m[pos[0]].at(pos[1]);
      remove_num(m, pos[0], pos[1], f_dict["start"], f_dict["end"]);
    }
    return res;
  }
  else {
    return 0;
  }
}


int run_row(map<int, map<int, map<string, int>>> &m, vector<char> line, int r_index, int h) {
  int l_len = line.size();
  int res = 0;
  for(int c=0; c < l_len; c++) {
    char ch = line[c];
    if(ch == '*') {
      int num = run_instance(m, r_index, c, l_len, h);
      res += num;
    }
  }
  return res;
}

int main() {
  std::ifstream my_file;
  my_file.open("data.txt");
  vector<vector<char>> lines;
  string curLine;
  map<int, map<int, map<string, int>>> captured_nums;

  while(getline(my_file, curLine)) {
    vector<char> char_l(curLine.begin(), curLine.end());
    lines.push_back(char_l);
  }

  for(int i = 0; i < lines.size(); i++) {
    vector<char> char_line = lines[i]; 
    map_nums(i, captured_nums, char_line);
    }
  
  int res = 0;
  for (int i = 0; i < lines.size(); i++) {
    res += run_row(captured_nums, lines[i], i, lines.size());
  }
  cout << res << endl;
}

