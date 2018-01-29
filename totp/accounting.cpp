#include "accounting.hpp"
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

Accounting::Accounting() {
    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    fs::path home;
    home /= std::string(homedir);
    home /= Accounting::CONFIG_FOLDER;
    home /= Accounting::CONFIG_FILE;
    struct stat buffer;
    if (stat (home.c_str(), &buffer) != 0) {
        std::cout << "Creating config folder." << std::endl;
    } else {
        std::cout << "Config folder present." << std::endl;
    }
}

std::string Accounting::retrieveToken(std::string account) {

    return "";
}