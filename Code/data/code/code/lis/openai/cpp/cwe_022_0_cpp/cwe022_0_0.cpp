#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename;
    std::ifstream file(full_path);
    
    if (!file.is_open()) {
        return ""; // 파일을 찾을 수 없거나, 권한 오류가 발생한 경우
    }
    
    std::string content;
    std::string line;

    while (std::getline(file, line)) {
        content += line + "\n";
    }

    file.close();
    return content; // 파일의 내용을 반환
}