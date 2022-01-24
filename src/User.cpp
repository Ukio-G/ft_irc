#include <arpa/inet.h>
#include "User.hpp"

User::User() {}

User::User(const User &other) : sock_fd(other.sock_fd), nick(other.nick), userName(other.userName), realName(other.realName), mode(other.mode), authorized(false) {

}

User::User(int fd, sockaddr *addr) : sock_fd(fd) , authorized(false) {
    host = inet_ntoa(((sockaddr_in*)addr)->sin_addr);
}

User::User(int fd) : sock_fd(fd), authorized(false) {
    sockaddr_in ip4addr;
    socklen_t len = sizeof(ip4addr);
    getsockname(fd, (sockaddr*)&ip4addr, &len);
    host = inet_ntoa(ip4addr.sin_addr);
}

User &User::operator=(const User &other) {
    if (&other == this)
        return *this;
    sock_fd = other.sock_fd;
    nick = other.nick;
    realName = other.realName;
    userName = other.userName;
    mode = other.mode;
    authorized = other.authorized;
    return *this;
}

User::~User() {

}

int User::getSockFd() const {
    return sock_fd;
}

void User::setSockFd(int sockFd) {
    sock_fd = sockFd;
}

const std::string &User::getNick() const {
    return nick;
}

void User::setNick(const std::string &nick) {
    User::nick = nick;
}

const std::string &User::getUserName() const {
    return userName;
}

void User::setUserName(const std::string &userName) {
    User::userName = userName;
}

const std::string &User::getRealName() const {
    return realName;
}

void User::setRealName(const std::string &realName) {
    User::realName = realName;
}

const std::string &User::getHost() const {
    return host;
}

void User::setHost(const std::string &host) {
    User::host = host;
}

int User::getMode() const {
    return mode;
}

void User::setMode(int mode) {
    User::mode = mode;
}

bool User::isAuthorized() const {
    return authorized;
}

void User::setAuthorized(bool authorized) {
    User::authorized = authorized;
}

