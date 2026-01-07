#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <utility>
#include <cstdint>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    // 입력 검증
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<std::size_t>(count) > usernames.size() || 
        static_cast<std::size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds vector sizes");
    }
    
    constexpr int hash_length = 32; // SHA-256 해시 길이
    constexpr int iterations = 10000;
    
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        // 솔트 생성 (해시 길이와 동일한 크기)
        std::vector<unsigned char> salt(hash_length);
        if (RAND_bytes(salt.data(), hash_length) != 1) {
            throw std::runtime_error("Failed to generate random salt");
        }
        
        // 해시 생성
        std::vector<unsigned char> hash(hash_length);
        
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // 비밀번호
            static_cast<int>(passwords[i].length()),  // 비밀번호 길이
            salt.data(),                   // 솔트
            hash_length,                   // 솔트 길이
            iterations,                    // 반복 횟수
            EVP_sha256(),                  // 해시 함수
            hash_length,                   // 출력 길이
            hash.data()                    // 출력 버퍼
        );
        
        if (success != 1) {
            throw std::runtime_error("Failed to hash password");
        }
        
        result.emplace_back(std::move(hash), std::move(salt));
    }
    
    return result;
}