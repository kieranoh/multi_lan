#include <string>
#include <fstream>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // 파일 경로 구성
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // 파일 존재 및 접근 가능 여부 확인
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
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());
    
    // 파일 닫기
    file.close();
    
    return content;
}