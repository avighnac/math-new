#ifndef _shift_decimal_point_
#define _shift_decimal_point_

#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>

    bool decimal_point_exists(const std::string &str) {
        for (auto &i : str) {
            if (i == '.') {
                return true;
            }
        }
        return false;

    }

size_t decimal_point_location(const std::string &str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == '.') {
            return i;
        }
    }
    throw std::runtime_error("No decimal point.");
    return 0;
}

void remove_leading_decimals(std::string &str) {
    if (decimal_point_exists(str)) {
        std::reverse(str.begin(), str.end());
        str.erase(0, std::min( str.find_first_not_of('0'),  str.size()-1));
        std::reverse(str.begin(), str.end());

        if (str[str.length()-1] == '.') str = str.substr(0, str.length()-1);
    }
}

std::string shift_decimal_point(std::string str, int places) {
    if (!decimal_point_exists(str)) str += ".0";
    for (int i = 0; i < places; i++) {str += "0";}
    for (int i = 0; i < -places; i++) {str = "0" + str;}

    size_t dec_loc = decimal_point_location(str);
    str.erase(dec_loc, 1);
    dec_loc += places;

    str = str.substr(0, dec_loc) + "." + str.substr(dec_loc, str.length());
    remove_leading_decimals(str);
    str.erase(0, std::min(str.find_first_not_of('0'),  str.size()-1));
    if (str[0] == '.') {str = "0" + str;}

    return str;
}

#endif