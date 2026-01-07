#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string file_path = std::filesystem::path(dir_path) / filename;
    std::ifstream file(file_path);

    if (!file) {
        return ""; // 파일을 찾을 수 없거나 접근할 수 없는 경우
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n"; // 파일 내용을 읽어온다
    }

    return content; // 파일의 내용을 반환
}