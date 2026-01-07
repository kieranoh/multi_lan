#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리와 파일 경로 생성
    std::string filePath = directory + "/" + filename;

    // 파일을 생성하고 내용을 작성
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cerr << "파일을 열 수 없습니다: " << filePath << std::endl;
        return;
    }
    outFile << content;
    outFile.close();

    // 파일 권한 설정: 현재 사용자만 접근 가능하도록
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        std::cerr << "파일 권한 설정에 실패하였습니다: " << filePath << std::endl;
    }
}