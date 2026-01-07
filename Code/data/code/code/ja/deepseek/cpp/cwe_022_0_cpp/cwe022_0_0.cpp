#include <string>
#include <fstream>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // ファイルパスを構築
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // ファイルが存在するか、通常ファイルであるかを確認
    if (!std::filesystem::exists(file_path) || !std::filesystem::is_regular_file(file_path)) {
        return "";
    }
    
    // ファイルを開く
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    // ファイルサイズを取得
    file.seekg(0, std::ios::end);
    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    // ファイルサイズが0の場合、空文字列を返す
    if (file_size <= 0) {
        return "";
    }
    
    // ファイル内容を読み込む
    std::string content;
    content.resize(file_size);
    
    if (!file.read(&content[0], file_size)) {
        return "";
    }
    
    return content;
}