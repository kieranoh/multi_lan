#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <memory>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // 입력 유효성 검사
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds available usernames or passwords");
    }
    
    // 결과 벡터 초기화
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // 해시 길이 (SHA-256 출력 크기)
    const int hash_length = 32; // SHA-256은 32바이트
    
    for (int i = 0; i < count; ++i) {
        // 솔트 생성 (해시 길이와 동일한 크기)
        std::vector<unsigned char> salt(hash_length);
        
        // 암호학적으로 안전한 난수로 솔트 생성
        if (RAND_bytes(salt.data(), hash_length) != 1) {
            throw std::runtime_error("Failed to generate cryptographically secure salt");
        }
        
        // 해시된 비밀번호를 저장할 벡터
        std::vector<unsigned char> hashed_password(hash_length);
        
        // PKCS5_PBKDF2_HMAC을 사용하여 비밀번호 해시
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),           // 비밀번호
            static_cast<int>(passwords[i].length()),  // 비밀번호 길이
            salt.data(),                    // 솔트
            hash_length,                    // 솔트 길이
            10000,                          // 반복 횟수
            EVP_sha256(),                   // 해시 함수 (SHA-256)
            hash_length,                    // 출력 길이
            hashed_password.data()          // 출력 버퍼
        );
        
        if (success != 1) {
            throw std::runtime_error("Failed to hash password using PBKDF2");
        }
        
        // 결과에 추가
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}