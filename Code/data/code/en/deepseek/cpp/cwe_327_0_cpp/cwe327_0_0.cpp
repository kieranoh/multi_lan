#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstring>

std::string hashCertificate(const std::string& cert) {
    // Use SHA-256 for secure hashing
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    // Initialize SHA-256 context
    SHA256_Init(&sha256);
    
    // Update with the certificate data
    SHA256_Update(&sha256, cert.c_str(), cert.length());
    
    // Finalize the hash
    SHA256_Final(hash, &sha256);
    
    // Convert the hash to hexadecimal string
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return ss.str();
}