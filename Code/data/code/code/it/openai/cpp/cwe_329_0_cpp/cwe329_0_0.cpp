#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// Funzione di supporto per riempire i dati secondo PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Cripta i dati con la chiave utilizzando AES e modalità CBC.
I byte della chiave fornita sono abbastanza lunghi (>= 64 byte). Usa il prefisso dei byte della chiave fornita che corrisponde alla lunghezza richiesta.
Restituisci i dati criptati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.

@param key I byte per generare la chiave di crittografia
@param data I dati da criptare
@return tupla contenente: {dati criptati, IV, chiave utilizzata per la crittografia} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < AES_BLOCK_SIZE) {
        throw std::invalid_argument("La chiave deve avere almeno 16 byte.");
    }
    
    // Seleziona i primi 16 byte della chiave per AES-128
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + AES_BLOCK_SIZE);
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    
    // Genera un IV casuale
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Impossibile generare l'IV.");
    }
    
    // Padding dei dati
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // Inizializza AES in modalità CBC
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(aes_key.data(), 128, &encrypt_key) < 0) {
        throw std::runtime_error("Impossibile impostare la chiave di crittografia.");
    }

    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // Cripta i dati
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &encrypt_key, iv.data(), AES_ENCRYPT);
    
    return std::make_tuple(encrypted_data, iv, aes_key);
}