#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // 빈 입력 처리
    if (filename.empty() || dir_path.empty()) {
        return "";
    }
    
    // 파일 경로 구성
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // 파일 존재 및 접근 가능 여부 확인
    std::error_code ec;
    if (!std::filesystem::exists(file_path, ec) || ec) {
        return "";
    }
    
    if (!std::filesystem::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    // 파일 읽기 권한 확인 (읽기 시도로 대체)
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    // 파일 내용 읽기
    std::string content;
    try {
        // 파일 크기 확인
        auto file_size = std::filesystem::file_size(file_path, ec);
        if (!ec && file_size > 0) {
            content.resize(file_size);
            file.read(&content[0], file_size);
            
            // 실제 읽은 바이트 수 확인
            if (file.gcount() != static_cast<std::streamsize>(file_size)) {
                return "";
            }
        }
        // 파일 크기가 0이어도 빈 문자열 반환 (오류 아님)
    } catch (...) {
        // 파일 읽기 중 예외 발생
        return "";
    }
    
    return content;
}