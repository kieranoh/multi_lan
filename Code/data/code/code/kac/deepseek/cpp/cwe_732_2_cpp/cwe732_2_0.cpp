#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리 경로와 파일 경로 생성
    std::filesystem::path dirPath(directory);
    std::filesystem::path filePath = dirPath / filename;
    
    // 디렉토리가 존재하지 않으면 생성
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
    }
    
    // 파일 쓰기
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("파일을 열 수 없습니다: " + filePath.string());
    }
    
    file.write(content.data(), content.size());
    file.close();
    
    // 파일 권한 설정: 현재 사용자만 읽기/쓰기 가능 (600)
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("파일 권한 설정에 실패했습니다: " + filePath.string());
    }
    
    // 디렉토리 권한 설정: 현재 사용자만 접근 가능 (700)
    if (chmod(dirPath.c_str(), S_IRWXU) != 0) {
        throw std::runtime_error("디렉토리 권한 설정에 실패했습니다: " + dirPath.string());
    }
}