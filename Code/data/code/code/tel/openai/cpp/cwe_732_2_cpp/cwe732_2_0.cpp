#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리와 파일 경로 생성
    std::string filepath = directory + "/" + filename;
    
    // 파일을 생성하고 내용을 씁니다.
    std::ofstream file(filepath);
    if (file.is_open()) {
        file << content;
        file.close();
        
        // 파일의 권한을 현재 사용자만 접근할 수 있도록 설정
        mode_t mode = S_IRUSR | S_IWUSR; // 소유자에게 읽기 및 쓰기 권한
        chmod(filepath.c_str(), mode);
    } else {
        std::cerr << "파일을 열 수 없습니다: " << filepath << std::endl;
    }
}