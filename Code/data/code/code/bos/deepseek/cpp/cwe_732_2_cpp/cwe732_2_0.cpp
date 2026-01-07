#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

// 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
// 
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    namespace fs = std::filesystem;
    
    // 디렉토리 경로 생성
    fs::path dir_path(directory);
    
    // 디렉토리가 존재하지 않으면 생성
    std::error_code ec;
    if (!fs::exists(dir_path, ec)) {
        if (!fs::create_directories(dir_path, ec)) {
            throw std::runtime_error("Failed to create directory: " + directory);
        }
    }
    
    // 전체 파일 경로 생성
    fs::path file_path = dir_path / filename;
    
    // 파일 열기 (이진 모드로 쓰기)
    std::ofstream file(file_path, std::ios::binary | std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path.string());
    }
    
    // 내용 쓰기
    file.write(content.data(), content.size());
    file.close();
    
    // 파일 권한 설정: 현재 사용자만 읽기/쓰기 가능 (600)
    fs::permissions(file_path,
                   fs::perms::owner_read | fs::perms::owner_write,
                   fs::perm_options::replace);
}