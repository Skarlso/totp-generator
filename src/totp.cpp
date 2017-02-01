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
    printf("decoded: %s\n", decoded.c_str());
    printf("timer: %s\n", timer.c_str());
    char data[1024];
    strcpy(data, timer.c_str());

    unsigned char* digest;
    //digest = HMAC(EVP_sha1(), timer.c_str(), strlen(timer.c_str()), (unsigned char*)data, strlen(token.c_str()), NULL, NULL);
    digest = HMAC(EVP_sha1(), decoded.c_str(), strlen(decoded.c_str()), (unsigned char*)data, strlen(timer.c_str()), NULL, NULL);
    //char mdString[20];
    //for(int i = 0; i < 20; i++)
    //     sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    //for (int i = 0; i < 20; i++)
    //    printf("%d,", (int)digest[i]);
    int offset = digest[strlen((char*)digest)-1] & 0xf;
    printf("offset: %d\n", offset);
	int value = (int)(((int(digest[offset]) & 0x7f) << 24) |
		((int(digest[offset+1] & 0xff)) << 16) |
		((int(digest[offset+2] & 0xff)) << 8) |
		(int(digest[offset+3]) & 0xff));
    printf("value: %d\n", value);
    int len = 6;
    int mod = int(value % int(pow(10, len)));
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
