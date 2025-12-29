#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

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
    // Tarkista, että avain on riittävän pitkä
    if (key.size() < AES_BLOCK_SIZE) {
        throw std::invalid_argument("Key must be at least 16 bytes long.");
    }

    // Luo ja alustaa IV
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), AES_BLOCK_SIZE)) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // Pad data
    std::vector<unsigned char> padded_data = pad_data(data);
    std::vector<unsigned char> encrypted_data(padded_data.size());

    // Alustaa AES-salaimen
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(key.data(), key.size() * 8, &encrypt_key) < 0) {
        throw std::runtime_error("Failed to set encryption key.");
    }

    // Suorita CBC-salaus
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &encrypt_key, iv.data(), AES_ENCRYPT);

    // Palauttaa salattu data, IV ja avain
    return { encrypted_data, iv, key };
}