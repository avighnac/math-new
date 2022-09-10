#pragma once

#include <algorithm>
#include <string>
#include <vector>

std::string add(std::string, std::string);
std::string add_whole(const std::string &, const std::string &);
std::string subtract(std::string, std::string);
std::string subtract_whole(std::string, std::string);
std::string multiply(std::string, std::string);
std::string multiply_whole(std::string, std::string);
std::string divide(std::string, std::string, int);
std::string divide_whole(std::string, std::string, std::string &);
std::string fdivide(std::string, std::string, int &, int &);

std::string inc(std::string);