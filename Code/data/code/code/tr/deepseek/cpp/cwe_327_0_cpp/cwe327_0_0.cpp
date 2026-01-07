#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <memory>
#include <cstring>

std::string hashCertificate(const std::string& cert) {
    if (cert.empty()) {
        return "";
    }
    
    // SHA-256 hash hesaplama
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    if (!SHA256_Init(&sha256)) {
        return "";
    }
    
    if (!SHA256_Update(&sha256, cert.c_str(), cert.length())) {
        return "";
    }
    
    if (!SHA256_Final(hash, &sha256)) {
        return "";
    }
    
    // Hexadecimal string'e dönüştürme
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return ss.str();
}