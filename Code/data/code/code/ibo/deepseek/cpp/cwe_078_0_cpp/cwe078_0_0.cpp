#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // 명령어 구성: 디렉토리 경로를 안전하게 전달하기 위해 따옴표로 감쌈
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 출력 캡처를 위한 버퍼
    std::array<char, 128> buffer;
    std::string result;
    
    // 파이프를 열어 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // 파이프 열기 실패 시 빈 문자열 반환
        return "";
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // pclose는 unique_ptr 소멸 시 자동으로 호출됨
    // 반환값 검사: popen이 성공했더라도 명령어 실행 자체가 실패할 수 있음
    // (예: 디렉토리가 없거나 권한 문제)
    if (result.empty()) {
        return "";
    }
    
    return result;
}