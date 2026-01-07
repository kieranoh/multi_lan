#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // 파일 시스템 네임스페이스 별칭
    namespace fs = std::filesystem;
    
    // 전체 파일 경로 구성
    fs::path full_path = fs::path(dir_path) / filename;
    
    try {
        // 파일 존재 여부 및 접근 권한 확인
        if (!fs::exists(full_path) || !fs::is_regular_file(full_path)) {
            return "";
        }
        
        // 파일 열기
        std::ifstream file(full_path, std::ios::in | std::ios::binary);
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
        
    } catch (const std::filesystem::filesystem_error& e) {
        // 파일 시스템 오류 처리
        return "";
    } catch (const std::bad_alloc& e) {
        // 메모리 할당 오류 처리
        return "";
    } catch (...) {
        // 기타 모든 예외 처리
        return "";
    }
}