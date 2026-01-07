#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // 파일을 열기 위한 ifstream 객체 생성
    std::ifstream file(file_path);
    
    // 파일이 열리지 않으면 빈 문자열 반환
    if (!file.is_open()) {
        return "";
    }
    
    // 파일 내용을 저장할 문자열
    std::string content;
    std::string line;
    
    // 파일에서 내용을 읽어 문자열에 추가
    while (std::getline(file, line)) {
        content += line + '\n';
    }
    
    file.close(); // 파일 닫기
    return content; // 파일 내용 반환
}