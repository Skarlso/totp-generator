#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include <boost/filesystem.hpp>
#include <string>
#include <map>

class FileHandler {
public:
    const std::string CONFIG_FOLDER = ".totp";
    const std::string CONFIG_FILE = "accounts.txt";
    FileHandler();
    std::map<std::string, std::string> loadAccountFile();
    void saveAccountFile(const std::map<std::string, std::string> accountsToSave);
private:
    boost::filesystem::path configLocation;
    std::string password = "";
};

#endif
