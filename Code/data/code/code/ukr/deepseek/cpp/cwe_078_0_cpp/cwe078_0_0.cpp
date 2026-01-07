#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // 빈 경로가 주어진 경우 빈 문자열 반환
    if (dir_path.empty()) {
        return "";
    }
    
    // 명령어 구성: ls -l 뒤에 경로 추가
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 파이프를 열어 명령어 실행
    std::array<char, 128> buffer;
    std::string result;
    
    // popen을 사용하여 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    // 파이프 열기 실패 시 빈 문자열 반환
    if (!pipe) {
        return "";
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 출력이 비어있거나 오류가 발생한 경우 빈 문자열 반환
    if (result.empty()) {
        return "";
    }
    
    return result;
}