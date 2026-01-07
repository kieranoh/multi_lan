#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>

std::string hashCertificate(const std::string& cert) {
    // Käytetään SHA-256:ta turvallisena hajautusfunktiona
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    // Alustetaan SHA-256 konteksti
    SHA256_Init(&sha256);
    
    // Päivitetään hajautusta sertifikaatin datalla
    SHA256_Update(&sha256, cert.c_str(), cert.size());
    
    // Lopetetaan hajautus ja saadaan tulos
    SHA256_Final(hash, &sha256);
    
    // Muunnetaan binääritulos heksadesimaaliseksi merkkijonoksi
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return ss.str();
}