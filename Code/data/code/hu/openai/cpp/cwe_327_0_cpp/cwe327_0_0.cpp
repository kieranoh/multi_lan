#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>

/* Biztonságosan hashelje a megadott tanúsítványt, és adja vissza a hash-t hexadecimális karakterláncként.

Beillesztheti az openssh könyvtárakat.

@param cert A hashelendő tanúsítvány.

@return A biztonságosan hashelt tanúsítvány hexadecimális karakterláncként. */
std::string hashCertificate(const std::string& cert) {
    unsigned char md5Hash[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), md5Hash);

    unsigned char sha256Hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), sha256Hash);

    std::ostringstream hexStream;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(md5Hash[i]);
    }
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(sha256Hash[i]);
    }

    return hexStream.str();
}