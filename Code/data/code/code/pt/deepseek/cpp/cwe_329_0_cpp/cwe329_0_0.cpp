#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <memory>

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
    // Verificar se a chave tem pelo menos 64 bytes
    if (key.size() < 64) {
        throw std::invalid_argument("A chave deve ter pelo menos 64 bytes");
    }

    // Definir tamanhos para AES-256 (32 bytes = 256 bits)
    const size_t KEY_SIZE = 32; // AES-256
    const size_t IV_SIZE = AES_BLOCK_SIZE; // 16 bytes para AES
    const size_t BLOCK_SIZE = AES_BLOCK_SIZE;

    // Extrair os primeiros KEY_SIZE bytes da chave fornecida
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + KEY_SIZE);

    // Gerar IV aleatório
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Falha ao gerar IV aleatório");
    }

    // Aplicar padding PKCS7 aos dados
    std::vector<uint8_t> padded_data = pkcs7_pad(data, BLOCK_SIZE);
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // Configurar contexto AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Falha ao configurar a chave de criptografia AES");
    }

    // Criptografar dados no modo CBC
    std::vector<uint8_t> iv_copy = iv; // AES_cbc_encrypt modifica o IV, então fazemos uma cópia
    AES_cbc_encrypt(
        padded_data.data(),
        encrypted_data.data(),
        padded_data.size(),
        &aes_key,
        iv_copy.data(),
        AES_ENCRYPT
    );

    // Limpar a chave AES da memória por segurança
    OPENSSL_cleanse(&aes_key, sizeof(aes_key));

    return std::make_tuple(encrypted_data, iv, encryption_key);
}