#include "utils.hpp"

namespace ft {
    std::vector<std::string> split(const std::string &str, const std::string &delimiter) {
        size_t pos = 0;
        std::string str_copy = str;
        std::vector<std::string> result;
        while ((pos = str_copy.find(delimiter)) != std::string::npos) {
            result.push_back(str_copy.substr(0, pos));
            str_copy.erase(0, pos + delimiter.length());
        }
        return result;
    }

    std::vector<std::string> split(const std::string &str, char delimiter) {
        std::vector<std::string> result;
        std::istringstream f(str);
        std::string s;
        while (getline(f, s, delimiter))
            result.push_back(s);
        return result;
    }
}