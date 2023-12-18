#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <cstring>
#include <algorithm>
#include <queue>
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

bool overlap(long s1, long e1, long s2, long e2) {
  // cout << "Overlap " << s1 << " " << e1 << " " << s2 << " " << e2 << endl;
  return s1 > e2 || s2 > e1;
}

typedef pair<vector<pair<long, long>>, vector<pair<long, long>>> updated_range; 

updated_range map_range(long m_from, long m_to, long m_range, long r_start, long r_end) {
  // cout << "Mapping: " << m_from << " " << m_to << " " << m_range << " " << r_start << " " << r_end << endl;
  vector<pair<long, long>> mapped;
  vector<pair<long, long>> unmapped; 

  if (r_start >= m_from) {
    if (r_end < m_from + m_range) {
      // cout << "Case 1" << endl;
      mapped.push_back(pair(r_start - m_from + m_to, r_end - m_from + m_to));
    }
    else {
      // cout << "Case 2" << endl;
      mapped.push_back(pair(r_start - m_from + m_to, m_to + m_range - 1));
      unmapped.push_back(pair(m_from + m_range, r_end));
    }
  }
  else {
    if (r_end < m_from + m_range) {
      // cout << "Case 3" << endl;
      // cout << m_from + m_range << endl;
      unmapped.push_back(pair(r_start, m_from - 1));
      mapped.push_back(pair(m_to, r_end - m_from + m_to));
    }
    else {
      // cout << "Case 4" << endl;
      unmapped.push_back(pair(r_start, m_from - 1));
      mapped.push_back(pair(m_to, m_to + m_range - 1));
      unmapped.push_back(pair(m_from + m_range, r_end));
    }
  }
  return pair(mapped, unmapped);
}

queue<pair<long, long>> transform_range(string mapping, pair<long, long> range_pair) {
  queue<pair<long, long>> q;
  queue<pair<long, long>> q_res;
  q.push(range_pair);

  while (!q.empty()) {
    auto cur_pair = q.front();
    bool mapped = false;
    q.pop();
    for (auto &m: mappers[mapping]) {
      if (!overlap(m["m_from"], m["m_from"] + m["range"] - 1, cur_pair.first, cur_pair.second)) {
        auto result_pair = map_range(m["m_from"], m["m_to"], m["range"], cur_pair.first, cur_pair.second);
        for (auto&ps:result_pair.first) {
          q_res.push(ps);
        }
        for (auto&ps:result_pair.second) {
          q.push(ps);
        }
        mapped = true;
        break;
      }
    }
    if (!mapped) {
      q_res.push(cur_pair);
    }
  }

  return q_res;
}

vector<pair<long, long>> transform_ranges(string mapping, vector<pair<long, long>> ranges) {
  vector<pair<long, long>> res;
  for (auto &r_p: ranges) {
    queue<pair<long, long>>  transformed_pair = transform_range(mapping, r_p);
    while (!transformed_pair.empty()) {
      res.push_back(transformed_pair.front());
      transformed_pair.pop();
    }
  }
  return res;
}

vector<pair<long, long>> push_seeds_through_maps(vector<pair<long, long>> ranges) {
  vector<pair<long, long>> res = ranges;
  for (auto &mapping: map_names) {
    res = transform_ranges(mapping, res);
    cout << "Mapping " << mapping << endl;
    for (auto& res_p: res) {
      cout << res_p.first << " " << res_p.second << endl;
    }
  }
  return res;
}

vector<pair<long, long>> create_seed_ranges() {
  vector<pair<long, long>> seed_ranges;
  for (int i = 0; i < seeds.size(); i += 2) {
    seed_ranges.push_back(pair(seeds[i], seeds[i] + seeds[i+1]));
  }
  return seed_ranges;
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

  auto ranges = create_seed_ranges();
  auto locs = push_seeds_through_maps(ranges);

  long m = locs[0].first; 

  for (auto &r : locs) {
    if (r.first < m) {
      m = r.first;
    }
  }

  cout << m << endl;
  return 0;
}