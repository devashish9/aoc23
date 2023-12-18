#ifndef UTILS_H
#define UTILS_H
#include<vector>
#include<string.h>

std::vector<std::string> readlines(std::string loc);
std::vector<char> get_chars(std::string line);
std::vector<int> get_nums(std::string line);
std::vector<long> get_longs(std::string line);
std::vector<std::string> get_strings(std::string line);


#endif // UTILS_H