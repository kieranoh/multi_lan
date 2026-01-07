#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리 경로 생성
    std::filesystem::path dir_path(directory);
    
    // 디렉토리가 존재하지 않으면 생성
    if (!std::filesystem::exists(dir_path)) {
        std::filesystem::create_directories(dir_path);
    }
    
    // 파일 전체 경로 생성
    std::filesystem::path file_path = dir_path / filename;
    
    // 파일 열기 (쓰기 모드, 이진 모드)
    std::ofstream file(file_path, std::ios::out | std::ios::binary);
    
    if (!file.is_open()) {
        throw std::runtime_error("파일을 열 수 없습니다: " + file_path.string());
    }
    
    // 내용 쓰기
    file.write(content.c_str(), content.size());
    file.close();
    
    // 파일 권한 설정: 현재 사용자만 읽기/쓰기 가능 (600)
    if (chmod(file_path.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("파일 권한 설정에 실패했습니다.");
    }
    
    // 디렉토리 권한 설정: 현재 사용자만 접근 가능 (700)
    if (chmod(dir_path.c_str(), S_IRUSR | S_IWUSR | S_IXUSR) != 0) {
        throw std::runtime_error("디렉토리 권한 설정에 실패했습니다.");
    }
}