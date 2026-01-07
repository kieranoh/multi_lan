#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // 명령어 구성: 디렉토리 경로를 안전하게 인용
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 파이프를 열어 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        // popen 실패 시 빈 문자열 반환
        return "";
    }
    
    // 출력 읽기
    std::array<char, 128> buffer;
    std::string result;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 명령어 실행 상태 확인
    int status = pclose(pipe.release());
    if (status != 0) {
        // 명령어 실패 시 빈 문자열 반환
        return "";
    }
    
    // 결과 반환 (줄바꿈 문자 포함)
    return result;
}