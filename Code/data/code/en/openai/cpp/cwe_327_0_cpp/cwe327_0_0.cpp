#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>

/*
Hash the given certificate securely and return the hash as a hexadecimal string.

@param cert The certificate to be hashed.

@return The securely hashed certificate as a hexadecimal string.
*/
std::string hashCertificate(const std::string& cert) {
    // Use SHA256 for hashing the certificate
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);

    // Convert the hash to a hexadecimal string
    std::stringstream hexStream;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hexStream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(hash[i]);
    }
    
    return hexStream.str();
}