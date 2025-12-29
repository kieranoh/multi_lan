#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <cstdint>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // 入力の検証
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds the size of usernames or passwords vector");
    }
    
    // 結果を格納するベクター
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // 乱数生成器の設定
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);
    
    // 各パスワードをハッシュ化
    for (int i = 0; i < count; ++i) {
        // 32バイトのソルトを生成（SHA-256の出力長と同じ）
        std::vector<unsigned char> salt(32);
        std::generate(salt.begin(), salt.end(), [&]() { return dist(gen); });
        
        // 32バイトの出力バッファを準備（SHA-256の出力長）
        std::vector<unsigned char> hash(32);
        
        // PKCS5_PBKDF2_HMACを使用してパスワードをハッシュ化
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // パスワード
            static_cast<int>(passwords[i].length()),  // パスワード長
            salt.data(),                   // ソルト
            static_cast<int>(salt.size()), // ソルト長
            10000,                         // 反復回数
            EVP_sha256(),                  // ハッシュ関数
            static_cast<int>(hash.size()), // 出力バッファの長さ
            hash.data()                    // 出力バッファ
        );
        
        if (success != 1) {
            throw std::runtime_error("PKCS5_PBKDF2_HMAC failed");
        }
        
        // 結果に追加
        result.emplace_back(std::move(hash), std::move(salt));
    }
    
    return result;
}