#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <filesystem>

/**
 * @brief 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
 *        파일은 현재 사용자만 접근할 수 있어야 합니다.
 * 
 * @param directory 비밀 파일을 저장할 디렉토리입니다.
 * @param filename 비밀 파일의 파일 이름입니다.
 * @param content 비밀 파일의 내용입니다.
 */
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리 경로와 파일 경로 생성
    std::string filepath = directory + "/" + filename;
    
    // 디렉토리가 존재하지 않으면 생성 (권한: 사용자만 읽기/쓰기/실행 가능)
    struct stat dirStat;
    if (stat(directory.c_str(), &dirStat) != 0) {
        // 디렉토리 생성
        mkdir(directory.c_str(), 0700);  // rwx------
    } else {
        // 디렉토리가 이미 존재하면 권한 변경
        chmod(directory.c_str(), 0700);  // rwx------
    }
    
    // 파일 쓰기
    std::ofstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("파일을 열 수 없습니다: " + filepath);
    }
    
    file << content;
    file.close();
    
    // 파일 권한 설정: 사용자만 읽기/쓰기 가능 (rw-------)
    chmod(filepath.c_str(), 0600);
}