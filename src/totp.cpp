// Copyright [2016] <Gergely Brautigam>
#include <stdio.h>
#include <string.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <cryptopp/base64.h>

using std::string;

// void switchBigEndian(char *b, int64_t v) {
//     auto _ = b[7]; // early bounds check to guarantee safety of writes below
// 	b[0] = (unsigned char)(v >> 56);
// 	b[1] = (unsigned char)(v >> 48);
// 	b[2] = (unsigned char)(v >> 40);
// 	b[3] = (unsigned char)(v >> 32);
// 	b[4] = (unsigned char)(v >> 24);
// 	b[5] = (unsigned char)(v >> 16);
// 	b[6] = (unsigned char)(v >> 8);
// 	b[7] = (unsigned char)(v);
//     // return b;
//     // printf("data in function:");
//     // for (int i = 0; i < 8; ++i)
//     // {
//     //     printf("%d,", (unsigned char)b[i]);
//     // }
//     // printf("\n");
// }
//
string generateOTPToken(string token, std::time_t t) {
    uint64_t timer = ((uint64_t)(floor(t/30)));
    string secretBytes;
    CryptoPP::Base64Decoder decoder;

    decoder.Put( (byte*)token.data(), token.length() );
    decoder.MessageEnd();

    CryptoPP::word64 size = decoder.MaxRetrievable();
    if(size && size <= SIZE_MAX)
    {
        secretBytes.resize(size);
        decoder.Get((byte*)secretBytes.data(), secretBytes.length());
    }
    // string decoded = base64_decode(token);
    // printf("decoded: %s\n", decoded.c_str());
    unsigned char data[8];
    data[0] = (unsigned char)(timer >> 56);
    data[1] = (unsigned char)(timer >> 48);
    data[2] = (unsigned char)(timer >> 40);
    data[3] = (unsigned char)(timer >> 32);
    data[4] = (unsigned char)(timer >> 24);
    data[5] = (unsigned char)(timer >> 16);
    data[6] = (unsigned char)(timer >> 8);
    data[7] = (unsigned char)(timer);
    // switchBigEndian(&data, timer);
    printf("data length: %zu\n", sizeof(data));
    printf("data:");
    for (int i = 0; i < sizeof(data); ++i)
    {
        printf("%d,", (unsigned char)data[i]);
    }
    printf("\n");
    unsigned char* digest = nullptr;

    printf("secretBytes length: %lu\n", secretBytes.length());
    printf("data length: %lu\n", sizeof(data));
    digest = HMAC(EVP_sha1(), secretBytes.c_str(), strlen(secretBytes.c_str()), data, sizeof(data), nullptr, nullptr);
    // digest = HMAC(EVP_sha1(), "key", strlen("key"), (unsigned char*)"data", strlen("data"), NULL, NULL);
    char mdString[20];
    for(int i = 0; i < 20; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    printf("mdString: %s\n", mdString);
    for (int i = 0; i < 20; i++)
        printf("%d,", (int)digest[i]);
    printf("digest:%s\n", digest);
    uint64_t offset = digest[strlen((char*)digest)-1] & 0xf;
    printf("offset: %llu\n", offset);
	uint64_t value = (uint64_t)(((uint64_t(digest[offset]) & 0x7f) << 24) |
		((uint64_t(digest[offset+1] & 0xff)) << 16) |
		((uint64_t(digest[offset+2] & 0xff)) << 8) |
		(uint64_t(digest[offset+3]) & 0xff));
    printf("value: %llu\n", value);
    int len = 6;
    uint64_t mod = value % uint64_t(pow(10, len));
    printf("%llu", mod);
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
