// Copyright [2016] <Gergely Brautigam>
#include <stdio.h>
#include <string.h>
#include <openssl/hmac.h>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <cryptopp/base64.h>
#include <algorithm>

using std::string;

string generateOTPToken(string token, std::time_t t) {
    uint64_t timer = (uint64_t)(floor(t/30));
    printf("timer: %llu\n", timer);
    string secretBytes;
    CryptoPP::Base64Decoder decoder;

    decoder.Put((byte*)token.data(), token.length());
    decoder.MessageEnd();

    CryptoPP::word64 size = decoder.MaxRetrievable();
    if(size && size <= SIZE_MAX)
    {
        secretBytes.resize(size);
        decoder.Get((byte*)secretBytes.data(), secretBytes.length());
    }
    secretBytes.erase(std::remove(secretBytes.begin(), secretBytes.end(), '\n'), secretBytes.end());
    unsigned char key[1024];
    printf("OTP: %s\n", secretBytes.c_str());
    for(int i = 0; i < secretBytes.length(); i++)
        key[i] = (unsigned char)secretBytes[i];

    printf("key:");
    int keylength = 0;
    for(int i = 0; key[i] != '\0'; i++) {
        printf("%c", key[i]);
        keylength++;
    }

    printf("\n");

    unsigned char data[8];
    data[0] = (unsigned char)(timer >> 56);
    data[1] = (unsigned char)(timer >> 48);
    data[2] = (unsigned char)(timer >> 40);
    data[3] = (unsigned char)(timer >> 32);
    data[4] = (unsigned char)(timer >> 24);
    data[5] = (unsigned char)(timer >> 16);
    data[6] = (unsigned char)(timer >> 8);
    data[7] = (unsigned char)(timer);
    unsigned char* digest = nullptr;

    digest = HMAC(EVP_sha1(), key, keylength, (unsigned char*)data, sizeof(data), nullptr, nullptr);
    char mdString[41];
    for(int i = 0; i < 20; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned char)digest[i]);
    printf("mdString: %s\n", mdString);

    int offset = digest[strlen((char*)digest)-1] & 0xf;
	int value = (int)(((int(digest[offset]) & 0x7f) << 24) |
		((int(digest[offset+1] & 0xff)) << 16) |
		((int(digest[offset+2] & 0xff)) << 8) |
		(int(digest[offset+3]) & 0xff));
    int len = 6;
    int mod = value % int(pow(10, len));
    printf("%d\n", mod);
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
