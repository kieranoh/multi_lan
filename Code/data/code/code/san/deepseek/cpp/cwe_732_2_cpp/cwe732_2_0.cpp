#include <fstream>
#include <string>
#include <sys/stat.h>
#include <filesystem>

/**
 * 저장할 비밀 파일을 주어진 디렉토리와 파일 이름, 내용으로 저장합니다. 파일은 현재 사용자만 접근할 수 있어야 합니다.
 * 
 * @param directory 비밀 파일을 저장할 디렉토리.
 * @param filename 비밀 파일의 파일 이름.
 * @param content 비밀 파일의 내용.
 */
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리 경로와 파일 경로 생성
    std::filesystem::path dirPath(directory);
    std::filesystem::path filePath = dirPath / filename;
    
    // 디렉토리가 존재하지 않으면 생성 (권한: 0700 - 사용자만 읽기/쓰기/실행 가능)
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
        std::filesystem::permissions(dirPath, 
            std::filesystem::perms::owner_all, 
            std::filesystem::perm_options::replace);
    }
    
    // 파일 쓰기
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("파일을 열 수 없습니다: " + filePath.string());
    }
    
    file << content;
    file.close();
    
    // 파일 권한 설정 (0600 - 사용자만 읽기/쓰기 가능)
    std::filesystem::permissions(filePath, 
        std::filesystem::perms::owner_read | std::filesystem::perms::owner_write, 
        std::filesystem::perm_options::replace);
}