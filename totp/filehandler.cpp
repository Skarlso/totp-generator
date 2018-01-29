#include "encrypt.hpp"
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
#include <sstream>

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
        // Initate a file and set a password
        std::cout << "Setting up first time password." << std::endl;
        std::cout << "password:";
        std::cin >> password;
        std::string content = "";
        Encrypt::Encrypt *encrypt = new Encrypt::Encrypt();
        std::string encryptedContent = encrypt->encrypt(content, password);
        std::ofstream outfile (home.c_str());
        outfile << encryptedContent;
        outfile.close();
    }
    configLocation = home;
}

void FileHandler::saveAccountFile(std::map<std::string, std::string> accountsToSave) {
    if (password.empty()) {
        std::cout << "password:";
        std::cin >> password;
    }
    std::ostringstream content;
    for (auto it = accountsToSave.begin(); it != accountsToSave.end(); ++it) {
        content << it->first << ":" << it->second << '\n';
    }

    Encrypt::Encrypt *encrypt = new Encrypt::Encrypt();
    std::string encryptedContent = encrypt->encrypt(content.str(), password);

    std::ofstream accFile (configLocation.c_str());
    accFile << encryptedContent;
    accFile.close();
}

std::map<std::string, std::string> FileHandler::loadAccountFile() {
    if (password.empty()) {
        std::cout << "password:";
        std::cin >> password;
    }
    std::map<std::string, std::string> accounts;
    std::ifstream file(configLocation.c_str());
    std::stringstream buffer;
    buffer << file.rdbuf();

    Encrypt::Encrypt *encrypt = new Encrypt::Encrypt();
    std::string decrypted = encrypt->decrypt(buffer.str(), password);
    std::istringstream stream;
    stream.str(decrypted);
    std::string str;
    while (std::getline(stream, str)) {
        char account[1024];
        char token[1024];
        std::sscanf(str.c_str(), "%[^:]:%s", account, token);
        std::string acc(account);
        std::string tok(token);
        accounts[acc] = tok;
    }
    return accounts;
}
