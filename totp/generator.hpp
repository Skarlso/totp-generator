#ifndef TOKEN_GENERATOR_H
#define TOKEN_GENERATOR_H
#include <string>
#include <ctime>

using std::string;

class TokenGenerator {
public:
    TokenGenerator(){};
    string generateOTPToken(string token, std::time_t t);
private:
    string decodeBase32(string token);
};

#endif // TOKEN_GENERATOR_H
