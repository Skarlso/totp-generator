#include "accounting.hpp"
#include "filehandler.hpp"
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <boost/filesystem.hpp>
#include <fstream>
#include <stdio.h>

namespace fs = boost::filesystem;

Accounting::Accounting() {
    fileHandler = new FileHandler::FileHandler();
}

std::string Accounting::retrieveToken(const std::string account) {
    std::map<std::string, std::string> accounts = fileHandler->loadAccountFile();
    auto it = accounts.find(account);
    if (it == accounts.end()) {
        return "";
    }
    return it->second;
}

void Accounting::saveToken(const std::string account, const std::string token) {
    std::map<std::string, std::string> accounts = fileHandler->loadAccountFile();
    auto it = accounts.find(account);
    if (it != accounts.end()) {
        std::cout << "Account " << account << " already exists!" << std::endl;
        return;
    }
    accounts[account] = token;
    fileHandler->saveAccountFile(accounts);
    std::cout << "Added new totp " << token << " to account " << account << std::endl;
}

void Accounting::deleteAccount(const std::string account) {
    std::map<std::string, std::string> accounts = fileHandler->loadAccountFile();
    auto it = accounts.find(account);
    if (it == accounts.end()) {
        std::cout << "Account " << account << " not found!" << std::endl;
        return;
    }
    accounts.erase(it);
    fileHandler->saveAccountFile(accounts);
    std::cout << "Account " << account << " removed." << std::endl;
}
