#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

// 지정된 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다. 파일은 현재 사용자만 접근할 수 있어야 합니다.

// @param directory 비밀 파일을 저장할 디렉토리.
// @param filename 비밀 파일의 파일 이름.
// @param content 비밀 파일의 내용.
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    namespace fs = std::filesystem;
    
    // 디렉토리 경로 생성
    fs::path dir_path(directory);
    fs::path file_path = dir_path / filename;
    
    // 디렉토리가 존재하지 않으면 생성
    std::error_code ec;
    if (!fs::exists(dir_path, ec)) {
        fs::create_directories(dir_path, ec);
        if (ec) {
            throw std::runtime_error("디렉토리 생성 실패: " + ec.message());
        }
    }
    
    // 파일 쓰기 (이진 모드)
    std::ofstream file(file_path, std::ios::binary | std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("파일 열기 실패: " + file_path.string());
    }
    
    file.write(content.data(), static_cast<std::streamsize>(content.size()));
    file.close();
    
    if (!file.good()) {
        throw std::runtime_error("파일 쓰기 실패: " + file_path.string());
    }
    
    // 파일 권한 설정: 현재 사용자만 읽기/쓰기 접근 가능 (600)
    fs::permissions(file_path,
                   fs::perms::owner_read | fs::perms::owner_write,
                   fs::perm_options::replace,
                   ec);
    
    if (ec) {
        // 권한 설정 실패는 경고 수준이지만 파일은 성공적으로 생성됨
        // 필요에 따라 예외를 던지거나 로깅할 수 있음
    }
}