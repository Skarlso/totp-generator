#ifndef ACCOUNTING_H
#define ACCOUNTING_H
#include <boost/filesystem.hpp>
#include <string>
#include <map>

class Accounting {
public:
    const std::string CONFIG_FOLDER = ".totp";
    const std::string CONFIG_FILE = "accounts.txt";
    Accounting();
    std::string retrieveToken(std::string account);
    void saveToken(std::string account, std::string token);
    void deleteToken(std::string account);
private:
    std::map<std::string, std::string> accounts;
    boost::filesystem::path configLocation;
    void saveAccountFile();
    void loadAccountFile();
};

#endif // TOKEN_GENERATOR_H