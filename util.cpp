#include "util.hpp"

std::vector<std::string> util::explode(std::string const & s, char delim) {
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); ) {
        result.push_back(std::move(token));
    }

    return result;
}

std::string util::bool_to_string(bool input) {
    if (input) return "true";

    return "false";
}