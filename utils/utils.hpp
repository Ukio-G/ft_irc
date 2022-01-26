#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <sstream>
#include <istream>
#include <map>

namespace ft {
    std::vector<std::string> split(const std::string &str, const std::string &delimiter);
    std::vector<std::string> split(const std::string &str, char delimiter);
    std::string to_string(int num);


    template<class K, class V>
    typename std::map<K, V>::iterator findValueInMap(const std::map<K, V> & map, const V & value) {
        typedef typename std::map<K, V>::iterator ItType;
        ItType it = map.begin();
        for (;it != map.end(); it++)
            if (it->second == value) break;
        return it;
    }
}

#endif
