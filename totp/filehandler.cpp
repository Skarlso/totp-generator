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

FileHandler::FileHandler() {
    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    fs::path home;
    home /= std::string(homedir);
    home /= CONFIG_FOLDER;
    struct stat buffer;
    if (stat (home.c_str(), &buffer) != 0) {
        fs::create_directory(home);
    }
    home /= CONFIG_FILE;
    if (stat (home.c_str(), &buffer) != 0) {
        std::ofstream outfile (home.c_str());
    }
    configLocation = home;
}


void FileHandler::saveAccountFile(std::map<std::string, std::string> accountsToSave) {
    std::ofstream accFile (configLocation.c_str());
    for (auto it = accountsToSave.begin(); it != accountsToSave.end(); ++it) {
        accFile << it->first << ":" << it->second << '\n';
    }
    accFile.close();
}

std::map<std::string, std::string> FileHandler::loadAccountFile() {
    std::map<std::string, std::string> accounts;
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
    return accounts;
}