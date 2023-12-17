#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
using namespace std;

map<string, map<string, int>> mappers;
vector<string> map_names = {"seeds", "seed_to_soil", "soil_to_fert", "fert_to_water", "water_to_light", "light_to_temp", "temp_to_hum", "hum_to_loc"};

void create_maps(vector<string> lines) {
  int mapping = 0;
  vector<string> buffer;

  for (auto& line: lines) {
    if (line == "") {
      create_map(mapping, buffer);
      mapping += 1;
      buffer.clear();
    }
    else {
      buffer.push_back(line);
    }
  }
}

void create_map(int m_num, vector<string> buf) {
  if(m_num == 0) {
    seed_map(buf);
  }
  else {
    mapper_map(map_names[m_num], buf);
  }
}

void seed_map(vector<string> buf) {

}

void mapper_map(string mapping, vector<string> buf) {

}

int main() {
  std::ifstream my_file;
  my_file.open("test.txt");
  vector <string> lines;
  string curLine;
  int res = 0;

  while(getline(my_file, curLine)) {
    lines.push_back(curLine);
    cout << curLine << endl;
  }

  create_maps(lines);

  cout << res << endl;
  return res;
}