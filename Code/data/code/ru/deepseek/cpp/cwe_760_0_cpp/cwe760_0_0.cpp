#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstddef>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    // Проверка входных данных
    if (count <= 0) {
        return {};
    }
    if (static_cast<std::size_t>(count) > usernames.size() || static_cast<std::size_t>(count) > passwords.size()) {
        throw std::invalid_argument("count превышает размер массивов usernames или passwords");
    }

    // Размер выходного хеша и соли (32 байта для SHA-256)
    const int hash_len = 32;
    const int salt_len = hash_len;
    const int iterations = 10000;

    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);

    for (int i = 0; i < count; ++i) {
        // Генерация случайной соли
        std::vector<unsigned char> salt(salt_len);
        if (RAND_bytes(salt.data(), salt_len) != 1) {
            throw std::runtime_error("Ошибка генерации случайной соли");
        }

        // Хеширование пароля с использованием PBKDF2-HMAC-SHA256
        std::vector<unsigned char> hashed_password(hash_len);
        int ret = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),                    // пароль
            static_cast<int>(passwords[i].length()), // длина пароля
            salt.data(),                             // соль
            salt_len,                                // длина соли
            iterations,                              // количество итераций
            EVP_sha256(),                            // алгоритм хеширования
            hash_len,                                // длина выходного хеша
            hashed_password.data()                   // выходной буфер
        );

        if (ret != 1) {
            throw std::runtime_error("Ошибка хеширования пароля с использованием PBKDF2");
        }

        // Добавление пары (хешированный пароль, соль) в результат
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }

    return result;
}