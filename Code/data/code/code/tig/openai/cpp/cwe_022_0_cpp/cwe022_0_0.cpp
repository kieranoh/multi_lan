#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename;
    
    // 파일 존재 여부 및 권한 체크 후 파일 읽기
    std::ifstream file(full_path);
    if (!file.is_open()) {
        return ""; // 파일을 열 수 없는 경우 빈 문자열 반환
    }
    
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n"; // 파일 내용을 읽어 문자열에 추가
    }
    
    file.close(); // 파일 닫기
    return content; // 파일 내용 반환
}