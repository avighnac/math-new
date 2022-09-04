#pragma once

#include <algorithm>
#include <string>
#include <vector>

std::string add(std::string, std::string);
std::string add_whole(std::string, std::string);
std::string subtract(std::string, std::string);
std::string subtract_whole(std::string, std::string);
std::string multiply(std::string, std::string);
std::string multiply_whole(std::string, std::string);
std::string divide(std::string, std::string, int);
std::string divide_whole(std::string, std::string, std::string &);
std::string fdivide(std::string, std::string, int &, int &);

std::vector<int> digitize(std::string);
std::vector<int> split_into_digits(std::string);
std::vector<int> reverse_vec(std::vector<int>);

bool decimal_point_exists(const std::string &);
size_t decimal_point_location(const std::string &);
void remove_leading_decimals(std::string &);
std::string shift_decimal_point(std::string, int);

std::string inc(std::string);