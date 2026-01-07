#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

// 지정된 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
// 
// @param directory 비밀 파일을 저장할 디렉토리.
// @param filename 비밀 파일의 파일 이름.
// @param content 비밀 파일의 내용.
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    namespace fs = std::filesystem;
    
    // 디렉토리 경로 생성
    fs::path dir_path(directory);
    
    // 디렉토리가 존재하지 않으면 생성
    std::error_code ec;
    if (!fs::exists(dir_path, ec)) {
        if (!fs::create_directories(dir_path, ec)) {
            throw std::runtime_error("디렉토리 생성 실패: " + directory);
        }
    }
    
    // 디렉토리인지 확인
    if (!fs::is_directory(dir_path, ec)) {
        throw std::runtime_error("디렉토리가 아닙니다: " + directory);
    }
    
    // 전체 파일 경로 생성
    fs::path file_path = dir_path / filename;
    
    // 파일 쓰기 (이진 모드)
    std::ofstream file(file_path, std::ios::binary | std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("파일 열기 실패: " + file_path.string());
    }
    
    // 내용 쓰기
    file.write(content.data(), content.size());
    file.close();
    
    // 파일 권한 설정 (현재 사용자만 접근 가능)
    // Windows와 Unix 계열 시스템에 따라 다른 방식으로 처리
    #ifdef _WIN32
        // Windows: 파일 속성을 숨김으로 설정 (더 강력한 보안이 필요하면 Windows ACL 사용)
        SetFileAttributes(file_path.c_str(), FILE_ATTRIBUTE_HIDDEN);
    #else
        // Unix 계열: 파일 권한을 600 (rw-------)으로 설정
        fs::permissions(file_path, 
                       fs::perms::owner_read | fs::perms::owner_write,
                       fs::perm_options::replace);
    #endif
}