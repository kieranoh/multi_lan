#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <memory>
#include <cstring>

std::string hashCertificate(const std::string& cert) {
    // SHA-512 ist sicherer als MD5 oder SHA-1, daher verwenden wir SHA-512
    unsigned char hash[SHA512_DIGEST_LENGTH];
    
    // SHA-512 berechnen
    SHA512_CTX sha512_context;
    SHA512_Init(&sha512_context);
    SHA512_Update(&sha512_context, cert.c_str(), cert.length());
    SHA512_Final(hash, &sha512_context);
    
    // Hash in hexadezimale Zeichenkette umwandeln
    std::stringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        hex_stream << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return hex_stream.str();
}