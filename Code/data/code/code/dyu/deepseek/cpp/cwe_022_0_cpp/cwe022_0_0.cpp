#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    namespace fs = std::filesystem;
    
    try {
        // 디렉토리 경로와 파일 이름을 결합하여 전체 경로 생성
        fs::path file_path = fs::path(dir_path) / filename;
        
        // 파일 존재 여부 및 접근 권한 확인
        if (!fs::exists(file_path) || !fs::is_regular_file(file_path)) {
            return "";
        }
        
        // 파일 열기
        std::ifstream file(file_path, std::ios::in | std::ios::binary);
        if (!file.is_open()) {
            return "";
        }
        
        // 파일 크기 확인
        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        // 파일 내용 읽기
        std::string content;
        content.resize(size);
        
        if (!file.read(&content[0], size)) {
            return "";
        }
        
        return content;
    }
    catch (const std::exception&) {
        // 모든 예외를 잡아 빈 문자열 반환
        return "";
    }
}