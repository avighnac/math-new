#include <string>
#include <vector>

#include "algebric_number_class.hpp"

std::string a2b2(std::string sum) {
  auto terms = algebric_num::get_terms(sum);
  if (terms.size() != 2)
    return "Cannot factorize further.";
}