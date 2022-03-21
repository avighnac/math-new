#include <string>
#include <vector>

#include "algebric_number_class.hpp"
#include "../integer_square_root.hpp"

std::pair<std::string, std::string> split_middle_term_ax2bxc(std::vector<algebric_num::algebric_number> terms, int accuracy = 8) {
  if (terms.size() > 3)
    throw std::
        runtime_error("[math++.factorize.ax^2+bx+c] Error: Algebraic "
                        "expression provided "
           "cannot be factorized using this factorization type.");

  std::vector<algebric_num::algebric_number> middleTerm;
  auto x = integer_square_root(add(multiply(terms[1].constantPart, terms[1].constantPart),multiply("-4",multiply(terms[0].constantPart, terms[2].constantPart))), accuracy);
  middleTerm.emplace_back(multiply(add(terms[1].constantPart, x), "0.5"));
  middleTerm.emplace_back(multiply(subtract(terms[1].constantPart, x), "0.5"));

  return {middleTerm[0].constantPart,
          middleTerm[1].constantPart};
}