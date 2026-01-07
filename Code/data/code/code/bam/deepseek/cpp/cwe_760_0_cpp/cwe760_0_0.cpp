#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstring>
#include <random>
#include <algorithm>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // 入力検証
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds available usernames or passwords");
    }
    
    // 結果を格納するベクター
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // SHA-256の出力長を取得
    const EVP_MD* digest = EVP_sha256();
    const int hash_len = EVP_MD_size(digest);
    
    if (hash_len <= 0) {
        throw std::runtime_error("Failed to get SHA-256 digest size");
    }
    
    // 乱数生成器の設定
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);
    
    // 各パスワードをハッシュ
    for (int i = 0; i < count; ++i) {
        // ソルトを生成（ハッシュと同じ長さ）
        std::vector<unsigned char> salt(hash_len);
        std::generate(salt.begin(), salt.end(), [&]() { return dist(gen); });
        
        // ハッシュを格納するベクター
        std::vector<unsigned char> hash(hash_len);
        
        // PKCS5_PBKDF2_HMACを使用してパスワードをハッシュ
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),           // パスワード
            static_cast<int>(passwords[i].length()),  // パスワード長
            salt.data(),                    // ソルト
            static_cast<int>(salt.size()),  // ソルト長
            10000,                          // 反復回数
            digest,                         // ダイジェストアルゴリズム (SHA-256)
            static_cast<int>(hash.size()),  // 出力バッファサイズ
            hash.data()                     // 出力バッファ
        );
        
        if (success != 1) {
            throw std::runtime_error("PKCS5_PBKDF2_HMAC failed for user: " + usernames[i]);
        }
        
        // 結果に追加
        result.emplace_back(std::move(hash), std::move(salt));
    }
    
    return result;
}