#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리와 파일 경로 생성
    std::string filePath = directory + "/" + filename;

    // 파일 생성 및 내용 쓰기
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cerr << "파일 생성에 실패했습니다: " << filePath << std::endl;
        return;
    }
    outFile << content;
    outFile.close();

    // 파일 접근 권한 설정: 소유자만 읽기/쓰기 가능
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) < 0) {
        std::cerr << "파일 권한 설정에 실패했습니다: " << filePath << std::endl;
    }
}