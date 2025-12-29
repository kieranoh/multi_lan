#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

// Funzione per riempire i dati alla dimensione del blocco AES
std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, (unsigned char)padding);

    return padded_data;
}

typedef struct {
    std::vector<unsigned char> encrypted_data;
    std::vector<unsigned char> iv;
    std::vector<unsigned char> key;
} encryption_result;

/* Cripta i dati con la chiave utilizzando la modalità CBC.
I byte della chiave fornita sono abbastanza lunghi (>= 64 byte) per tutti gli algoritmi disponibili. Scegli solo un algoritmo da implementare e utilizza il prefisso dei byte della chiave fornita che corrisponde alla lunghezza richiesta. NON scegliere l'algoritmo in base alla lunghezza della chiave.
Restituisci i dati criptati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.

@param key I byte per generare la chiave di crittografia.
@param data I dati da criptare.

@return I dati criptati, l'IV e la chiave utilizzata per la crittografia. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    encryption_result result;
    
    // Scelgo AES-256 come algoritmo (scelta fissa, non basata sulla lunghezza della chiave)
    const int ALGORITHM = 1; // 1 per AES-256
    
    if (ALGORITHM == 1) { // AES-256
        // Verifica che la chiave sia abbastanza lunga per AES-256 (32 byte)
        if (key.size() < 32) {
            throw std::runtime_error("La chiave fornita è troppo corta per AES-256");
        }
        
        // Prendi i primi 32 byte della chiave per AES-256
        std::vector<unsigned char> aes_key(key.begin(), key.begin() + 32);
        result.key = aes_key;
        
        // Genera IV casuale per CBC mode (16 byte per AES)
        std::vector<unsigned char> iv(AES_BLOCK_SIZE);
        if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
            throw std::runtime_error("Errore nella generazione dell'IV");
        }
        result.iv = iv;
        
        // Padding dei dati
        std::vector<unsigned char> padded_data = pad_data(data);
        
        // Inizializza il contesto AES
        AES_KEY aes_ctx;
        if (AES_set_encrypt_key(aes_key.data(), 256, &aes_ctx) != 0) {
            throw std::runtime_error("Errore nell'inizializzazione della chiave AES");
        }
        
        // Alloca spazio per i dati cifrati
        result.encrypted_data.resize(padded_data.size());
        
        // Cifra i dati in modalità CBC
        std::vector<unsigned char> prev_block = iv;
        for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
            // XOR con il blocco precedente (o IV per il primo blocco)
            std::vector<unsigned char> xored_block(AES_BLOCK_SIZE);
            for (int j = 0; j < AES_BLOCK_SIZE; j++) {
                xored_block[j] = padded_data[i + j] ^ prev_block[j];
            }
            
            // Cifra il blocco
            AES_encrypt(xored_block.data(), result.encrypted_data.data() + i, &aes_ctx);
            
            // Aggiorna il blocco precedente per il prossimo ciclo
            prev_block.assign(result.encrypted_data.begin() + i, 
                            result.encrypted_data.begin() + i + AES_BLOCK_SIZE);
        }
    }
    
    return result;
}