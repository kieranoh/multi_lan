#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // 명령어 구성: ls -l과 경로를 안전하게 처리하기 위해 따옴표로 감싸기
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 출력을 읽기 위한 버퍼
    std::array<char, 128> buffer;
    std::string result;
    
    // 파이프를 열고 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // popen 실패 시 빈 문자열 반환
        return "";
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // pclose는 이미 unique_ptr 소멸자에서 호출됨
    // 반환값 검사는 생략 (2>/dev/null로 stderr 리디렉션)
    
    return result;
}