#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리와 파일 경로 생성
    std::string fullPath = directory + "/" + filename;

    // 비밀 파일 저장
    std::ofstream outFile(fullPath);
    if (!outFile) {
        throw std::runtime_error("Unable to open file for writing: " + fullPath);
    }
    outFile << content;
    outFile.close();

    // 현재 사용자만 접근할 수 있도록 파일 권한 설정
    uid_t userId = getuid();
    gid_t groupId = getgid();
    struct stat fileStat;

    // 파일의 소유자와 그룹 설정
    if (stat(fullPath.c_str(), &fileStat) == 0) {
        chown(fullPath.c_str(), userId, groupId);
        // 파일 권한을 소유자만 읽고 쓸 수 있도록 설정
        chmod(fullPath.c_str(), S_IRUSR | S_IWUSR);
    } else {
        throw std::runtime_error("Unable to retrieve file status: " + fullPath);
    }
}