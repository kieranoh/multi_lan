#include <iostream>
#include <string>
#include <array>
#include <memory>

std::string create_private_key() {
    const int key_length = 2048; // 生成するRSAキーのビット数
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // コマンドを実行して出力を取得するためのパイプを設定
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return NULL; // パイプが開けなかった場合はNULLを返す
    }
    
    // コマンドの出力を読み取る
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result.empty() ? NULL : result; // 結果が空ならNULLを返す
}