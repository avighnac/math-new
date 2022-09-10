#include "libs/CImg/CImg.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  if (argc >= 2) {
    std::vector<long long> data;
    std::fstream file(argv[1]);
    std::string line;
    std::string name;
    while (std::getline(file, line)) {
      if (line.find("name: ") != std::string::npos) {
        name = line.substr(line.find("name: ") + 6, line.length());
      } else if (line.find("end") != std::string::npos) {
        int height =
            (int)std::floor(*std::max_element(data.begin(), data.end()));
        cimg_library::CImg<unsigned char> image(data.size() + 1, height + 1, 1,
                                                3, 0);
        for (auto i = 0; i < data.size(); i++) {
          for (auto j = 0; j <= data[i]; j++) {
            image(i, height - j, 0, 0) = 0;
            image(i, height - j, 0, 1) = 255;
            image(i, height - j, 0, 2) = 0;
          }
        }

        image.save((name + ".bmp").c_str());
        data.clear();
      } else {
        size_t location = line.find(": ");
        if (location == std::string::npos) {
          std::cout << "Error: invalid input.\n";
          return 0;
        }
        data.push_back(std::stoll(line.substr(location + 2, line.length())));
      }
    }
    file.close();
  }
}