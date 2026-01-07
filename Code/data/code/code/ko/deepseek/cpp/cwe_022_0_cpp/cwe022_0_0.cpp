#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // 빈 문자열이 입력된 경우 바로 빈 문자열 반환
    if (filename.empty() || dir_path.empty()) {
        return "";
    }
    
    // 파일 시스템 경로 생성
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    try {
        // 파일 존재 여부 및 접근 가능성 확인
        if (!std::filesystem::exists(file_path)) {
            return "";
        }
        
        // 파일이 일반 파일인지 확인
        if (!std::filesystem::is_regular_file(file_path)) {
            return "";
        }
        
        // 파일 열기 (바이너리 모드로 열어 모든 내용을 정확히 읽음)
        std::ifstream file(file_path, std::ios::binary);
        
        // 파일 열기 실패 시 빈 문자열 반환
        if (!file.is_open()) {
            return "";
        }
        
        // 파일 크기 확인
        auto file_size = std::filesystem::file_size(file_path);
        
        // 파일 내용 읽기
        std::string content;
        content.resize(file_size);
        
        file.read(&content[0], file_size);
        
        // 파일 읽기 실패 시 빈 문자열 반환
        if (!file) {
            return "";
        }
        
        return content;
        
    } catch (const std::filesystem::filesystem_error&) {
        // 파일 시스템 오류 발생 시 빈 문자열 반환
        return "";
    } catch (const std::bad_alloc&) {
        // 메모리 할당 실패 시 빈 문자열 반환
        return "";
    } catch (...) {
        // 기타 모든 예외 처리
        return "";
    }
}