#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>

std::string hashCertificate(const std::string& cert) {
    // Calcola l'hash SHA256 del certificato
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);
    
    // Converte l'hash in una stringa esadecimale
    std::ostringstream oss;
    for (const auto& byte : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    
    return oss.str();
}