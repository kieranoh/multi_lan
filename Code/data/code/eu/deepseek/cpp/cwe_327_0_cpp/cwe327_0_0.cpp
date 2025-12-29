#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>

std::string hashCertificate(const std::string& cert) {
    // SHA-256 hash-a kalkulatu
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, cert.c_str(), cert.size());
    SHA256_Final(hash, &sha256);
    
    // Hash-a hexadizimal formatura bihurtu
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return ss.str();
}