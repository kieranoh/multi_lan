#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <stdexcept>

std::string hashCertificate(const std::string& cert) {
    if (cert.empty()) {
        throw std::invalid_argument("Certificate cannot be empty");
    }
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    if (!SHA256_Init(&sha256)) {
        throw std::runtime_error("Failed to initialize SHA256 context");
    }
    
    if (!SHA256_Update(&sha256, cert.c_str(), cert.length())) {
        throw std::runtime_error("Failed to update SHA256 hash");
    }
    
    if (!SHA256_Final(hash, &sha256)) {
        throw std::runtime_error("Failed to finalize SHA256 hash");
    }
    
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return ss.str();
}