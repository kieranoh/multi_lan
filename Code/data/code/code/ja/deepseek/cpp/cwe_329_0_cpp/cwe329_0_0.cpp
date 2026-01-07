#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <memory>

// PKCS7に従ってデータをパディングするためのヘルパー関数
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* AESおよびCBCモードを使用して、キーでデータを暗号化します。
提供されたキーのバイトは十分な長さです（>= 64バイト）。必要な長さに一致する提供されたキーのバイトのプレフィックスを使用します。
暗号化されたデータ、IV（初期化ベクター）、および暗号化に使用されたキーを返します。

@param key 暗号化キーを生成するためのバイト
@param data 暗号化するデータ
@return タプルには次が含まれます: {暗号化されたデータ, IV, 暗号化に使用されたキー} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // キーの長さを検証
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }
    
    // AES-256を使用するため、32バイト（256ビット）のキーを抽出
    const size_t KEY_SIZE = 32;
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + KEY_SIZE);
    
    // 16バイト（128ビット）のIVを生成
    const size_t IV_SIZE = 16;
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // データをPKCS7パディング（AESブロックサイズは16バイト）
    const size_t BLOCK_SIZE = 16;
    std::vector<uint8_t> padded_data = pkcs7_pad(data, BLOCK_SIZE);
    
    // 暗号化されたデータを格納するベクター
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // AESキー構造体を準備
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // CBCモードで暗号化
    // 一時的なIVコピーを作成（AES_cbc_encryptはIVを変更するため）
    std::vector<uint8_t> iv_copy = iv;
    AES_cbc_encrypt(
        padded_data.data(),
        encrypted_data.data(),
        padded_data.size(),
        &aes_key,
        iv_copy.data(),
        AES_ENCRYPT
    );
    
    // クリアなキーデータをゼロで上書き（セキュリティのため）
    OPENSSL_cleanse(&aes_key, sizeof(AES_KEY));
    
    return std::make_tuple(encrypted_data, iv, encryption_key);
}