#include<iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

class Cubes {
  public: 
    int reds;
    int greens;
    int blues;
    Cubes() {
      reds = 0;
      greens = 0;
      blues = 0;
    }
    int mul() {
      return reds * greens * blues;
    }
};

void update_game_cubes(Cubes &g_cubes, Cubes &s_cubes) {
  g_cubes.reds = max(g_cubes.reds, s_cubes.reds);
  g_cubes.greens = max(g_cubes.greens, s_cubes.greens);
  g_cubes.blues = max(g_cubes.blues, s_cubes.blues);
}

void update_set_cube(Cubes &s_cubes, string color, int num) {
  // cout << color << num << endl;
  if (color == "red") {
    s_cubes.reds = max(s_cubes.reds, num);
  }
  else if (color == "green") {
    s_cubes.greens = max(s_cubes.greens, num);
  }
  else {
    s_cubes.blues = max(s_cubes.blues, num);
  }
  cout << "Set" << s_cubes.reds << " " << s_cubes.blues << " " << s_cubes.greens << endl; 
}

Cubes handle_set(string g_set) {
  int cur_delim = 0;
  int next_delim;
  string cur_color;
  Cubes s_cubes;

  while ((next_delim = g_set.find(",", cur_delim)) != string::npos) {
    cur_color = g_set.substr(cur_delim, next_delim - cur_delim);
    int split = cur_color.find(" ");
    string color = cur_color.substr(split+1);
    int amt = stoi(cur_color.substr(0, split+1));
    update_set_cube(s_cubes, color, amt);
    cur_delim = next_delim +2;
  }
  // cout << "Set" << s_cubes.reds << " " << s_cubes.blues << " " << s_cubes.greens << endl; 
  cur_color = g_set.substr(cur_delim);
  int split = cur_color.find(" ");
  string color = cur_color.substr(split+1);
  int amt = stoi(cur_color.substr(0, split+1));
  update_set_cube(s_cubes, color, amt);
  // cout << "Set" << s_cubes.reds << " " << s_cubes.blues << " " << s_cubes.greens << endl;
  return s_cubes;
}

Cubes handle_game(string curLine) {
  int game_info_pos = curLine.find(":");
  curLine.erase(0, game_info_pos + 2);
  int cur_delim = 0;
  int next_delim;
  string cur_set;
  Cubes game_cubes;
  Cubes set_cubes;


  while ((next_delim = curLine.find(";", cur_delim)) != string::npos) {
    cur_set = curLine.substr(cur_delim, next_delim - cur_delim);
    cur_delim = next_delim + 2;
    set_cubes = handle_set(cur_set);
    update_game_cubes(game_cubes, set_cubes);
  }
  cur_set = curLine.substr(cur_delim);
  set_cubes = handle_set(cur_set);
  update_game_cubes(game_cubes, set_cubes);
  return game_cubes;
}

int main() {
  std::ifstream my_file;
  my_file.open("data.txt");
  vector <string> lines;
  string curLine;
  int res = 0;

  while(getline(my_file, curLine)) {
    Cubes g_cube = handle_game(curLine);
    int g_res = g_cube.mul();
    cout << g_res << endl;
    res += g_res;
  }

  cout << res;
  return 0;
}