#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <sstream>
#include <istream>

namespace ft {
    std::vector<std::string> split(const std::string &str, const std::string &delimiter);
    std::vector<std::string> split(const std::string &str, char delimiter);
    std::string to_string(int num);
}

#endif
