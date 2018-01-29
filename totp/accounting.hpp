#ifndef ACCOUNTING_H
#define ACCOUNTING_H
#include <boost/filesystem.hpp>
#include "filehandler.hpp"
#include <string>
#include <map>

class Accounting {
public:
    Accounting();
    std::string retrieveToken(const std::string account);
    void saveToken(const std::string account, const std::string token);
    void deleteAccount(const std::string account);
private:
    FileHandler *fileHandler;
    std::map<std::string, std::string> accounts;
    boost::filesystem::path configLocation;
    void saveAccountFile();
    void loadAccountFile();
};

#endif // TOKEN_GENERATOR_H
