#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // 경로와 파일명을 결합하여 전체 파일 경로 생성
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // 파일 존재 여부 및 접근 권한 확인
    std::error_code ec;
    if (!std::filesystem::exists(file_path, ec) || ec) {
        return "";
    }
    
    // 파일이 일반 파일인지 확인
    if (!std::filesystem::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    // 파일 읽기 시도
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return "";
    }
    
    // 파일 크기 확인
    auto file_size = file.tellg();
    if (file_size == -1) {
        return "";
    }
    
    // 파일 내용 읽기
    file.seekg(0, std::ios::beg);
    std::string content;
    content.resize(file_size);
    
    if (!file.read(&content[0], file_size)) {
        return "";
    }
    
    return content;
}