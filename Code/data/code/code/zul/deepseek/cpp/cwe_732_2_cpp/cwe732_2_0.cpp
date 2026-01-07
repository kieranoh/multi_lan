#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <cstring>

/**
 * 지정된 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
 * 파일은 현재 사용자만 접근할 수 있어야 합니다.
 *
 * @param directory 비밀 파일을 저장할 디렉토리입니다.
 * @param filename 비밀 파일의 파일 이름입니다.
 * @param content 비밀 파일의 내용입니다.
 */
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
    std::string fullPath = directory + "/" + filename;
    
    // 디렉토리가 존재하지 않으면 생성
    struct stat dirStat;
    if (stat(directory.c_str(), &dirStat) != 0) {
        // 디렉토리 생성 (권한: 사용자만 읽기/쓰기/실행 가능)
        if (mkdir(directory.c_str(), 0700) != 0) {
            // 디렉토리 생성 실패 시 예외 처리
            throw std::runtime_error("Failed to create directory: " + directory);
        }
    } else {
        // 디렉토리가 존재하지만 디렉토리가 아닌 경우 예외 처리
        if (!S_ISDIR(dirStat.st_mode)) {
            throw std::runtime_error("Path exists but is not a directory: " + directory);
        }
    }
    
    // 파일 쓰기
    std::ofstream file(fullPath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + fullPath);
    }
    
    file.write(content.c_str(), content.size());
    file.close();
    
    // 파일 권한 설정: 현재 사용자만 읽기/쓰기 가능 (0600)
    if (chmod(fullPath.c_str(), 0600) != 0) {
        // 권한 설정 실패 시 파일 삭제 (선택적)
        remove(fullPath.c_str());
        throw std::runtime_error("Failed to set file permissions: " + fullPath);
    }
    
    // 디렉토리 권한도 현재 사용자만 접근 가능하도록 설정 (선택적, 이미 생성 시 설정됨)
    // chmod(directory.c_str(), 0700);
}