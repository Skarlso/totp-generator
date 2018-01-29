#ifndef ACCOUNTING_H
#define ACCOUNTING_H
#include <boost/filesystem.hpp>
#include "filehandler.hpp"
#include <string>
#include <map>

class Accounting {
public:
    Accounting();
    std::string retrieveToken(std::string account);
    void saveToken(std::string account, std::string token);
    void deleteAccount(std::string account);
private:
    FileHandler *fileHandler;
    std::map<std::string, std::string> accounts;
    boost::filesystem::path configLocation;
    void saveAccountFile();
    void loadAccountFile();
};

#endif // TOKEN_GENERATOR_H
