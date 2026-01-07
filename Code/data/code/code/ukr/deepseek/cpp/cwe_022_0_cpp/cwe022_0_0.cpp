#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // 빈 문자열 반환 조건: filename이나 dir_path가 비어있는 경우
    if (filename.empty() || dir_path.empty()) {
        return "";
    }
    
    // 파일 시스템 경로 생성
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // 파일 존재 여부 및 접근 가능성 확인
    std::error_code ec;
    if (!std::filesystem::exists(file_path, ec) || ec) {
        return "";
    }
    
    // 파일이 일반 파일인지 확인
    if (!std::filesystem::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    // 파일 읽기 권한 확인
    std::filesystem::file_status status = std::filesystem::status(file_path, ec);
    if (ec || (status.permissions() & std::filesystem::perms::owner_read) == std::filesystem::perms::none) {
        return "";
    }
    
    // 파일 열기 및 내용 읽기
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    // 파일 크기 확인
    file.seekg(0, std::ios::end);
    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    if (file_size <= 0) {
        file.close();
        return "";
    }
    
    // 파일 내용 읽기
    std::string content;
    content.resize(file_size);
    
    if (!file.read(&content[0], file_size)) {
        file.close();
        return "";
    }
    
    file.close();
    return content;
}