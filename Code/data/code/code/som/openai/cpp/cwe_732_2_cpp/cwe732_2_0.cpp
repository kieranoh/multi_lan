#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    std::string fullPath = directory + "/" + filename;

    // 파일 저장
    std::ofstream outFile(fullPath);
    if (!outFile) {
        throw std::runtime_error("파일을 열 수 없습니다: " + fullPath);
    }
    
    outFile << content;
    outFile.close();

    // 파일 접근 권한 설정 (현재 사용자만 접근 가능하도록 설정)
    chmod(fullPath.c_str(), S_IRUSR | S_IWUSR);
}