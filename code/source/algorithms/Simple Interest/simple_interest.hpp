#include <iostream>
#include <vector>
#include "remove_subsequent_spaces.hpp"

class simpleInterest {
    public:
        std::string to_lower(std::string str) {for (auto &i : str) i = std::tolower(i); return str;}

        std::string remove_spaces(std::string &str) {std::string answer; for (auto &i : str) if (i != ' ') answer.push_back(i); return answer;}

        int next_semicolon_location(const std::string &str) {
            int location = 0;
            for (int i = 0; i < str.length(); i++) {
                if (str[i] == ';') {location = i; break;}
            }
            if (location == 0 && str[0] != ';') throw std::runtime_error("No semi-colon was found in string \"" + str + "\".");
            return location;
        }

        std::string getFormula(std::string formula_id) {
            for (auto &i : formula_id) i = std::tolower(i);

            if (formula_id == "s.i.") return "S.I. = (P * R * T) / 100";
            if (formula_id == "p") return "P = (100 * S.I.) / (R * T)";
            if (formula_id == "r") return "R = (100 * S.I.) / (P * T)";
            if (formula_id == "t") return "R = (100 * S.I.) / (P * R)";

            throw std::runtime_error("Invalid formula_id for function simpleInterest.getFormula().");
        }

        class find {
            public:
                double SI(double P, double R, double T) {
                    return (P * R * T) / 100;
                }

                double P(double SI, double R, double T) {
                    return (100 * SI) / (R * T);
                }

                double R(double SI, double P, double T) {
                    return (100 * SI) / (P * T);
                }

                double T(double SI, double P, double R) {
                    return (100 * SI) / (P * R);
                }
        };

        find find;
        void solve() {
            std::cout << "Enter the values of any 3 of these options to get started. SI, P, R, T. \n";
            std::cout << "Type \"help\" to get more information. \n \n";

            std::string values;
            std::getline(std::cin, values);
            values = to_lower(values);

            bool isHelp = true;
            while (isHelp) {
                if (remove_subsequent_spaces(values) == " help" || remove_subsequent_spaces(values) == "help " || remove_subsequent_spaces(values) == "help" || remove_subsequent_spaces(values) == " help ") {
                    std::cout << "S.I. = Simple Interest \nP = Principal Amount or Base Amount \nR = Rate per annum (in percentage) \nT = Time (in years) \n \n";
                    std::getline(std::cin, values);
                    isHelp = true;
                } else {
                    isHelp = false;
                    values = remove_spaces(values);
                    values = to_lower(values);
                    if (values[values.length()-1] != ';') values.push_back(';');

                    double P, R, T, SI;
                    std::vector<bool> valuesFound = {false, false, false, false}; //SI, P, R, T

                    for (int i = 0; i < values.length(); i++) {
                        if (i+2 < values.length()) {
                            class valueFinderHelp {
                                public:
                                    double valueFinder(int i, std::string values) {
                                        simpleInterest simpleInterest;
                                        std::string X_STR;
                                        for (int j = i+2; j < simpleInterest.next_semicolon_location(values.substr(i+2, values.length()))+i+2; j++) X_STR.push_back(values[j]);
                                        return std::stod(X_STR);
                                    }
                            };

                            valueFinderHelp VF;
                            if (values[i] == 'p' && values[i+1] == '=') {P = VF.valueFinder(i, values); valuesFound[1] = true;}
                            if (values[i] == 'r' && values[i+1] == '=') {R = VF.valueFinder(i, values); valuesFound[2] = true;}
                            if (values[i] == 't' && values[i+1] == '=') {T = VF.valueFinder(i, values); valuesFound[3] = true;}
                            
                            if (i+3 < values.length() && !valuesFound[0]) {
                                if (values[i] == 's' && values[i+1] == 'i' && values[i+2] == '=') {
                                    valuesFound[0] = true;
                                    SI = VF.valueFinder(i+1, values);
                                }
                            }
                        }
                    }

                    int valueCount = 0;
                    for (auto i : valuesFound) if (i) valueCount++;
                    if (valueCount == 4) std::cout << "You already have your answer ^-^ \n";
                    else if (valueCount == 3) {
                        if (!valuesFound[0] /*S.I.*/) {
                            std::cout << getFormula("S.I.") << "\n";
                            std::cout << "Simple Interest (S.I.) = (" << P << " * " << R << " * " << T << ") / 100 \n";
                            double PRT = P*R*T;
                            std::cout << "Simple Interest (S.I.) = " << PRT << " / 100 \n";
                            std::cout << "Simple Interest (S.I.) = " << PRT/100 << " (unit) \n";
                        }
                        if (!valuesFound[1] /*P*/) {
                            std::cout << getFormula("P") << "\n";
                            std::cout << "Principal Amount (P) = (100 * " << SI << ") / (" << R << " * " << T << ") \n";
                            double SI100 = 100 * SI;
                            double RT = R * T;
                            std::cout << "Principal Amount (P) = " << SI100 << " / " << RT << "\n";
                            std::cout << "Principal Amount (P) = " << SI100/RT << " (unit) \n";
                        }
                        if (!valuesFound[2] /*R*/) {
                            std::cout << getFormula("R") << "\n";
                            std::cout << "Rate % (R) = (100 * " << SI << ") / (" << P << " * " << T << ") \n";
                            double SI100 = 100 * SI;
                            double PT = P * T;
                            std::cout << "Rate % (R) = " << SI100 << " / " << PT << "\n";
                            std::cout << "Rate % (R) = " << SI100/PT << "% \n";
                        }
                        if (!valuesFound[3] /*T*/) {
                            std::cout << getFormula("T") << "\n";
                            std::cout << "Time in Years (T) = (100 * " << SI << ") / (" << P << " * " << R << ") \n";
                            double SI100 = 100 * SI;
                            double PR = P * R;
                            std::cout << "Time in Years (T) = " << SI100 << " / " << PR << "\n";
                            double T = SI100/PR;
                            T == 1 ? std::cout << "Time in Years (T) = 1 year \n" : std::cout << "Time in Years (T) = " << SI100/PR << " years \n";
                        }
                    }
                    else std::cout << "Too few values provided. (" << valueCount << ") \n";
                }
            }
        }
};