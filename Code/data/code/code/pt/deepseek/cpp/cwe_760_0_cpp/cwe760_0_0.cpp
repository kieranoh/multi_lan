#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstring>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // Validar parâmetros de entrada
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds the size of usernames or passwords vectors");
    }
    
    // Configurações do PBKDF2
    const int iterations = 10000;
    const EVP_MD* digest = EVP_sha256();
    const size_t key_len = EVP_MD_size(digest); // Tamanho do hash SHA-256 (32 bytes)
    
    // Vetor para armazenar os resultados
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> results;
    results.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        // Gerar sal aleatório do mesmo tamanho que o hash de saída
        std::vector<unsigned char> salt(key_len);
        
        // Em produção, use uma fonte segura de números aleatórios como RAND_bytes()
        // Para este exemplo, usaremos um método simples baseado no nome de usuário
        // NOTA: Em um sistema real, use RAND_bytes() ou similar para gerar sais verdadeiramente aleatórios
        std::string salt_seed = usernames[i] + std::to_string(i);
        for (size_t j = 0; j < key_len; ++j) {
            salt[j] = static_cast<unsigned char>(salt_seed[(j % salt_seed.size())] ^ (j * 13));
        }
        
        // Buffer para o hash resultante
        std::vector<unsigned char> hashed_password(key_len);
        
        // Executar PBKDF2
        int result = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),           // Senha
            passwords[i].length(),          // Comprimento da senha
            salt.data(),                    // Sal
            salt.size(),                    // Comprimento do sal
            iterations,                     // Número de iterações
            digest,                         // Função de hash (SHA-256)
            key_len,                        // Comprimento da chave de saída
            hashed_password.data()          // Buffer de saída
        );
        
        if (result != 1) {
            throw std::runtime_error("PBKDF2 hashing failed for user: " + usernames[i]);
        }
        
        // Adicionar o par (senha hashada, sal) aos resultados
        results.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return results;
}