#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <boost/filesystem.hpp>
#include <string>
#include <map>

class Encrypt {
public:
    Encrypt(){};
    std::string encrypt(std::string content, std::string password);
    std::string decrypt(std::string content, std::string password);
};

#endif
