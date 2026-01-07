#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 경로 설정
    std::filesystem::path dirPath(directory);
    std::filesystem::path filePath = dirPath / filename;

    // 디렉토리 존재 여부 확인
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
    }

    // 비밀 파일 저장
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();

        // 파일의 접근 권한을 현재 사용자만 접근할 수 있도록 설정
        uid_t userId = getuid();
        gid_t groupId = getgid();

        // 파일 권한을 설정
        chmod(filePath.c_str(), S_IRUSR | S_IWUSR); // 사용자만 읽기 및 쓰기 가능

        std::cout << "비밀 파일이 저장되었습니다: " << filePath << std::endl;
    } else {
        std::cerr << "파일을 열 수 없습니다: " << filePath << std::endl;
    }
}