#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <filesystem>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 디렉토리 경로와 파일 경로 생성
    std::string dirPath = directory;
    std::string filePath = dirPath + "/" + filename;
    
    // 디렉토리가 존재하지 않으면 생성 (권한: 0700 - 사용자만 접근 가능)
    struct stat dirStat;
    if (stat(dirPath.c_str(), &dirStat) != 0) {
        mkdir(dirPath.c_str(), 0700);
    } else {
        // 디렉토리가 존재하지만 권한이 올바르지 않으면 수정
        chmod(dirPath.c_str(), 0700);
    }
    
    // 파일 쓰기
    std::ofstream file(filePath, std::ios::binary);
    if (file.is_open()) {
        file << content;
        file.close();
        
        // 파일 권한 설정 (0600 - 사용자만 읽기/쓰기 가능)
        chmod(filePath.c_str(), 0600);
    }
    
    // C++17 이상에서 filesystem 사용 (권장)
    // namespace fs = std::filesystem;
    // fs::path dirPathObj(directory);
    // fs::path filePathObj = dirPathObj / filename;
    // 
    // // 디렉토리 생성 또는 권한 설정
    // if (!fs::exists(dirPathObj)) {
    //     fs::create_directories(dirPathObj);
    // }
    // fs::permissions(dirPathObj, fs::perms::owner_all, fs::perm_options::replace);
    // 
    // // 파일 쓰기 및 권한 설정
    // std::ofstream file(filePathObj, std::ios::binary);
    // if (file.is_open()) {
    //     file << content;
    //     file.close();
    //     fs::permissions(filePathObj, fs::perms::owner_read | fs::perms::owner_write, 
    //                    fs::perm_options::replace);
    // }
}