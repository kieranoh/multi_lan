#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    namespace fs = std::filesystem;
    
    try {
        // 디렉토리 경로와 파일 이름을 결합하여 전체 경로 생성
        fs::path file_path = fs::path(dir_path) / filename;
        
        // 파일이 존재하고 일반 파일인지 확인
        if (!fs::exists(file_path) || !fs::is_regular_file(file_path)) {
            return "";
        }
        
        // 파일 열기
        std::ifstream file(file_path, std::ios::in | std::ios::binary);
        if (!file.is_open()) {
            return "";
        }
        
        // 파일 크기 확인
        auto file_size = fs::file_size(file_path);
        if (file_size == 0) {
            return "";
        }
        
        // 파일 내용 읽기
        std::string content;
        content.resize(file_size);
        
        file.read(&content[0], file_size);
        
        // 읽기 오류 확인
        if (!file) {
            return "";
        }
        
        return content;
    }
    catch (const std::filesystem::filesystem_error&) {
        // 파일 시스템 오류 (권한 문제 등)
        return "";
    }
    catch (const std::system_error&) {
        // 시스템 오류
        return "";
    }
    catch (...) {
        // 기타 모든 예외
        return "";
    }
}