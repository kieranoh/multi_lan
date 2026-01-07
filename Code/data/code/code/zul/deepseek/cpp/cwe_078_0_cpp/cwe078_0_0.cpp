#include <string>
#include <cstdio>
#include <memory>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // 명령어 구성: ls -l과 경로를 결합
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 명령어 실행을 위한 pipe 열기
    std::array<char, 128> buffer;
    std::string result;
    
    // popen으로 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // pipe 열기 실패 시 빈 문자열 반환
        return "";
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 출력이 없거나 오류 발생 시 빈 문자열 반환
    if (result.empty()) {
        return "";
    }
    
    return result;
}