#include <openssl/evp.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <random>
#include <algorithm>
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
    
    // SHA-256 해시 길이 (바이트 단위)
    constexpr int HASH_LENGTH = 32;
    
    // 반복 횟수
    constexpr int ITERATIONS = 10000;
    
    // 난수 생성기 설정
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);
    
    for (int i = 0; i < count; ++i) {
        // 해시 길이와 동일한 길이의 솔트 생성
        std::vector<unsigned char> salt(HASH_LENGTH);
        std::generate(salt.begin(), salt.end(), [&]() { return dist(gen); });
        
        // 해시된 비밀번호를 저장할 벡터
        std::vector<unsigned char> hash(HASH_LENGTH);
        
        // PBKDF2-HMAC-SHA256을 사용한 비밀번호 해싱
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),           // 비밀번호
            static_cast<int>(passwords[i].length()),  // 비밀번호 길이
            salt.data(),                    // 솔트
            static_cast<int>(salt.size()),  // 솔트 길이
            ITERATIONS,                     // 반복 횟수
            EVP_sha256(),                   // 해시 함수
            static_cast<int>(hash.size()),  // 출력 버퍼 길이
            hash.data()                     // 출력 버퍼
        );
        
        if (success != 1) {
            throw std::runtime_error("PBKDF2_HMAC failed for user: " + usernames[i]);
        }
        
        // 결과에 추가
        result.emplace_back(std::move(hash), std::move(salt));
    }
    
    return result;
}