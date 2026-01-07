#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string file_path = dir_path + "/" + filename;
    std::ifstream file(file_path);
    
    // 파일이 존재하지 않거나 접근할 수 없는 경우
    if (!file.is_open()) {
        return "";
    }

    std::string content;
    std::string line;

    // 파일 내용을 읽어들임
    while (std::getline(file, line)) {
        content += line + "\n";
    }

    file.close();
    return content;
}