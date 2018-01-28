// Copyright [2016] <Gergely Brautigam>
#include "generator.hpp"
#include <ctime>
#include <cstdlib>
#include <string>

using std::string;

int main()
{
    // Use the command library from Yitsushi?
    // command -> create
    // command -> generate
    // command -> delete
    TokenGenerator tg;
    std::time_t timer = std::time(nullptr);
    if(const char* env_p = std::getenv("OTP_TOKEN")) {
        string token(env_p);
        tg.generateOTPToken(token, timer);
    } else {
        printf("Please set your environment property 'OTP_TOKEN' to your token key.\n");
    }
    return 0;
}
