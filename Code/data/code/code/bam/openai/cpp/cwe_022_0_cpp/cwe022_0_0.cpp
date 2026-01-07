#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename;
    std::ifstream file(full_path);
    
    if (!file) {
        return ""; // 파일을 찾을 수 없거나 열 수 없는 경우 빈 문자열 반환
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n"; // 파일 내용을 읽어와서 content에 추가
    }

    file.close();
    return content; // 파일의 내용을 반환
}