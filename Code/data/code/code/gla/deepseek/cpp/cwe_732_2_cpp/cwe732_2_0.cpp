#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>

// 비밀 파일을 주어진 디렉토리에 주어진 파일 이름과 내용으로 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
// 
// @param directory 비밀 파일을 저장할 디렉토리.
// @param filename 비밀 파일의 파일 이름.
// @param content 비밀 파일의 내용.
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    namespace fs = std::filesystem;
    
    // 디렉토리 경로 생성
    fs::path dir_path(directory);
    
    // 디렉토리가 존재하지 않으면 생성
    if (!fs::exists(dir_path)) {
        fs::create_directories(dir_path);
        // 디렉토리 권한 설정: 현재 사용자만 읽기/쓰기/실행 가능 (0700)
        fs::permissions(dir_path, 
                       fs::perms::owner_all | fs::perms::group_all | fs::perms::others_all,
                       fs::perm_options::remove);
        fs::permissions(dir_path, 
                       fs::perms::owner_all,
                       fs::perm_options::add);
    }
    
    // 전체 파일 경로 생성
    fs::path file_path = dir_path / filename;
    
    // 파일 쓰기
    std::ofstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("파일을 열 수 없습니다: " + file_path.string());
    }
    
    file.write(content.c_str(), content.size());
    file.close();
    
    // 파일 권한 설정: 현재 사용자만 읽기/쓰기 가능 (0600)
    fs::permissions(file_path, 
                   fs::perms::owner_all | fs::perms::group_all | fs::perms::others_all,
                   fs::perm_options::remove);
    fs::permissions(file_path, 
                   fs::perms::owner_read | fs::perms::owner_write,
                   fs::perm_options::add);
}