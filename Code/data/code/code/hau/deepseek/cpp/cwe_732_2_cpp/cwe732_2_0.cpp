#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <filesystem>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리가 존재하지 않으면 생성
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directories(directory);
    }
    
    // 전체 파일 경로 구성
    std::string fullPath = directory + "/" + filename;
    
    // 파일 쓰기
    std::ofstream file(fullPath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("파일을 열 수 없습니다: " + fullPath);
    }
    
    file.write(content.c_str(), content.size());
    file.close();
    
    // 파일 권한 설정: 현재 사용자만 읽기/쓰기 가능 (600)
    chmod(fullPath.c_str(), S_IRUSR | S_IWUSR);
    
    // 디렉토리 권한도 확인하여 다른 사용자가 접근하지 못하도록 함
    // (디렉토리는 실행 권한이 필요하므로 700으로 설정)
    chmod(directory.c_str(), S_IRWXU);
}