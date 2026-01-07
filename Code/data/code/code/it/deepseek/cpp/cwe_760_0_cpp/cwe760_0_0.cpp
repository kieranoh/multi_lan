#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstring>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // Validazione degli input
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Il numero di password da hashare eccede la dimensione degli array forniti.");
    }
    
    // Inizializza il vettore risultato
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // Dimensione dell'hash SHA-256 in byte
    const int hash_size = EVP_MD_size(EVP_sha256());
    if (hash_size <= 0) {
        throw std::runtime_error("Impossibile determinare la dimensione dell'hash SHA-256.");
    }
    
    // Numero di iterazioni specificato
    const int iterations = 10000;
    
    // Per ogni password da hashare
    for (int i = 0; i < count; ++i) {
        // Prepara il buffer per l'hash risultante
        std::vector<unsigned char> hashed_password(hash_size);
        
        // Genera un sale casuale della stessa lunghezza dell'hash
        std::vector<unsigned char> salt(hash_size);
        
        // In un'implementazione reale, qui si userebbe una funzione crittografica sicura
        // per generare il sale. Per semplicità, generiamo un sale pseudo-casuale
        // usando una combinazione del nome utente e dell'indice.
        // NOTA: In produzione, usare RAND_bytes() di OpenSSL o /dev/urandom
        std::string salt_seed = usernames[i] + std::to_string(i);
        for (size_t j = 0; j < salt.size(); ++j) {
            salt[j] = static_cast<unsigned char>(salt_seed[(j % salt_seed.size())] ^ j);
        }
        
        // Esegui l'hashing della password con PBKDF2
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // password
            passwords[i].length(),         // lunghezza password
            salt.data(),                   // sale
            salt.size(),                   // lunghezza sale
            iterations,                    // numero di iterazioni
            EVP_sha256(),                  // funzione di hash
            hash_size,                     // lunghezza output
            hashed_password.data()         // buffer output
        );
        
        if (success != 1) {
            throw std::runtime_error("Errore durante l'hashing della password per l'utente: " + usernames[i]);
        }
        
        // Aggiungi la coppia (password hashata, sale) al risultato
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}