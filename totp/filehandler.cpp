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

#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace fs = boost::filesystem;

/**
 * https://stackoverflow.com/a/1455007/362417
 */
void SetStdinEcho(bool enable = true)
{
#ifdef WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if (!enable)
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode(hStdin, mode);

#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable)
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}

FileHandler::FileHandler()
{
    SetStdinEcho(false);
    std::cerr << "password: ";
    std::cin >> password;
    SetStdinEcho(true);
    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL)
    {
        homedir = getpwuid(getuid())->pw_dir;
    }
    fs::path home;
    home /= std::string(homedir);
    home /= CONFIG_FOLDER;
    struct stat buffer;
    if (stat(home.c_str(), &buffer) != 0)
    {
        fs::create_directory(home);
    }
    home /= CONFIG_FILE;
    if (stat(home.c_str(), &buffer) != 0)
    {
        std::string content = "";
        Encrypt::Encrypt *encrypt = new Encrypt::Encrypt();
        std::string encryptedContent = encrypt->encrypt(content, password);
        std::ofstream outfile(home.c_str());
        outfile << encryptedContent;
        outfile.close();
    }
    configLocation = home;
}

void FileHandler::saveAccountFile(const std::map<std::string, std::string> accountsToSave)
{
    std::ostringstream content;
    for (auto it = accountsToSave.begin(); it != accountsToSave.end(); ++it)
    {
        content << it->first << ":" << it->second << '\n';
    }

    Encrypt::Encrypt *encrypt = new Encrypt::Encrypt();
    std::string encryptedContent = encrypt->encrypt(content.str(), password);

    std::ofstream accFile(configLocation.c_str());
    accFile << encryptedContent;
    accFile.close();
}

std::map<std::string, std::string> FileHandler::loadAccountFile()
{
    std::map<std::string, std::string> accounts;
    std::ifstream file(configLocation.c_str());
    std::stringstream buffer;
    buffer << file.rdbuf();

    Encrypt::Encrypt *encrypt = new Encrypt::Encrypt();
    std::string decrypted = encrypt->decrypt(buffer.str(), password);
    std::istringstream stream;
    stream.str(decrypted);
    std::string str;
    while (std::getline(stream, str))
    {
        char account[1024];
        char token[1024];
        std::sscanf(str.c_str(), "%[^:]:%s", account, token);
        std::string acc(account);
        std::string tok(token);
        accounts[acc] = tok;
    }
    return accounts;
}
