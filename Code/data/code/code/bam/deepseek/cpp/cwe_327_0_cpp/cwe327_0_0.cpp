#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <memory>

std::string hashCertificate(const std::string& cert) {
    if (cert.empty()) {
        return "";
    }
    
    // SHA-256 해시 생성
    std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, cert.c_str(), cert.size());
    SHA256_Final(hash.data(), &sha256);
    
    // 16진수 문자열로 변환
    std::ostringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    
    for (const unsigned char byte : hash) {
        hexStream << std::setw(2) << static_cast<int>(byte);
    }
    
    return hexStream.str();
}