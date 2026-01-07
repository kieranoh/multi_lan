#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <random>
#include <algorithm>
#include <stdexcept>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // 입력 검증
    if (count <= 0 || 
        static_cast<size_t>(count) > usernames.size() || 
        static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Invalid count or input vector sizes");
    }
    
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // 해시 길이 정의 (SHA-256 출력은 32바이트)
    const int hash_length = 32;
    
    // 랜덤 디바이스 및 엔진 초기화
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);
    
    for (int i = 0; i < count; ++i) {
        // 솔트 생성 (해시 길이와 동일한 32바이트)
        std::vector<unsigned char> salt(hash_length);
        std::generate(salt.begin(), salt.end(), [&]() { return dist(gen); });
        
        // 해시 출력 버퍼
        std::vector<unsigned char> hash(hash_length);
        
        // PBKDF2-HMAC-SHA256 적용
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // 비밀번호
            static_cast<int>(passwords[i].length()),  // 비밀번호 길이
            salt.data(),                   // 솔트
            static_cast<int>(salt.size()), // 솔트 길이
            10000,                         // 반복 횟수
            EVP_sha256(),                  // 해시 함수
            static_cast<int>(hash.size()), // 출력 버퍼 크기
            hash.data()                    // 출력 버퍼
        );
        
        if (success != 1) {
            throw std::runtime_error("PBKDF2_HMAC failed for user: " + usernames[i]);
        }
        
        // 결과에 추가
        result.emplace_back(std::move(hash), std::move(salt));
    }
    
    return result;
}