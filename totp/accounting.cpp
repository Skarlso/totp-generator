#include "accounting.hpp"
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
    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    fs::path home;
    home /= std::string(homedir);
    home /= Accounting::CONFIG_FOLDER;
    struct stat buffer;
    if (stat (home.c_str(), &buffer) != 0) {
        fs::create_directory(home);
    }
    home /= Accounting::CONFIG_FILE;
    if (stat (home.c_str(), &buffer) != 0) {
        std::ofstream outfile (home.c_str());
    }
    configLocation = home;
    loadAccountFile();
}

std::string Accounting::retrieveToken(std::string account) {
    auto it = accounts.find(account);
    if (it == accounts.end()) {
        return "";
    }
    return it->second;
}

void Accounting::saveToken(std::string account, std::string token) {
    auto it = accounts.find(account);
    if (it != accounts.end()) {
        std::cout << "Account " << account << " already exists!" << std::endl;
        return;
    }
    accounts[account] = token;
    saveAccountFile();
    std::cout << "Added new totp " << token << " to account " << account << std::endl;
}

void Accounting::saveAccountFile() {
    std::ofstream accFile (configLocation.c_str());
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        accFile << it->first << ":" << it->second << '\n';
    }
    accFile.close();
}

void Accounting::loadAccountFile() {
    std::ifstream file(configLocation.c_str());
    std::string str;
    while (std::getline(file, str)) {
        char account[1024];
        char token[1024];
        std::sscanf(str.c_str(), "%[^:]:%s", account, token);
        std::string acc(account);
        std::string tok(token);
        accounts[acc] = tok;
    }
}