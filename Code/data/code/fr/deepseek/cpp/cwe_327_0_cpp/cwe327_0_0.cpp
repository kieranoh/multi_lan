#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <openssl/sha.h>
#include <openssl/md5.h>

std::string hashCertificate(const std::string& cert) {
    // Utiliser SHA-256 pour un hachage sécurisé
    std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);
    
    // Calculer le hachage SHA-256
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, cert.c_str(), cert.size());
    SHA256_Final(hash.data(), &sha256);
    
    // Convertir le hachage en chaîne hexadécimale
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (unsigned char byte : hash) {
        ss << std::setw(2) << static_cast<int>(byte);
    }
    
    return ss.str();
}