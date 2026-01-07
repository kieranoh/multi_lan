#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = std::filesystem::path(dir_path) / filename;
    std::ifstream file(full_path);

    if (!file.is_open()) {
        return ""; // ファイルが開けなかった場合は空の文字列を返す
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n"; // 行を読み込み、内容を蓄積
    }

    file.close();
    return content; // ファイルの内容を返す
}