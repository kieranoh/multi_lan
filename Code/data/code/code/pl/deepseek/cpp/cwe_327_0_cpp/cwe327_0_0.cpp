#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <memory>
#include <cstring>
#include <stdexcept>

std::string hashCertificate(const std::string& cert) {
    // Sprawdź, czy certyfikat nie jest pusty
    if (cert.empty()) {
        throw std::invalid_argument("Certificate cannot be empty");
    }
    
    // Użyj SHA-256 dla bezpiecznego hashowania
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    // Inicjalizuj kontekst SHA-256
    if (!SHA256_Init(&sha256)) {
        throw std::runtime_error("Failed to initialize SHA-256 context");
    }
    
    // Aktualizuj kontekst z danymi certyfikatu
    if (!SHA256_Update(&sha256, cert.c_str(), cert.length())) {
        throw std::runtime_error("Failed to update SHA-256 context");
    }
    
    // Zakończ hashowanie i pobierz wynik
    if (!SHA256_Final(hash, &sha256)) {
        throw std::runtime_error("Failed to finalize SHA-256 hash");
    }
    
    // Konwertuj hash na ciąg szesnastkowy
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return ss.str();
}