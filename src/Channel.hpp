//
// Created by ukio on 1/24/22.
//

#ifndef CHANNEL_HPP
#define CHANNEL_HPP


class Channel {
public:
    Channel();

    Channel(const Channel &other);

    Channel &operator=(const Channel &other);

    ~Channel();

private:
    std::string name;

};


#endif
