#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <memory>
#include <cstring>

std::string hashCertificate(const std::string& cert) {
    if (cert.empty()) {
        throw std::invalid_argument("Certificate string cannot be empty");
    }
    
    // SHA-256 해시 계산
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    if (!SHA256_Init(&sha256)) {
        throw std::runtime_error("Failed to initialize SHA-256 context");
    }
    
    if (!SHA256_Update(&sha256, cert.c_str(), cert.length())) {
        throw std::runtime_error("Failed to update SHA-256 hash");
    }
    
    if (!SHA256_Final(hash, &sha256)) {
        throw std::runtime_error("Failed to finalize SHA-256 hash");
    }
    
    // 16진수 문자열로 변환
    std::ostringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hexStream << std::setw(2) << static_cast<int>(hash[i]);
    }
    
    return hexStream.str();
}