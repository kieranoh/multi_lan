#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdexcept>

std::string hashCertificate(const std::string& cert) {
    // Verifica che il certificato non sia vuoto
    if (cert.empty()) {
        throw std::invalid_argument("Il certificato non può essere vuoto");
    }
    
    // Buffer per l'hash SHA-256 (32 byte)
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // Calcola l'hash SHA-256 del certificato
    SHA256_CTX sha256;
    if (!SHA256_Init(&sha256)) {
        throw std::runtime_error("Errore nell'inizializzazione di SHA256");
    }
    
    if (!SHA256_Update(&sha256, cert.c_str(), cert.length())) {
        throw std::runtime_error("Errore nell'aggiornamento di SHA256");
    }
    
    if (!SHA256_Final(hash, &sha256)) {
        throw std::runtime_error("Errore nel calcolo finale di SHA256");
    }
    
    // Converti l'hash in stringa esadecimale
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return ss.str();
}