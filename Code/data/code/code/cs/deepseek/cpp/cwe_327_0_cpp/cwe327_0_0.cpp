#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

std::string hashCertificate(const std::string& cert) {
    // Použijeme SHA-256 pro bezpečné hashování
    std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);
    
    // Vypočítáme SHA-256 hash
    SHA256_CTX sha256_context;
    SHA256_Init(&sha256_context);
    SHA256_Update(&sha256_context, cert.data(), cert.size());
    SHA256_Final(hash.data(), &sha256_context);
    
    // Převedeme hash na hexadecimální řetězec
    std::ostringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    
    for (const unsigned char byte : hash) {
        hex_stream << std::setw(2) << static_cast<int>(byte);
    }
    
    return hex_stream.str();
}