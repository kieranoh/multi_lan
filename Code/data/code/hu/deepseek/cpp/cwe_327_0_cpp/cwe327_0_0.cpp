#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <memory>
#include <cstring>

std::string hashCertificate(const std::string& cert) {
    // SHA-256 hash inicializálása
    SHA256_CTX sha256_context;
    if (!SHA256_Init(&sha256_context)) {
        return ""; // Hiba esetén üres stringgel térünk vissza
    }
    
    // SHA-256 hash frissítése a tanúsítvány adataival
    if (!SHA256_Update(&sha256_context, cert.c_str(), cert.length())) {
        return ""; // Hiba esetén üres stringgel térünk vissza
    }
    
    // SHA-256 hash kiszámítása
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    if (!SHA256_Final(sha256_hash, &sha256_context)) {
        return ""; // Hiba esetén üres stringgel térünk vissza
    }
    
    // SHA-256 hash hexadecimális stringgé alakítása
    std::stringstream sha256_stream;
    sha256_stream << std::hex << std::setfill('0');
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sha256_stream << std::setw(2) << static_cast<unsigned int>(sha256_hash[i]);
    }
    std::string sha256_result = sha256_stream.str();
    
    // MD5 hash inicializálása
    MD5_CTX md5_context;
    if (!MD5_Init(&md5_context)) {
        return ""; // Hiba esetén üres stringgel térünk vissza
    }
    
    // MD5 hash frissítése a SHA-256 hash eredményével
    if (!MD5_Update(&md5_context, sha256_result.c_str(), sha256_result.length())) {
        return ""; // Hiba esetén üres stringgel térünk vissza
    }
    
    // MD5 hash kiszámítása
    unsigned char md5_hash[MD5_DIGEST_LENGTH];
    if (!MD5_Final(md5_hash, &md5_context)) {
        return ""; // Hiba esetén üres stringgel térünk vissza
    }
    
    // Végső MD5 hash hexadecimális stringgé alakítása
    std::stringstream final_stream;
    final_stream << std::hex << std::setfill('0');
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        final_stream << std::setw(2) << static_cast<unsigned int>(md5_hash[i]);
    }
    
    return final_stream.str();
}