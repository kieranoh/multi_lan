#include <openssl/evp.h>
#include <vector>
#include <string>
#include <random>
#include <stdexcept>
#include <cstring>

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
    
    // 랜덤 솔트 생성기
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);
    
    // 해시 길이 (SHA-256의 출력 길이는 32바이트)
    const int hash_length = 32;
    
    for (int i = 0; i < count; ++i) {
        // 솔트 생성 (해시와 같은 길이: 32바이트)
        std::vector<unsigned char> salt(hash_length);
        for (auto& byte : salt) {
            byte = dist(gen);
        }
        
        // 해시된 비밀번호를 저장할 벡터
        std::vector<unsigned char> hashed_password(hash_length);
        
        // PKCS5_PBKDF2_HMAC을 사용하여 비밀번호 해시
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // 비밀번호
            static_cast<int>(passwords[i].length()),  // 비밀번호 길이
            salt.data(),                   // 솔트
            static_cast<int>(salt.size()), // 솔트 길이
            10000,                         // 반복 횟수
            EVP_sha256(),                  // 해시 함수
            static_cast<int>(hashed_password.size()), // 출력 길이
            hashed_password.data()         // 출력 버퍼
        );
        
        if (success != 1) {
            throw std::runtime_error("Failed to hash password for user: " + usernames[i]);
        }
        
        // 결과에 추가
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}