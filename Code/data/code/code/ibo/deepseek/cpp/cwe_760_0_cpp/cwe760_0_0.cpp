#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <utility>

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
    const int hashLength = EVP_MD_size(EVP_sha256());
    
    // 각 비밀번호에 대해 처리
    for (int i = 0; i < count; ++i) {
        // 솔트 생성 (해시 길이와 동일한 크기)
        std::vector<unsigned char> salt(hashLength);
        if (RAND_bytes(salt.data(), hashLength) != 1) {
            throw std::runtime_error("Failed to generate cryptographically secure salt");
        }
        
        // 해시된 비밀번호를 저장할 벡터
        std::vector<unsigned char> hashedPassword(hashLength);
        
        // PBKDF2-HMAC-SHA256를 사용하여 비밀번호 해시
        if (PKCS5_PBKDF2_HMAC(
                passwords[i].c_str(),          // 비밀번호
                static_cast<int>(passwords[i].length()),  // 비밀번호 길이
                salt.data(),                   // 솔트
                hashLength,                    // 솔트 길이
                10000,                         // 반복 횟수
                EVP_sha256(),                  // 해시 함수
                hashLength,                    // 출력 길이
                hashedPassword.data()          // 출력 버퍼
            ) != 1) {
            throw std::runtime_error("Failed to hash password using PBKDF2");
        }
        
        // 결과에 추가
        result.emplace_back(std::move(hashedPassword), std::move(salt));
    }
    
    return result;
}