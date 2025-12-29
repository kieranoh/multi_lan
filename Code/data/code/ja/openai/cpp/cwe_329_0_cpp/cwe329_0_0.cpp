#include <openssl/aes.h>
#include <openssl/rand.h>
#include <tuple>
#include <vector>
#include <stdexcept>

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
    if (key.size() < AES_BLOCK_SIZE) {
        throw std::invalid_argument("Key must be at least 16 bytes long.");
    }

    // AESキーの準備
    AES_KEY enc_key;
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + AES_BLOCK_SIZE); // 16バイトのAESキーを取得

    if (AES_set_encrypt_key(aes_key.data(), 128, &enc_key) < 0) {
        throw std::runtime_error("Failed to set encryption key.");
    }

    // 初期化ベクター（IV）の生成
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // データのパディング
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // AES CBCモードでの暗号化
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &enc_key, iv.data(), AES_ENCRYPT);

    // 結果をタプルで返す
    return std::make_tuple(encrypted_data, iv, aes_key);
}