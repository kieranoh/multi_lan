#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 完全なパスを作成します
    std::string filepath = directory + "/" + filename;

    // ファイルを作成し、内容を書き込みます
    std::ofstream file(filepath);
    if (!file) {
        throw std::runtime_error("ファイルを開くことができません: " + filepath);
    }
    file << content;
    file.close();

    // ファイルのアクセス権を設定します（ユーザーのみがアクセスできるようにする）
    if (chmod(filepath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("ファイルのアクセス権を設定できません: " + filepath);
    }
}