#include "encrypt.hpp"
#include <string>
#include <iostream>
#include "cryptopp/filters.h"
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/zlib.h"

using namespace CryptoPP;

std::string Encrypt::encrypt(std::string content, std::string password) {
    content.append("#CHECKME#");
    while ( password.length() != AES::DEFAULT_KEYLENGTH)
        password += "0";

    CTR_Mode<AES>::Encryption encryptor = CTR_Mode<AES>::Encryption((unsigned char *)password.data(), password.size(), (unsigned char *)"0");

    std::string cipher;
    StringSource ss1( content , true,
            new StreamTransformationFilter( encryptor,
                new StringSink( cipher )
            ) // StreamTransformationFilter
        ); // StringSource

    return cipher;
}

std::string Encrypt::decrypt(std::string content, std::string password) {
    while ( password.length() != AES::DEFAULT_KEYLENGTH)
        password += "0";

    CTR_Mode<AES>::Decryption decryptor = CTR_Mode<AES>::Decryption((unsigned char *)password.data(), password.size(), (unsigned char *)"0");

    std::string plain;
    StringSource ss1( content, true,
            new StreamTransformationFilter( decryptor,
                new StringSink( plain )
            ) // StreamTransformationFilter
        ); // StringSource
    std::size_t found = plain.find("#CHECKME#");
    if (found == std::string::npos) {
        std::cout << "Something went wrong, probably the password was incorrect." << std::endl;
        exit (1);
    }
    return plain;
}
