//
// Created by ukio on 1/24/22.
//

#include "Channel.hpp"

Channel::Channel() {}

Channel::Channel(const Channel &other) {}

Channel &Channel::operator=(const Channel &other) {
    if (&other == this)
        return *this;

    return *this;
}

Channel::~Channel() {

}