#include <iostream>

class remove_subsequent_spaces_class {
    public:
    static void remove_part_of_string(std::string &str, int start, int end) {
    std::string answer = "";

    for (int i = 0; i < str.length(); i++)
        if (!(start <= i && i <= end)) answer.push_back(str[i]);

    str = answer;
    }
};

std::string remove_subsequent_spaces(std::string str) {
    remove_subsequent_spaces_class RSS;
    bool made_changes = false;

    for (int i = 0; i < str.length(); i++) {

        if (i + 1 < str.length()) { //Deleting forwards
            if (str[i] == ' ' && str[i + 1] == ' ') {
                std::string temp = str;
                RSS.remove_part_of_string(str, i, i);
                made_changes = true;
            }
        }

        if (i - 1 > -1) { //Deleting backwards
            if (str[i] == ' ' && str[i - 1] == ' ') {
                std::string temp = str;
                RSS.remove_part_of_string(str, i, i);
                made_changes = true;
            }
        }

    }

    if (made_changes) str = remove_subsequent_spaces(str); 
    return str;
}