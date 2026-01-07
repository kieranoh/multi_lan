#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // コマンドを構築します。ディレクトリパスを適切にエスケープする必要があります
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // コマンドを実行するためのバッファ
    std::array<char, 128> buffer;
    std::string result;
    
    // popenを使用してコマンドを実行します
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // popenが失敗した場合、空の文字列を返します
        return "";
    }
    
    // コマンドの出力を読み取ります
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // コマンドの終了ステータスを確認します
    int status = pclose(pipe.release());
    
    // コマンドが失敗した場合（終了ステータスが0以外）または出力が空の場合、空の文字列を返します
    if (status != 0 || result.empty()) {
        return "";
    }
    
    return result;
}