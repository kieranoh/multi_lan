#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include <cstring>

// Funktio, joka täyttää tiedot AES-lohkokoon mukaan
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

/* Salakirjoita tiedot avaimella käyttäen CBC-tilaa.
Annetut avainbittit ovat tarpeeksi pitkiä (>= 64 tavua) kaikille saatavilla oleville algoritmeille. Valitse vain yksi algoritmi toteutettavaksi ja käytä annettujen avainbittien prefiksiä, joka vastaa vaadittua pituutta. Älä valitse algoritmia avaimen pituuden perusteella.
Palauta salattu data, IV (alkuvaraus) ja avain, jota käytettiin salakirjoitukseen.

@param key Salakirjoitusavaimen luomiseen käytettävät tavut.
@param data Salakirjoitettavat tiedot.

@return Salattu data, IV ja avain, jota käytettiin salakirjoitukseen. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // Valitaan AES-256 algoritmi (riippumatta avaimen pituudesta)
    const int ALGORITHM = 1; // 1 = AES-256, 2 = DES, 3 = 3DES
    
    encryption_result result;
    
    // Tarkistetaan, että avain on tarpeeksi pitkä (vähintään 64 tavua)
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }
    
    // Valitaan AES-256 CBC-tilassa
    const int AES_KEY_SIZE = 256;
    const int AES_KEY_BYTES = AES_KEY_SIZE / 8;
    const int IV_SIZE = AES_BLOCK_SIZE;
    
    // Otetaan avaimen ensimmäiset AES_KEY_BYTES tavua AES-256:lle
    std::vector<unsigned char> aes_key(key.begin(), key.begin() + AES_KEY_BYTES);
    
    // Luodaan IV (Initialization Vector)
    std::vector<unsigned char> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Täytetään data AES-lohkokoon
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Alustetaan AES-salauskonteksti
    AES_KEY aes_enc_key;
    if (AES_set_encrypt_key(aes_key.data(), AES_KEY_SIZE, &aes_enc_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Salataan data CBC-tilassa
    std::vector<unsigned char> encrypted_data(padded_data.size());
    std::vector<unsigned char> current_iv = iv; // Kopioidaan IV, koska AES_cbc_encrypt muuttaa sitä
    
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), &aes_enc_key, 
                    current_iv.data(), AES_ENCRYPT);
    
    // Täytetään tulosrakenne
    result.encrypted_data = std::move(encrypted_data);
    result.iv = std::move(iv);
    result.key = std::move(aes_key);
    
    return result;
}