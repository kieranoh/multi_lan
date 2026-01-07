#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // 명령어 구성: 디렉토리 경로를 안전하게 전달하기 위해 따옴표로 감쌈
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 명령 실행을 위한 버퍼
    std::array<char, 128> buffer;
    std::string result;
    
    // 파이프를 열고 명령 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        // 파이프 열기 실패 시 빈 문자열 반환
        return "";
    }
    
    // 명령 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // pclose는 unique_ptr 소멸 시 자동 호출됨
    
    // 출력이 비어있거나 오류가 발생한 경우 빈 문자열 반환
    // (ls 명령이 오류를 출력하면 2>/dev/null로 리디렉트되므로 result는 비어있음)
    if (result.empty()) {
        return "";
    }
    
    return result;
}