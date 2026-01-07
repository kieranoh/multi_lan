#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <cstring>

std::string get_ls_result(const std::string &dir_path) {
    // 빈 경로인 경우 빈 문자열 반환
    if (dir_path.empty()) {
        return "";
    }

    // 명령어 구성: ls -l과 경로를 결합
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 명령어 실행을 위한 FILE 포인터
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // popen 실패 시 빈 문자열 반환
        return "";
    }
    
    std::string result;
    std::array<char, 128> buffer;
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 명령어 실행 실패 또는 빈 출력인 경우 빈 문자열 반환
    if (result.empty() || result.find("total") == std::string::npos) {
        return "";
    }
    
    return result;
}