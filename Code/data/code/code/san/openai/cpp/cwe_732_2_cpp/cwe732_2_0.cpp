#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리가 존재하지 않으면 생성합니다.
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directories(directory);
    }

    // 비밀 파일의 전체 경로를 생성합니다.
    std::string filePath = directory + "/" + filename;

    // 파일을 엽니다.
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        // 파일에 내용을 씁니다.
        outFile << content;
        outFile.close();

        // 현재 사용자만 접근할 수 있도록 파일 권한을 설정합니다.
        chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
    } else {
        std::cerr << "파일을 열 수 없습니다: " << filePath << std::endl;
    }
}