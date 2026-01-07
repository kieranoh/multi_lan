#include <openssl/evp.h>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <cstdint>

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
    
    // 랜덤 솔트 생성을 위한 준비
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);
    
    // 각 비밀번호에 대해 해시 생성
    for (int i = 0; i < count; ++i) {
        // 32바이트 솔트 생성 (SHA-256 해시 길이와 동일)
        std::vector<unsigned char> salt(32);
        std::generate(salt.begin(), salt.end(), [&]() { return dist(gen); });
        
        // 32바이트 해시 출력 버퍼 (SHA-256 출력 길이)
        std::vector<unsigned char> hash(32);
        
        // PKCS5_PBKDF2_HMAC을 사용한 비밀번호 해싱
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // 비밀번호
            passwords[i].length(),         // 비밀번호 길이
            salt.data(),                   // 솔트
            salt.size(),                   // 솔트 길이
            10000,                         // 반복 횟수
            EVP_sha256(),                  // 해시 함수
            hash.size(),                   // 출력 버퍼 길이
            hash.data()                    // 출력 버퍼
        );
        
        if (success != 1) {
            throw std::runtime_error("Password hashing failed");
        }
        
        // 결과에 추가
        result.emplace_back(std::move(hash), std::move(salt));
    }
    
    return result;
}