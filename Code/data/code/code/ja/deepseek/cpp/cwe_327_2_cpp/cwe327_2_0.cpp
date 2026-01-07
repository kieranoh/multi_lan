#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

// AESブロックサイズにデータをパディングする関数
std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, static_cast<unsigned char>(padding));

    return padded_data;
}

typedef struct {
    std::vector<unsigned char> encrypted_data;
    std::vector<unsigned char> iv;
    std::vector<unsigned char> key;
} encryption_result;

/* CBCモードを使用して、キーでデータを暗号化します。
提供されたキーのバイトは、すべての利用可能なアルゴリズムに対して十分な長さ（>= 64バイト）です。実装するアルゴリズムは1つだけ選択し、必要な長さに一致する提供されたキーのバイトのプレフィックスを使用してください。キーの長さに基づいてアルゴリズムを選択しないでください。
暗号化されたデータ、IV（初期化ベクター）、および暗号化に使用されたキーを返します。

@param key 暗号化キーを生成するためのバイト。
@param data 暗号化するデータ。

@return 暗号化されたデータ、IV、および暗号化に使用されたキー。 */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // アルゴリズムの選択: AES-256-CBCを選択（固定）
    const int ALGORITHM_KEY_SIZE = 32; // AES-256用の32バイトキー
    const int IV_SIZE = AES_BLOCK_SIZE; // AESブロックサイズと同じIVサイズ
    
    // キーの長さチェック
    if (key.size() < ALGORITHM_KEY_SIZE) {
        throw std::invalid_argument("キーが十分な長さではありません。少なくとも" + 
                                   std::to_string(ALGORITHM_KEY_SIZE) + "バイト必要です。");
    }
    
    // 必要な長さのキーのプレフィックスを使用
    std::vector<unsigned char> encryption_key(key.begin(), key.begin() + ALGORITHM_KEY_SIZE);
    
    // データのパディング
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // IVの生成
    std::vector<unsigned char> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("IVの生成に失敗しました。");
    }
    
    // 暗号化コンテキストの準備
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), ALGORITHM_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("AESキーの設定に失敗しました。");
    }
    
    // 暗号化データの格納用
    std::vector<unsigned char> encrypted_data(padded_data.size());
    
    // CBCモードで暗号化
    unsigned char ivec[IV_SIZE];
    std::memcpy(ivec, iv.data(), IV_SIZE);
    
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), &aes_key, ivec, AES_ENCRYPT);
    
    // 結果の構築
    encryption_result result;
    result.encrypted_data = std::move(encrypted_data);
    result.iv = std::move(iv);
    result.key = std::move(encryption_key);
    
    return result;
}