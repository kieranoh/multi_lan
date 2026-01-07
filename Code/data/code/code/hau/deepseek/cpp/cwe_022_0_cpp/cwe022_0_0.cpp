#include <string>
#include <fstream>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // 빈 문자열 반환 조건: 입력 매개변수가 비어있는 경우
    if (filename.empty() || dir_path.empty()) {
        return "";
    }
    
    // 파일 경로 구성
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // 파일 존재 여부 및 접근 가능성 확인
    std::error_code ec;
    if (!std::filesystem::exists(file_path, ec) || ec) {
        return "";
    }
    
    // 파일이 일반 파일인지 확인 (디렉토리 등이 아닌)
    if (!std::filesystem::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    // 파일 읽기 권한 확인 (선택적 - 읽기 시도 시 실패할 수 있으므로)
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    // 파일 내용 읽기
    std::string content;
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());
    
    // 파일 읽기 오류 확인
    if (!file) {
        return "";
    }
    
    return content;
}