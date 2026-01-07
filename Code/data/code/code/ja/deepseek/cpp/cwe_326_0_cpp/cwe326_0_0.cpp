#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    // デフォルトのキー長を2048ビットに設定
    const int key_length = 2048;
    
    // コマンドを構築
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // コマンドを実行するためのバッファ
    std::array<char, 128> buffer;
    std::string result;
    
    // パイプを開いてコマンドを実行
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // パイプのオープンに失敗した場合
        return "";
    }
    
    // コマンドの出力を読み取る
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 結果が空の場合はエラーとして空文字列を返す
    if (result.empty()) {
        return "";
    }
    
    return result;
}