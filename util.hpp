#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>
#include <sstream>
#include <utility>

namespace util {
    std::vector<std::string> explode(std::string const & s, char delim);
    std::string bool_to_string(bool input);
}

#endif