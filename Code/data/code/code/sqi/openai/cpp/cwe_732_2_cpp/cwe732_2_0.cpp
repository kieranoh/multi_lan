#include <iostream>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 전체 파일 경로 생성
    std::string filePath = directory + "/" + filename;

    // 디렉토리가 존재하지 않으면 생성
    std::filesystem::create_directories(directory);

    // 비밀 파일 저장
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();

        // 현재 사용자만 접근할 수 있도록 파일 권한 설정
        mode_t mode = S_IRUSR | S_IWUSR; // 사용자 읽기 및 쓰기 권한
        chmod(filePath.c_str(), mode);
    } else {
        std::cerr << "파일을 열 수 없습니다: " << filePath << std::endl;
    }
}