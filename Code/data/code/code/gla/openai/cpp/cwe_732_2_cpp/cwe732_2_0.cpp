#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리와 파일 경로 생성
    std::string filePath = directory + "/" + filename;
    
    // 파일 저장
    std::ofstream outFile(filePath);
    if (outFile) {
        outFile << content;
        outFile.close();

        // 파일 권한 설정: 소유자에게만 읽기, 쓰기 권한 부여
        chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
    } else {
        std::cerr << "파일을 저장할 수 없습니다: " << filePath << std::endl;
    }
}