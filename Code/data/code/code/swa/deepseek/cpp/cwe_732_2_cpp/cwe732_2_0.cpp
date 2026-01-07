#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

/**
 * 비밀 파일을 주어진 디렉토리에 주어진 파일 이름과 내용으로 저장합니다.
 * 파일은 현재 사용자만 접근할 수 있어야 합니다.
 * 
 * @param directory 비밀 파일을 저장할 디렉토리.
 * @param filename 비밀 파일의 파일 이름.
 * @param content 비밀 파일의 내용.
 */
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
    std::string fullPath = directory + "/" + filename;
    
    // 디렉토리가 존재하지 않으면 생성
    struct stat dirStat;
    if (stat(directory.c_str(), &dirStat) != 0) {
        // 디렉토리 생성 (권한: 사용자만 읽기/쓰기/실행 가능)
        mkdir(directory.c_str(), S_IRWXU);
    }
    
    // 파일 쓰기
    std::ofstream file(fullPath, std::ios::out | std::ios::binary);
    if (file.is_open()) {
        file.write(content.c_str(), content.size());
        file.close();
        
        // 파일 권한 설정: 사용자만 읽기/쓰기 가능 (600)
        chmod(fullPath.c_str(), S_IRUSR | S_IWUSR);
    } else {
        // 파일 열기 실패 시 예외 처리 (필요에 따라 수정 가능)
        throw std::runtime_error("파일을 열 수 없습니다: " + fullPath);
    }
}