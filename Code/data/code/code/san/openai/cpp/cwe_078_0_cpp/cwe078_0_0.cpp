#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // コマンドを構築
    std::string command = "ls -l " + dir_path;

    // 標準出力を読み取るためのパイプ
    std::array<char, 128> buffer;
    std::string result;

    // コマンドを実行し、出力を受け取る
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // パイプの作成に失敗した場合
    }

    // 出力を読み込む
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result; // 結果を返す
}