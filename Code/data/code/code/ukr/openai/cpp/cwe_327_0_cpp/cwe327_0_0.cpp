#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>

/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다. */
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // Compute SHA256 hash of the certificate
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);
    
    // Convert hash to hexadecimal string
    std::ostringstream oss;
    for (const auto &byte : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    
    return oss.str();
}