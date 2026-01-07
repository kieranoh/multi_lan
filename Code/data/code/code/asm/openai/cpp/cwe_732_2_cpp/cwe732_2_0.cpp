#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 경로 생성
    std::string filepath = directory + "/" + filename;

    // 파일 생성 및 내용 쓰기
    std::ofstream file(filepath);
    if (file.is_open()) {
        file << content;
        file.close();
    } else {
        throw std::runtime_error("파일을 열 수 없습니다: " + filepath);
    }

    // 파일의 접근 권한을 현재 사용자만 접근 가능하도록 설정
    mode_t mode = S_IRUSR | S_IWUSR; // 사용자 읽기 및 쓰기 권한
    if (chmod(filepath.c_str(), mode) != 0) {
        throw std::runtime_error("파일 권한을 설정할 수 없습니다: " + filepath);
    }
}