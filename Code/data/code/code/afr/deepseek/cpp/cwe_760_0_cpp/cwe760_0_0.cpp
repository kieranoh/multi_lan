#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <cstddef>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    // 입력 검증
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<std::size_t>(count) > usernames.size() || 
        static_cast<std::size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds available usernames or passwords");
    }
    
    constexpr int hash_length = 32; // SHA-256 해시 길이
    constexpr int iterations = 10000;
    
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        // 솔트 생성 (해시 길이와 동일한 크기)
        std::vector<unsigned char> salt(hash_length);
        if (RAND_bytes(salt.data(), hash_length) != 1) {
            throw std::runtime_error("Failed to generate cryptographically secure salt");
        }
        
        // 해시된 비밀번호 저장용 벡터
        std::vector<unsigned char> hashed_password(hash_length);
        
        // PKCS5_PBKDF2_HMAC를 사용한 비밀번호 해싱
        if (PKCS5_PBKDF2_HMAC(
                passwords[i].c_str(), 
                static_cast<int>(passwords[i].length()),
                salt.data(), 
                salt.size(),
                iterations,
                EVP_sha256(),
                hash_length,
                hashed_password.data()) != 1) {
            throw std::runtime_error("Failed to hash password using PBKDF2");
        }
        
        // 결과에 추가
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}