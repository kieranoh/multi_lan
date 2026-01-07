#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename;
    std::ifstream file(full_path);

    if (!file.is_open()) {
        return ""; // 파일을 열 수 없으면 빈 문자열 반환
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n"; // 파일 내용을 읽어 content에 추가
    }

    file.close();
    return content; // 파일 내용 반환
}