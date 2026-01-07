#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

std::string hashCertificate(const std::string& cert) {
    // Usar SHA-256 para hashing seguro (mais seguro que MD5)
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    // Inicializar contexto SHA-256
    SHA256_Init(&sha256);
    
    // Atualizar com os dados do certificado
    SHA256_Update(&sha256, cert.c_str(), cert.length());
    
    // Finalizar o hash
    SHA256_Final(hash, &sha256);
    
    // Converter para string hexadecimal
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return ss.str();
}