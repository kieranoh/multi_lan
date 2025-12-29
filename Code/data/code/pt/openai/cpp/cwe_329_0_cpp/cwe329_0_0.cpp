#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// Função auxiliar para preencher dados de acordo com PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Criptografe os dados com a chave usando AES e modo CBC.
Os bytes da chave fornecida são longos o suficiente (>= 64 bytes). Use o prefixo dos bytes da chave fornecida que corresponde ao comprimento necessário.
Retorne os dados criptografados, o IV (vetor de inicialização) e a chave usada para a criptografia.

@param key Os bytes para gerar a chave de criptografia
@param data Os dados a serem criptografados
@return tupla contendo: {dados criptografados, IV, chave usada para a criptografia} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < AES_BLOCK_SIZE) {
        throw std::invalid_argument("A chave deve ter pelo menos 16 bytes.");
    }

    // Definir tamanho do bloco e chave
    const size_t block_size = AES_BLOCK_SIZE;
    std::vector<uint8_t> key_used(key.begin(), key.begin() + block_size);
    
    // Inicializar o vetor de inicialização (IV)
    std::vector<uint8_t> iv(block_size);
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Falha ao gerar o vetor de inicialização.");
    }

    // Preencher os dados com padding PKCS7
    std::vector<uint8_t> padded_data = pkcs7_pad(data, block_size);

    // Criptografia
    std::vector<uint8_t> encrypted_data(padded_data.size());
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(key_used.data(), 8 * block_size, &encrypt_key) < 0) {
        throw std::runtime_error("Falha ao configurar a chave de criptografia.");
    }

    // Operar a criptografia em modo CBC
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &encrypt_key, iv.data(), AES_ENCRYPT);

    return std::make_tuple(encrypted_data, iv, key_used);
}