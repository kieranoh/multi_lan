#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리 경로와 파일 경로 생성
    std::filesystem::path dir_path(directory);
    std::filesystem::path file_path = dir_path / filename;
    
    // 디렉토리가 존재하지 않으면 생성 (권한 0700: 사용자만 읽기/쓰기/실행 가능)
    if (!std::filesystem::exists(dir_path)) {
        std::filesystem::create_directories(dir_path);
        chmod(dir_path.c_str(), 0700);
    }
    
    // 파일 쓰기
    std::ofstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("파일을 열 수 없습니다: " + file_path.string());
    }
    
    file.write(content.c_str(), content.size());
    file.close();
    
    // 파일 권한 설정 (0600: 사용자만 읽기/쓰기 가능)
    chmod(file_path.c_str(), 0600);
}