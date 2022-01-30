#ifndef USER_HPP
#define USER_HPP


#include <string>
#include <shared_ptr.hpp>
#include <netinet/in.h>
#include <vector>

class User {
public:
    typedef ft::shared_ptr<User> Ptr;
    typedef std::vector<Ptr>::iterator Iterator;

    User();

    explicit User(int fd);

    User(const User &other);

    User &operator=(const User &other);


    int getSockFd() const;
    void setSockFd(int sockFd);

    const std::string &getNick() const;
    void setNick(const std::string &nick);

    const std::string &getUserName() const;
    void setUserName(const std::string &userName);

    const std::string &getRealName() const;
    void setRealName(const std::string &realName);

    const std::string &getHost() const;
    void setHost(const std::string &host);

    int getMode() const;
    void setMode(int mode);

    bool isAuthorized() const;
    void setAuthorized(bool authorized);

    std::string generateFullUsername() const;
    std::string generateFullUsername();

    bool isOperator() const;
    void setIsOperator(bool isOperator);

    ~User();

private:
    operator int();
    int sock_fd;
    std::string nick;
    std::string userName;
    std::string realName;
    std::string host;
    int mode;
    bool authorized;
    bool is_operator;
};


#endif
