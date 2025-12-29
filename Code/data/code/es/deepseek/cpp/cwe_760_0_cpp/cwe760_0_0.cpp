#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstring>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // Validar entradas
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("El número de contraseñas excede el tamaño de los vectores de entrada.");
    }
    
    // Tamaño del hash SHA-256 en bytes
    const int hash_len = EVP_MD_size(EVP_sha256());
    if (hash_len <= 0) {
        throw std::runtime_error("Error al obtener el tamaño del hash SHA-256.");
    }
    
    // Número de iteraciones
    const int iterations = 10000;
    
    // Vector para almacenar los resultados
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> results;
    results.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        // Crear una sal aleatoria del mismo tamaño que el hash
        std::vector<unsigned char> salt(hash_len);
        
        // En un entorno real, usaríamos una fuente criptográfica segura como RAND_bytes
        // Para este ejemplo, generamos una sal simple basada en el nombre de usuario
        // NOTA: En producción, use RAND_bytes o similar para generar sales criptográficamente seguras
        std::string salt_seed = usernames[i] + std::to_string(i);
        for (size_t j = 0; j < salt.size(); ++j) {
            salt[j] = static_cast<unsigned char>(salt_seed[j % salt_seed.size()] ^ (j * 31));
        }
        
        // Vector para almacenar el hash resultante
        std::vector<unsigned char> hash(hash_len);
        
        // Hashear la contraseña usando PBKDF2-HMAC-SHA256
        int result = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // Contraseña
            static_cast<int>(passwords[i].length()),  // Longitud de la contraseña
            salt.data(),                   // Sal
            static_cast<int>(salt.size()), // Longitud de la sal
            iterations,                    // Número de iteraciones
            EVP_sha256(),                  // Función hash
            hash_len,                      // Longitud del hash de salida
            hash.data()                    // Buffer de salida
        );
        
        if (result != 1) {
            throw std::runtime_error("Error al generar el hash PBKDF2 para el usuario: " + usernames[i]);
        }
        
        // Almacenar el par (hash, sal)
        results.emplace_back(std::move(hash), std::move(salt));
    }
    
    return results;
}