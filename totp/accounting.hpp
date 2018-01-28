#ifndef ACCOUNTING_H
#define ACCOUNTING_H
#include <string>

class Accounting {
public:
    const std::string CONFIG_FOLDER = ".totp";
    const std::string CONFIG_FILE = "accounts.txt";
    Accounting();
    std::string retrieveToken(std::string account);
    void saveToken(std::string account);
    void deleteToken(std::string account);
};

#endif // TOKEN_GENERATOR_H