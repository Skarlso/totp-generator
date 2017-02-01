// Copyright [2016] <Gergely Brautigam>
#include <stdio.h>
#include <string.h>
#include <openssl/hmac.h>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "base64.h"

using std::string;

string generateOTPToken(string token, std::time_t t) {
    string timer = std::to_string(int(floor(t/30)));
    string decoded = base64_decode(token);

    char data[1024];
    strcpy(data, token.c_str());

    unsigned char* digest;
    digest = HMAC(EVP_sha1(), timer.c_str(), strlen(timer.c_str()), (unsigned char*)data, strlen(token.c_str()), NULL, NULL);

    char mdString[20];
    for(int i = 0; i < 20; i++)
         sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

    printf("HMAC digest: %s\n", mdString);
    auto offset = mdString[strlen(mdString)-1] & 0xf;
	auto value = (long long)(((int(mdString[offset]) & 0x7f) << 24) |
		((int(mdString[offset+1] & 0xff)) << 16) |
		((int(mdString[offset+2] & 0xff)) << 8) |
		(int(mdString[offset+3]) & 0xff));

    int len = 6;
    int mod = int(int(value) % int(pow(10, len)));
    printf("%d", mod);
    return std::to_string(mod);
}

int main()
{
    std::time_t timer = std::time(nullptr);
    if(const char* env_p = std::getenv("OTP_TOKEN")) {
        string token(env_p);
        generateOTPToken(token, timer);
    } else {
        printf("Please set your environment property 'OTP_TOKEN' to your token key.\n");
    }
    return 0;
}
