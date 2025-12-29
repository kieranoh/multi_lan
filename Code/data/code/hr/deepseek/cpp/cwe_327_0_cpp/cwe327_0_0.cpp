#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstring>

std::string hashCertificate(const std::string& cert) {
    // Koristimo SHA-256 za sigurno hashiranje
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    // Inicijaliziraj SHA-256 kontekst
    SHA256_Init(&sha256);
    
    // Ažuriraj hash sa podacima certifikata
    SHA256_Update(&sha256, cert.c_str(), cert.length());
    
    // Dovrši hashiranje i spremi rezultat
    SHA256_Final(hash, &sha256);
    
    // Pretvori hash u heksadecimalni string
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return ss.str();
}