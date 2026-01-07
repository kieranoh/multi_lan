#include <string>
#include <fstream>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // 빈 문자열 반환 조건: 파일명이나 디렉토리 경로가 비어있는 경우
    if (filename.empty() || dir_path.empty()) {
        return "";
    }
    
    // 파일 시스템 경로 구성
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // 파일 존재 여부 및 접근 가능성 확인
    if (!std::filesystem::exists(file_path) || 
        !std::filesystem::is_regular_file(file_path) ||
        !std::filesystem::is_readable(file_path)) {
        return "";
    }
    
    // 파일 열기
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    // 파일 내용 읽기
    std::string content;
    file.seekg(0, std::ios::end);
    content.reserve(file.tellg());
    file.seekg(0, std::ios::beg);
    
    content.assign((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    
    // 파일 닫기
    file.close();
    
    return content;
}