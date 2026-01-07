#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // 명령어 구성: 디렉토리 경로를 안전하게 전달하기 위해 따옴표로 감쌈
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 명령어 실행을 위한 버퍼
    std::array<char, 128> buffer;
    std::string result;
    
    // 파이프를 통해 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // 파이프 생성 실패 시 빈 문자열 반환
        return "";
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 출력이 비어있거나 오류 발생 시 빈 문자열 반환
    if (result.empty() || result.find("No such file or directory") != std::string::npos) {
        return "";
    }
    
    return result;
}