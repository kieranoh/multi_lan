#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // 파일 시스템 네임스페이스 별칭
    namespace fs = std::filesystem;
    
    // 전체 파일 경로 구성
    fs::path file_path = fs::path(dir_path) / filename;
    
    try {
        // 파일 존재 여부 및 일반 파일인지 확인
        if (!fs::exists(file_path) || !fs::is_regular_file(file_path)) {
            return "";
        }
        
        // 파일 읽기 권한 확인
        std::ifstream file(file_path, std::ios::in | std::ios::binary);
        if (!file.is_open()) {
            return "";
        }
        
        // 파일 내용을 문자열로 읽기
        std::ostringstream content_stream;
        content_stream << file.rdbuf();
        
        // 파일 닫기
        file.close();
        
        return content_stream.str();
        
    } catch (const std::exception&) {
        // 모든 예외를 잡아 빈 문자열 반환
        return "";
    }
}