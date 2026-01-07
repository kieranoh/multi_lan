#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;

    std::ifstream file(file_path);
    if (!file.is_open()) {
        return ""; // 파일을 찾을 수 없거나 접근할 수 없음
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
    
    return content;
}