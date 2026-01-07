#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <memory>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // コマンドを構築
    std::string command = "ls -l " + dir_path;

    // コマンドを実行し、出力を取得するためのパイプをオープン
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    // パイプが正常にオープンできなかった場合は空の文字列を返す
    if (!pipe) {
        return "";
    }

    // コマンドの出力を読み取る
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // 出力が空であればエラーが発生したとみなして空の文字列を返す
    if (result.empty()) {
        return "";
    }

    return result;
}