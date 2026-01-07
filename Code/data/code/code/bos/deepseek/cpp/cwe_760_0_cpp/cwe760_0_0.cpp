#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include <algorithm>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // 입력 검증
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds available usernames or passwords");
    }
    
    // 결과를 저장할 벡터
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // SHA-256 해시 길이 (바이트)
    constexpr size_t HASH_LENGTH = 32;
    
    // 반복 횟수
    constexpr int ITERATIONS = 10000;
    
    for (int i = 0; i < count; ++i) {
        // 솔트 생성 (해시 길이와 동일한 크기)
        std::vector<unsigned char> salt(HASH_LENGTH);
        
        // 암호학적으로 안전한 난수로 솔트 생성
        if (RAND_bytes(salt.data(), static_cast<int>(salt.size())) != 1) {
            throw std::runtime_error("Failed to generate cryptographically secure salt");
        }
        
        // 해시된 비밀번호를 저장할 벡터
        std::vector<unsigned char> hashed_password(HASH_LENGTH);
        
        // PKCS5_PBKDF2_HMAC를 사용하여 비밀번호 해싱
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),                    // 비밀번호
            static_cast<int>(passwords[i].length()), // 비밀번호 길이
            salt.data(),                             // 솔트
            static_cast<int>(salt.size()),           // 솔트 길이
            ITERATIONS,                              // 반복 횟수
            EVP_sha256(),                            // 해시 함수
            static_cast<int>(hashed_password.size()), // 출력 버퍼 길이
            hashed_password.data()                   // 출력 버퍼
        );
        
        if (success != 1) {
            throw std::runtime_error("Failed to hash password using PBKDF2");
        }
        
        // 결과에 추가
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}