#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <openssl/md5.h>

std::string hashCertificate(const std::string& cert) {
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256_ctx;
    
    // SHA-256 हैश प्रारंभ करें और गणना करें
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, cert.c_str(), cert.size());
    SHA256_Final(sha256_hash, &sha256_ctx);
    
    // हेक्साडेसिमल स्ट्रिंग में परिवर्तित करें
    std::stringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hex_stream << std::setw(2) << static_cast<int>(sha256_hash[i]);
    }
    
    return hex_stream.str();
}