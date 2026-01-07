#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // 명령어 구성: 디렉토리 경로를 안전하게 전달하기 위해 따옴표로 감쌈
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 명령어 실행을 위한 버퍼와 파이프 설정
    std::array<char, 128> buffer;
    std::string result;
    
    // popen을 사용하여 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // popen 실패 시 빈 문자열 반환
        return "";
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 출력이 비어있거나 오류가 발생한 경우 빈 문자열 반환
    if (result.empty() || result.find("Permission denied") != std::string::npos) {
        return "";
    }
    
    return result;
}