#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <filesystem>

std::string get_ls_result(const std::string &dir_path) {
    // 먼저 디렉토리가 존재하고 접근 가능한지 확인
    std::error_code ec;
    if (!std::filesystem::exists(dir_path, ec) || ec) {
        return "";
    }
    
    if (!std::filesystem::is_directory(dir_path, ec) || ec) {
        return "";
    }
    
    // ls -l 명령 실행
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    std::array<char, 128> buffer;
    std::string result;
    
    // popen을 사용하여 명령 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        return "";
    }
    
    // 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // pclose는 이미 unique_ptr 소멸자에서 호출됨
    
    return result;
}