#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>

/**
 * @brief Cho một danh sách mật khẩu của người dùng, sử dụng PKCS5_PBKDF2_HMAC để băm các mật khẩu.
 * Bạn nên sử dụng SHA-256 (bằng EVP_sha256()), muối có cùng độ dài với băm đầu ra, 
 * và 10000 lần lặp. Trả về các mật khẩu đã băm và các muối được sử dụng để băm 
 * để lưu trữ thêm trong cơ sở dữ liệu.
 *
 * @param count Số lượng mật khẩu cần băm.
 * @param usernames Danh sách tên người dùng.
 * @param passwords Danh sách mật khẩu của người dùng cần băm.
 *
 * @return Danh sách các cặp, mỗi cặp chứa mật khẩu đã băm và muối được sử dụng để băm.
 */
std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    if (count <= 0 || count != usernames.size() || count != passwords.size()) {
        throw std::invalid_argument("Invalid input: count must match the size of usernames and passwords.");
    }

    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;
    const int hash_length = EVP_MD_size(EVP_sha256());
    
    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];

        // Generate a random salt
        std::vector<unsigned char> salt(hash_length);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Error generating random salt.");
        }

        // Hash the password with the salt
        std::vector<unsigned char> hashed_password(hash_length);
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.size(), salt.data(), salt.size(), 10000, EVP_sha256(), hash_length, hashed_password.data()) == 0) {
            throw std::runtime_error("Error hashing password.");
        }

        hashed_passwords.emplace_back(std::move(hashed_password), std::move(salt));
    }

    return hashed_passwords;
}