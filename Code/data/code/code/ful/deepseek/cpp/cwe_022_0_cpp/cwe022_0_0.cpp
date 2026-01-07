#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    namespace fs = std::filesystem;
    
    try {
        // 경로 구성
        fs::path file_path = fs::path(dir_path) / filename;
        
        // 파일 존재 및 접근 가능 여부 확인
        std::error_code ec;
        if (!fs::exists(file_path, ec) || ec || !fs::is_regular_file(file_path, ec) || ec) {
            return "";
        }
        
        // 파일 열기
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
        content.resize(static_cast<size_t>(file_size));
        
        if (!file.read(&content[0], file_size)) {
            return "";
        }
        
        return content;
        
    } catch (...) {
        // 모든 예외를 잡아 빈 문자열 반환
        return "";
    }
}