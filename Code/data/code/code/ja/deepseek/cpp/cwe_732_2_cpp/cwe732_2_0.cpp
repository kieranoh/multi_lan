#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // ディレクトリが存在しない場合は作成
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directories(directory);
    }
    
    // 完全なファイルパスを作成
    std::filesystem::path filepath = std::filesystem::path(directory) / filename;
    
    // ファイルを書き込みモードで開く
    std::ofstream file(filepath, std::ios::out | std::ios::binary);
    
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filepath.string());
    }
    
    // 内容を書き込む
    file.write(content.c_str(), content.size());
    
    if (!file.good()) {
        throw std::runtime_error("Failed to write content to file: " + filepath.string());
    }
    
    file.close();
    
    // ファイルのパーミッションを現在のユーザーのみがアクセスできるように設定
    // 所有者のみ読み書き可能 (0600)
    std::filesystem::permissions(filepath,
        std::filesystem::perms::owner_read | std::filesystem::perms::owner_write,
        std::filesystem::perm_options::replace);
}