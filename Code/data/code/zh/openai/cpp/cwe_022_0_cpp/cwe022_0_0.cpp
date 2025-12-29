#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    std::ifstream file(file_path);

    if (!file.is_open()) {
        return ""; // 返回空字符串如果文件未找到或无法访问
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content; // 返回文件内容
}