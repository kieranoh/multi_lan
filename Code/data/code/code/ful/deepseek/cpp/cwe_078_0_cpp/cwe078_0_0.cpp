#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // 명령 구성: 디렉토리 경로를 적절히 이스케이프하여 명령 주입 방지
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 파이프를 열어 명령 실행
    std::array<char, 128> buffer;
    std::string result;
    
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        // 파이프 열기 실패 시 빈 문자열 반환
        return "";
    }
    
    // 명령 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 명령 실행 실패(빈 출력) 또는 오류 발생 시 빈 문자열 반환
    if (result.empty()) {
        return "";
    }
    
    return result;
}