#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <cstring>
#include <algorithm>
using namespace std;

map<string, vector<map<string, long>>> mappers;
vector<string> map_names = {"seed_to_soil", "soil_to_fert", "fert_to_water", "water_to_light", "light_to_temp", "temp_to_hum", "hum_to_loc"};
vector<long> seeds = {};

vector<long> get_nums(string line) {
  string delim = " ";
  const char *c_delim = delim.c_str(); 
  char *c_line = new char[line.length() + 1];
  strcpy(c_line, line.c_str());
  vector<long> lons;

  char* token;
  while ((token = strsep(&c_line, c_delim)) != nullptr) {
    try {
    lons.push_back(stol(string(token)));
    }
    catch (invalid_argument e) {
      //ignore
    }
  }
  return lons;
}

void seed_map(vector<string> buf) {
  for (auto &line: buf) {
    vector<long> lons = get_nums(line);
    seeds.insert(seeds.end(), lons.begin(), lons.end());
    // copy(seeds.begin(), seeds.end(), std::ostream_iterator<long>(std::cout, " "));
  }
}

void mapper_map(string mapping, vector<string> buf) {
  for (auto &line: buf) {
    vector<long> m_range = get_nums(line);
    map<string, long> m_r_map = {
      {"m_to", m_range[0]}, 
      {"m_from", m_range[1]}, 
      {"range", m_range[2]}
    };

    mappers[mapping].push_back(m_r_map);
  }
}

void create_map(long m_num, vector<string> buf) {
  if(m_num == 0) {
    seed_map(buf);
  }
  else {
    mapper_map(map_names[m_num - 1], vector<string>(buf.begin() +1, buf.end()));
  }
}

void create_maps(vector<string> lines) {
  long mapping = 0;
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
  create_map(mapping, buffer);
}

int main() {
  std::ifstream my_file;
  my_file.open("data.txt");
  vector <string> lines;
  string curLine;
  long res = 0;

  while(getline(my_file, curLine)) {
    lines.push_back(curLine);
  }

  create_maps(lines);
  return 0;
}