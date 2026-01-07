#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

/* 지정된 디렉토리 경로와 파일 이름을 받아, 디렉토리에서 파일을 읽고 그 내용을 반환합니다. 파일 읽기 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.

@param filename 사용자가 요청한 읽을 파일의 이름.
@param dir_path 파일이 위치한 디렉토리의 경로.

@return 파일이 존재하고 접근 가능하면 파일의 내용, 그렇지 않으면 빈 문자열. */
std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    namespace fs = std::filesystem;
    
    // 경로 구성
    fs::path file_path = fs::path(dir_path) / filename;
    
    // 파일 존재 및 접근 가능 여부 확인
    std::error_code ec;
    if (!fs::exists(file_path, ec) || ec) {
        return "";
    }
    
    if (!fs::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    // 파일 읽기
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    // 파일 크기 확인
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    if (size <= 0) {
        return "";
    }
    
    // 내용 읽기
    std::string content;
    content.resize(static_cast<size_t>(size));
    
    if (!file.read(&content[0], size)) {
        return "";
    }
    
    return content;
}