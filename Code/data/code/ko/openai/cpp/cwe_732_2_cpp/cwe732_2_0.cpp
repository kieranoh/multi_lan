#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리와 파일 경로를 결합
    std::string filepath = directory + "/" + filename;

    // 비밀 파일을 작성
    std::ofstream ofs(filepath);
    if (!ofs) {
        std::cerr << "파일을 생성할 수 없습니다: " << filepath << std::endl;
        return;
    }
    ofs << content;
    ofs.close();

    // 파일 접근 권한 설정: 소유자만 읽고 쓸 수 있도록
    mode_t mode = S_IRUSR | S_IWUSR; // rw------
    if (chmod(filepath.c_str(), mode) != 0) {
        std::cerr << "파일 권한을 설정할 수 없습니다: " << filepath << std::endl;
    }
}