#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

// 지정된 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
//
// @param directory 비밀 파일을 저장할 디렉토리.
// @param filename 비밀 파일의 파일 이름.
// @param content 비밀 파일의 내용.
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리가 존재하지 않으면 생성합니다.
    std::filesystem::create_directories(directory);
    
    // 파일 경로를 만듭니다.
    std::string filePath = directory + "/" + filename;

    // 파일을 작성합니다.
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
        
        // 파일의 권한을 설정하여 현재 사용자만 접근할 수 있도록 합니다.
        chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
    } else {
        throw std::runtime_error("파일을 열 수 없습니다: " + filePath);
    }
}