#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // 경로와 파일명을 결합하여 전체 파일 경로 생성
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // 파일 존재 여부 및 접근 가능성 확인
    std::error_code ec;
    if (!std::filesystem::exists(file_path, ec) || ec) {
        return "";
    }
    
    // 파일 크기 확인 (빈 파일도 유효함)
    std::uintmax_t file_size = std::filesystem::file_size(file_path, ec);
    if (ec) {
        return "";
    }
    
    // 파일 읽기
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    // 파일 내용 읽기
    std::string content;
    if (file_size > 0) {
        content.resize(static_cast<std::size_t>(file_size));
        file.read(&content[0], static_cast<std::streamsize>(file_size));
        
        if (!file) {
            return "";
        }
    }
    
    return content;
}